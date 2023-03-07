#pragma once

#include <type_traits>
#include <utility>

#include <actor-zeta/detail/memory_resource.hpp>

namespace actor_zeta { namespace detail {

    template<class Signature>
    class unique_function;

    template<class R, class... Args>
    class unique_function<R(Args...)> {
        detail::pmr::memory_resource* memory_resource_ = nullptr;

        /***
         * @brief class wrapper
         **/
        class wrapper {
        public:
            virtual ~wrapper() {}
            virtual R operator()(Args...) = 0;

            virtual void destroy(detail::pmr::memory_resource* memory_resource, void* ptr) = 0;
        };

        using raw_pointer = R (*)(Args...);
        using wrapper_pointer = wrapper*;

        template<class F>
        class wrapper_maker_t {
            class impl final : public wrapper {
            public:
                impl(F&& fun)
                    : fun_(std::move(fun)) {
                }

                R operator()(Args... args) override {
                    return fun_(args...);
                }

                void destroy(detail::pmr::memory_resource* memory_resource, void* ptr) {
                    assert(ptr);
//                    printf("%s %p\n", __func__, ptr);
                    detail::pmr::deallocate_ptr<impl>(memory_resource, reinterpret_cast<impl**>(&ptr));
                }

            private:
                F fun_;
            };

        public:
            static wrapper_pointer make_wrapper(detail::pmr::memory_resource* memory_resource, F&& f) { 
                auto* impl_ptr = detail::pmr::allocate_ptr<impl>(memory_resource, std::forward<F>(f));
//                printf("%s sizeof(impl) = %d, alignof(impl) = %d\n", __func__, sizeof(impl), alignof(impl));
                assert(impl_ptr);
                return wrapper_pointer{impl_ptr};
            }
        };

    public:
        unique_function()
            : holds_wrapper_(false)
            , fptr_(nullptr) {
        }

        unique_function(unique_function&& other)
            : holds_wrapper_(other.holds_wrapper_) {
            fptr_ = other.fptr_;
            if (other.holds_wrapper_) {
                other.holds_wrapper_ = false;
            }
            other.fptr_ = nullptr;
        }

        unique_function(const unique_function&) = delete;

        explicit unique_function(raw_pointer fun)
            : memory_resource_(nullptr)
            , holds_wrapper_(false)
            , fptr_(fun) {
        }

        explicit unique_function(detail::pmr::memory_resource* memory_resource, wrapper_pointer ptr)
            : memory_resource_(memory_resource)
            , holds_wrapper_(true)
            , wptr_(ptr) {
        }

        template<
            class T,
            class = typename std::enable_if<
                !std::is_convertible<T, raw_pointer>::value && std::is_same<decltype((std::declval<T&>())(std::declval<Args>()...)),
                                                                            R>::value>::type>
        explicit unique_function(detail::pmr::memory_resource* memory_resource, T f)
            : unique_function(memory_resource, wrapper_maker_t<T>::make_wrapper(memory_resource, std::move(f))) {
        }

        ~unique_function() {
            destroy();
        }

        /**
         * 
         * @brief test_same_decltype [static]
         * 
         * @details for tests only
         * 
         **/
        template<class T>
        static bool test_same_decltype(T f) {
            return std::is_same<decltype((std::declval<T&>())(std::declval<Args>()...)), R>::value;
        }

        /**
         * 
         * @brief test_convertible [static]
         * 
         * @details for tests only
         * 
         **/
        template<class T>
        static bool test_convertible(T f) {
            return !std::is_convertible<T, raw_pointer>::value;
        }

        unique_function& operator=(unique_function&& other) {
            destroy();
            if (other.holds_wrapper_) {
                holds_wrapper_ = true;
                wptr_ = other.wptr_;
                other.holds_wrapper_ = false;
                other.fptr_ = nullptr;
            } else {
                holds_wrapper_ = false;
                fptr_ = other.fptr_;
            }
            return *this;
        }

        unique_function& operator=(raw_pointer f) {
            return *this = unique_function{f};
        }

        unique_function& operator=(const unique_function&) = delete;

        void assign(raw_pointer f) {
            *this = unique_function{f};
        }

        void assign(wrapper_pointer ptr) {
            *this = unique_function{ptr};
        }

        R operator()(Args... args) {
            if (holds_wrapper_) {
                return (*wptr_)(std::move(args)...);
            }
            return (*fptr_)(std::move(args)...);
        }

        explicit operator bool() const noexcept {
            return !is_nullptr();
        }

        bool operator!() const noexcept {
            return is_nullptr();
        }

    private:
        bool is_nullptr() const noexcept {
            return fptr_ == nullptr;
        }

        void destroy() {
            if (holds_wrapper_) {
                wptr_->destroy(memory_resource_, wptr_);
            }
        }

        bool holds_wrapper_;

        union {
            raw_pointer fptr_;
            wrapper_pointer wptr_;
        };
    };

    template<class T>
    bool operator==(const unique_function<T>& x, std::nullptr_t) noexcept {
        return x.is_nullptr();
    }

    template<class T>
    bool operator==(std::nullptr_t, const unique_function<T>& x) noexcept {
        return x.is_nullptr();
    }

    template<class T>
    bool operator!=(const unique_function<T>& x, std::nullptr_t) noexcept {
        return !x.is_nullptr();
    }

    template<class T>
    bool operator!=(std::nullptr_t, const unique_function<T>& x) noexcept {
        return !x.is_nullptr();
    }

}} // namespace actor_zeta::detail
