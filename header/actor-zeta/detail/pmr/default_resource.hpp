#pragma once

#include <actor-zeta/config.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <atomic>
#include <cassert>
#include <memory>
#include <new>

namespace actor_zeta { namespace detail { namespace pmr {

#if CPP17_OR_GREATER && defined __has_include
#if __has_include(<memory_resource>)
    using std::pmr::get_default_resource;
    using std::pmr::set_default_resource;
    using std::pmr::new_delete_resource;
    using std::pmr::null_memory_resource;
#endif
#else
    class null_memory_resource_t final : public memory_resource {
        union holder;

#ifndef WEAK_CONSTINIT
#ifndef NO_DESTROY
        static holder instance_;
#else
        NO_DESTROY
        static null_memory_resource_t instance_;
#endif
#else
        static null_memory_resource_t instance_;
#endif

    public:
        static memory_resource*
        get() noexcept {
            return reinterpret_cast<memory_resource*>(
                reinterpret_cast<std::uintptr_t*>(
                    &instance_));
        }
        ~null_memory_resource_t();

        void*
        do_allocate(
            std::size_t bytes,
            std::size_t alignment) override;

        void
        do_deallocate(
            void* p,
            std::size_t bytes,
            std::size_t alignment) override;

        bool
        do_is_equal(
            memory_resource const& mr) const noexcept override;
    };

    class default_memory_resource_t final : public memory_resource {
        union holder;

#ifndef WEAK_CONSTINIT
#ifndef NO_DESTROY
        static holder instance_;
#else
        NO_DESTROY
        static default_memory_resource_t instance_;
#endif
#else
        static default_memory_resource_t instance_;
#endif

    public:
        static memory_resource*
        exchange(memory_resource* new_res = nullptr) noexcept {
            static std::atomic<memory_resource*> __res =
                {reinterpret_cast<memory_resource*>(
                    reinterpret_cast<std::uintptr_t*>(
                        &instance_))};
            if (new_res) {
                return std::atomic_exchange_explicit(
                    &__res, new_res, std::memory_order_acq_rel); // @TODO maybe check memory order
            }
            return std::atomic_load_explicit(
                &__res, std::memory_order_acquire);
        }

        ~default_memory_resource_t();

        void*
        do_allocate(
            std::size_t bytes,
            std::size_t alignment) override;

        void
        do_deallocate(
            void* p,
            std::size_t bytes,
            std::size_t alignment) override;

        bool
        do_is_equal(
            memory_resource const& mr) const noexcept override;
    };

    union null_memory_resource_t::holder {
#ifndef WEAK_CONSTINIT
        constexpr
#endif
            holder()
            : mr() {
        }
        ~holder() {}

        null_memory_resource_t mr;
    };

    union default_memory_resource_t::holder {
#ifndef WEAK_CONSTINIT
        constexpr
#endif
            holder()
            : mr() {
        }
        ~holder() {}

        default_memory_resource_t mr;
    };

    memory_resource* get_default_resource() noexcept;

    memory_resource* set_default_resource(memory_resource* new_res) noexcept;

    memory_resource* new_delete_resource() noexcept;

    memory_resource* null_memory_resource() noexcept;

#endif

}}} // namespace actor_zeta::detail::pmr