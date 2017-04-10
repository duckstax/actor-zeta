#ifndef INTRUSIVE_PTR_HPP
#define INTRUSIVE_PTR_HPP
//C++ 11 intrusive_ptr
//frindle api for boost

#include <utility>
#include "ref_counted.hpp"

namespace actor_zeta {
///
/// @brief This class represents smart pointers
/// @tparam T
///
    template<class T>
    class intrusive_ptr {
    public:
        using pointer = T *;
        using reference = T &;

        constexpr intrusive_ptr() : ptr_(nullptr) {}

        intrusive_ptr(pointer raw_ptr, bool add_ref = true) {
            set_ptr(raw_ptr, add_ref);
        }

        intrusive_ptr(intrusive_ptr &&other) : ptr_(other.detach()) {}

        intrusive_ptr(const intrusive_ptr &other) {
            set_ptr(other.get(), true);
        }

        template<class Y>
        intrusive_ptr(intrusive_ptr<Y> other) : ptr_(other.detach()) {
            static_assert(std::is_convertible<Y *, T *>::value,
                          "Y* is not assignable to T*");
        }

        intrusive_ptr &operator=(pointer ptr) {
            reset(ptr);
            return *this;
        }

        intrusive_ptr &operator=(intrusive_ptr other) {
            swap(other);
            return *this;
        }

        ~intrusive_ptr() {
            if (ptr_) {
                intrusive_ptr_release(ptr_);
            }
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

        void reset(pointer new_value = nullptr, bool add_ref = true) {
            auto old = ptr_;
            set_ptr(new_value, add_ref);
            if (old) {
                intrusive_ptr_release(old);
            }
        }

        pointer get() const {
            return ptr_;
        }

        pointer operator->() const {
            return ptr_;
        }

        reference operator*() const {
            return *ptr_;
        }

        bool operator!() const {
            return ptr_ == nullptr;
        }

        explicit operator bool() const {
            return ptr_ != nullptr;
        }

        void swap(intrusive_ptr &other) noexcept {
            std::swap(ptr_, other.ptr_);
        }

        template<class C>
        intrusive_ptr<C> downcast() const {
            return (ptr_) ? dynamic_cast<C *>(get()) : nullptr;
        }

        template<class C>
        intrusive_ptr<C> upcast() const {
            return (ptr_) ? static_cast<C *>(get()) : nullptr;
        }

    private:
        inline void set_ptr(pointer raw_ptr, bool add_ref) {
            ptr_ = raw_ptr;
            if (raw_ptr && add_ref) {
                intrusive_ptr_add_ref(raw_ptr);
            }
        }

        pointer ptr_;
    };

    template<class T, class U>
    bool operator==(intrusive_ptr<T> const &a, intrusive_ptr<U> const &b) noexcept {
        return a.get() == b.get();
    }

    template<class T, class U>
    bool operator!=(intrusive_ptr<T> const &a, intrusive_ptr<U> const &b) noexcept {
        return !(a == b);
    }

    template<class T>
    bool operator==(intrusive_ptr<T> const &a, T *b) noexcept {
        return a.get() == b;
    }

    template<class T>
    bool operator!=(intrusive_ptr<T> const &a, T *b) noexcept {
        return a.get() != b;
    }

    template<class T>
    bool operator==(T *a, intrusive_ptr<T> const &b)noexcept {
        return a == b.get();
    }

    template<class T>
    bool operator!=(T *a, intrusive_ptr<T> const &b)noexcept {
        return a != b.get();
    }

    template<class T, class U>
    bool operator<(intrusive_ptr<T> const &a, intrusive_ptr<U> const &b) noexcept; // never throws

    template<class T>
    inline void swap(intrusive_ptr<T> &a, intrusive_ptr<T> &b) noexcept {
        a.swap(b);
    }

    template<class T>
    T *get_pointer(intrusive_ptr<T> const &p) noexcept {
        return p.get();
    }

    template<class T, class U>
    intrusive_ptr<T> static_pointer_cast(intrusive_ptr<U> const &r) noexcept {
        return r.template upcast<T>();
    }

    template<class T, class U>
    intrusive_ptr<T> const_pointer_cast(intrusive_ptr<U> const &r) noexcept; // never throws

    template<class T, class U>
    intrusive_ptr<T> dynamic_pointer_cast(intrusive_ptr<U> const &r) noexcept {
        return r.template downcast<T>();
    }
}
#endif //INTRUSIVE_PTR_HPP