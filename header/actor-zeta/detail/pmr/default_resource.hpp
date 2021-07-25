#pragma once

#include <actor-zeta/config.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <atomic>
#include <cassert>
#include <memory>
#include <new>
#include <stdexcept>

namespace actor_zeta { namespace detail { namespace pmr {

    class default_resource final : public memory_resource {
        union holder;

#ifndef WEAK_CONSTINIT
#ifndef NO_DESTROY
        static holder instance_;
#else
        NO_DESTROY
        static default_resource instance_;
#endif
#endif

    public:
        static memory_resource*
        get() noexcept {
#ifdef WEAK_CONSTINIT
            static default_resource instance_;
#endif
            return reinterpret_cast<memory_resource*>(
                reinterpret_cast<std::uintptr_t*>(
                    &instance_));
        }

        ~default_resource();

        void*
        do_allocate(
            std::size_t n,
            std::size_t) override;

        void
        do_deallocate(
            void* p,
            std::size_t,
            std::size_t) override;

        bool
        do_is_equal(
            memory_resource const& mr) const noexcept override;
    };

    union default_resource::holder {
#ifndef WEAK_CONSTINIT
        constexpr
#endif
            holder()
            : mr() {
        }
        ~holder() {}

        default_resource mr;
    };

    namespace resource {

#if CPP17_OR_GREATER
#if __has_include(<memory_resource>)

        memory_resource* get_default_resource() noexcept {
            return std::pmr::get_default_resource();
        }

        memory_resource* set_default_resource(memory_resource* __new_res) noexcept {
            return std::pmr::set_default_resource(__new_res);
        }

        memory_resource* new_delete_resource() noexcept {
            return std::pmr::new_delete_resource();
        }

        memory_resource* null_memory_resource() noexcept {
            return std::pmr::null_memory_resource();
        }

        //template<class T>
        //using polymorphic_allocator = std::pmr::polymorphic_allocator<T>;

#else

        memory_resource* get_default_resource() noexcept {
            return std::experimental::pmr::get_default_resource();
        }

        memory_resource* set_default_resource(memory_resource* __new_res) noexcept {
            return std::experimental::pmr::set_default_resource(__new_res);
        }

        memory_resource* new_delete_resource() noexcept {
            return std::experimental::pmr::new_delete_resource();
        }

        memory_resource* null_memory_resource() noexcept {
            return std::experimental::pmr::null_memory_resource();
        }

        //template<class T>
        //using polymorphic_allocator = std::experimental::pmr::polymorphic_allocator<T>;

#endif

#elif CPP14_OR_GREATER or CPP11_OR_GREATER

        namespace clang_impl {

            ////////////////

            constexpr bool is_pow2(size_t n) { return (0 == (n & (n - 1))); }

            template<typename Alloc>
            void* aligned_allocate(size_t bytes, size_t alignment, Alloc alloc) {
                assert(is_pow2(alignment));

                size_t padded_allocation_size{bytes + alignment + sizeof(std::ptrdiff_t)};

                char* const original = static_cast<char*>(alloc(padded_allocation_size));

                void* aligned{original + sizeof(std::ptrdiff_t)};

                std::align(alignment, bytes, aligned, padded_allocation_size);

                std::ptrdiff_t offset = static_cast<char*>(aligned) - original;

                *(static_cast<std::ptrdiff_t*>(aligned) - 1) = offset;

                return aligned;
            }

            template<typename Dealloc>
            void aligned_deallocate(void* p, size_t bytes, size_t alignment, Dealloc dealloc) {
                (void) alignment;
                (void) bytes;

                std::ptrdiff_t const offset = *(reinterpret_cast<std::ptrdiff_t*>(p) - 1);

                void* const original = static_cast<char*>(p) - offset;

                dealloc(original);
            }

            ////////////////
            class __attribute__((__visibility__("default"))) __new_delete_memory_resource_imp
                : public memory_resource {
                void* do_allocate(size_t size, size_t align) override {
                    /*#ifdef _LIBCPP_HAS_NO_ALIGNED_ALLOCATION
                if (__is_overaligned_for_new(align))
                    __throw_bad_alloc();
#endif*/
                    return aligned_allocate(size, align, [](size_t size) { return ::operator new(size); });
                }

                void do_deallocate(void* p, size_t n, size_t align) override {
                    aligned_deallocate(p, n, align, [](void* p) { ::operator delete(p); });
                }

                bool do_is_equal(memory_resource const& other) const noexcept override { return &other == this; }

            public:
                ~__new_delete_memory_resource_imp() override = default;
            };

            class __attribute__((__visibility__("default"))) __null_memory_resource_imp
                : public memory_resource {
            public:
                ~__null_memory_resource_imp() = default;

            protected:
                virtual void* do_allocate(size_t, size_t) {
                    assert(false);
                    //throw std::runtime_error("bad_alloc");
                    //__throw_bad_alloc();
                }
                virtual void do_deallocate(void*, size_t, size_t) {}
                virtual bool do_is_equal(memory_resource const& __other) const noexcept { return &__other == this; }
            };

            union ResourceInitHelper {
                struct {
                    __new_delete_memory_resource_imp new_delete_res;
                    __null_memory_resource_imp null_res;
                } resources;
                char dummy;

                ResourceInitHelper()
                    : resources() {
                }
                ~ResourceInitHelper() {}
            };

            ResourceInitHelper res_init __attribute__((init_priority(101)));

            memory_resource* new_delete_resource() noexcept {
                return &res_init.resources.new_delete_res;
            }

            memory_resource* null_memory_resource() noexcept {
                return &res_init.resources.null_res;
            }
            static memory_resource*
            __default_memory_resource(bool set = false, memory_resource* new_res = nullptr) noexcept {
                //#ifndef _LIBCPP_HAS_NO_ATOMIC_HEADER
                __attribute__((__require_constant_initialization__)) static std::atomic<memory_resource*> __res =
                    {&res_init.resources.new_delete_res};
                std::printf("%s :: __res = %p; new_res = %p\n", __func__, __res.load(), new_res);
                if (set) {
                    new_res = new_res ? new_res : new_delete_resource();
                    // TODO: Can a weaker ordering be used?
                    auto ret = std::atomic_exchange_explicit(
                        &__res, new_res, std::memory_order_acq_rel);
                    std::printf("%s :: __res = %p; new_res = %p\n", __func__, __res.load(), new_res);
                    return ret;
                } else {
                    return std::atomic_load_explicit(
                        &__res, std::memory_order_acquire);
                }
                /*
#elif !defined(_LIBCPP_HAS_NO_THREADS)
            _LIBCPP_SAFE_STATIC static memory_resource* res = &res_init.resources.new_delete_res;
            static mutex res_lock;
            if (set) {
                new_res = new_res ? new_res : new_delete_resource();
                lock_guard<mutex> guard(res_lock);
                memory_resource* old_res = res;
                res = new_res;
                return old_res;
            } else {
                lock_guard<mutex> guard(res_lock);
                return res;
            }
#else
            _LIBCPP_SAFE_STATIC static memory_resource* res = &res_init.resources.new_delete_res;
            if (set) {
                new_res = new_res ? new_res : new_delete_resource();
                memory_resource* old_res = res;
                res = new_res;
                return old_res;
            } else {
                return res;
            }
#endif*/
            }
            memory_resource* get_default_resource() noexcept {
                return __default_memory_resource();
            }

            memory_resource* set_default_resource(memory_resource* __new_res) noexcept {
                auto res = __default_memory_resource(true, __new_res);
                std::printf("%s :: res = %p\n", __func__, res);
                return res;
            }
        } // namespace clang_impl
#endif
    } // namespace resource

}}} // namespace actor_zeta::detail::pmr