#pragma once

#include <type_traits>
#include <utility>

namespace actor_zeta { namespace detail {

    template<class Signature>
    class unique_function;

    template<class R, class... Args>
    class unique_function<R(Args...)> {
    public:
        class wrapper {
        public:
            virtual ~wrapper() {}
            virtual R operator()(Args...) = 0;
        };

        using raw_pointer = R (*)(Args...);
        using wrapper_pointer = wrapper*;

        template<class F>
        static wrapper_pointer make_wrapper(F&& f) {
            class impl final : public wrapper {
            public:
                impl(F&& fun)
                    : fun_(std::move(fun)) {
                }

                R operator()(Args... args) override {
                    return fun_(args...);
                }

            private:
                F fun_;
            };
            return new impl(std::forward<F>(f));
        }

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
            : holds_wrapper_(false)
            , fptr_(fun) {
        }

        explicit unique_function(wrapper_pointer ptr)
            : holds_wrapper_(true)
            , wptr_(ptr) {
        }

        template<
            class T,
            class = typename std::enable_if<
                !std::is_convertible<T, raw_pointer>::value && std::is_same<decltype((std::declval<T&>())(std::declval<Args>()...)),
                                                                            R>::value>::type>
        explicit unique_function(T f)
            : unique_function(make_wrapper(std::move(f))) {
            // nop
        }

        ~unique_function() {
            destroy();
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
                delete wptr_;
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
