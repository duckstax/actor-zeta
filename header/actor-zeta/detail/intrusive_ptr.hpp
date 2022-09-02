#pragma once

//C++ 11 intrusive_ptr
//frindle api for boost

#include <utility>

#include <actor-zeta/detail/ref_counted.hpp>
#include <actor-zeta/detail/type_traits.hpp>

namespace actor_zeta {
    ///
    /// @brief Represents intrusive pointer
    /// @tparam T
    ///
    template<class T>
    class intrusive_ptr final {
    public:
        using pointer = T*;
        using const_pointer = const T*;
        using element_type = T;
        using reference = T&;
        using const_reference = const T&;

        constexpr intrusive_ptr() noexcept
            : ptr_(nullptr) {
        }

        constexpr intrusive_ptr(std::nullptr_t) noexcept
            : intrusive_ptr() {
        }

        intrusive_ptr(pointer raw_ptr, bool add_ref = true) noexcept {
            set_ptr(raw_ptr, add_ref);
        }

        intrusive_ptr(intrusive_ptr&& other) noexcept
            : ptr_(other.detach()) {
        }

        intrusive_ptr(const intrusive_ptr& other) noexcept {
            set_ptr(other.get(), true);
        }

        template<class Y>
        intrusive_ptr(intrusive_ptr<Y> other) noexcept
            : ptr_(other.detach()) {
            static_assert(std::is_convertible<Y*, T*>::value, "Y* is not assignable to T*");
        }

        intrusive_ptr& operator=(pointer ptr) noexcept {
            reset(ptr);
            return *this;
        }

        intrusive_ptr& operator=(intrusive_ptr other) noexcept {
            swap(other);
            return *this;
        }

        ~intrusive_ptr() {
            if (ptr_) {
                intrusive_ptr_release(ptr_);
            }
        }

        void swap(intrusive_ptr& other) noexcept {
            using std::swap;
            std::swap(ptr_, other.ptr_);
        }

        pointer detach() noexcept {
            auto result = ptr_;
            if (result) {
                ptr_ = nullptr;
            }
            return result;
        }

        pointer release() noexcept {
            return detach();
        }

        void reset(pointer new_value = nullptr, bool add_ref = true) noexcept {
            auto old = ptr_;
            set_ptr(new_value, add_ref);
            if (old) {
                intrusive_ptr_release(old);
            }
        }

        pointer get() const noexcept {
            return ptr_;
        }

        pointer operator->() const noexcept {
            return ptr_;
        }

        reference operator*() const noexcept {
            return *ptr_;
        }

        bool operator!() const noexcept {
            return !ptr_;
        }

        explicit operator bool() const noexcept {
            return ptr_ != nullptr;
        }

        template<class C>
        intrusive_ptr<C> downcast() const noexcept {
            return (ptr_) ? dynamic_cast<C*>(get()) : nullptr;
        }

        template<class C>
        intrusive_ptr<C> upcast() const noexcept {
            return (ptr_) ? static_cast<C*>(get()) : nullptr;
        }

    private:
        void set_ptr(pointer raw_ptr, bool add_ref) noexcept {
            ptr_ = raw_ptr;
            if (raw_ptr && add_ref) {
                intrusive_ptr_add_ref(raw_ptr);
            }
        }

        pointer ptr_;
    };

    template<class T>
    bool operator==(const intrusive_ptr<T>& x, std::nullptr_t) noexcept {
        return !x;
    }

    template<class T>
    bool operator==(std::nullptr_t, const intrusive_ptr<T>& x) noexcept {
        return !x;
    }

    template<class T>
    bool operator!=(const intrusive_ptr<T>& x, std::nullptr_t) noexcept {
        return static_cast<bool>(x);
    }

    template<class T>
    bool operator!=(std::nullptr_t, const intrusive_ptr<T>& x) noexcept {
        return static_cast<bool>(x);
    }

    template<class T>
    bool operator==(const intrusive_ptr<T>& x, const T* y) noexcept {
        return x.get() == y;
    }

    template<class T>
    bool operator==(const T* x, const intrusive_ptr<T>& y) noexcept {
        return x == y.get();
    }

    template<class T>
    bool operator!=(const intrusive_ptr<T>& x, const T* y) noexcept {
        return x.get() != y;
    }

    template<class T>
    bool operator!=(const T* x, const intrusive_ptr<T>& y) noexcept {
        return x != y.get();
    }

    template<class T>
    bool operator<(const intrusive_ptr<T>& x, const intrusive_ptr<T>& y) {
        return x.get() < y.get();
    }

    template<class T>
    inline void swap(intrusive_ptr<T>& a, intrusive_ptr<T>& b) noexcept {
        a.swap(b);
    }

    template<class T>
    bool operator<(const intrusive_ptr<T>& x, const T* y) noexcept {
        return x.get() < y;
    }

    template<class T>
    bool operator<(const T* x, const intrusive_ptr<T>& y) noexcept {
        return x < y.get();
    }

    template<class T>
    T* get_pointer(intrusive_ptr<T> const& p) noexcept {
        return p.get();
    }

    template<class T, class U>
    intrusive_ptr<T> static_pointer_cast(intrusive_ptr<U> const& r) noexcept {
        return r.template upcast<T>();
    }

    template<class T, class U>
    intrusive_ptr<T> const_pointer_cast(intrusive_ptr<U> const& r) noexcept; // never throws

    template<class T, class U>
    intrusive_ptr<T> dynamic_pointer_cast(intrusive_ptr<U> const& r) noexcept {
        return r.template downcast<T>();
    }

    template<class T, class... args>
    intrusive_ptr<T> make_counted(args&&... xs) {
        return intrusive_ptr<T>(new T(std::forward<args>(xs)...), false);
    }

} // namespace actor_zeta