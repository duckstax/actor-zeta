#ifndef INTRUSIVE_PTR_HPP
#define INTRUSIVE_PTR_HPP
//C++ 11 intrusive_ptr
//frindle api for boost

#include <utility>
#include "ref_counted.hpp"

namespace actor_zeta {
    template<class T>
    class intrusive_ptr {
    public:
        using pointer = T *;
        using reference = T &;

        constexpr intrusive_ptr() noexcept  : ptr_(nullptr) { }

        intrusive_ptr(pointer raw_ptr, bool add_ref = true) {
            set_ptr(raw_ptr, add_ref);
        }

        intrusive_ptr(intrusive_ptr const &other) {
            set_ptr(other.get(), true);
        }

        intrusive_ptr(intrusive_ptr &&other) : ptr_(other.release()) { }

        template<class Y>
        intrusive_ptr(intrusive_ptr<Y> const &r);

        ~intrusive_ptr() {
            if (ptr_) {
                intrusive_ptr_release(ptr_);
            }
        };

        intrusive_ptr &operator=(intrusive_ptr const &other) {
            intrusive_ptr tmp{other};
            swap(tmp);
            return *this;
        }

        template<class Y>
        intrusive_ptr &operator=(intrusive_ptr<Y> const &other);

        intrusive_ptr &operator=(pointer ptr) {
            reset(ptr);
            return *this;
        }

        intrusive_ptr &operator=(intrusive_ptr &&other) {
            swap(other);
            return *this;
        }

        //TODO: boost api
        //void reset();
        //TODO: boost api
        //void reset(pointer);

        void reset(pointer new_value = nullptr, bool add_ref = true) {
            auto old = ptr_;
            set_ptr(new_value, add_ref);
            if (old) {
                intrusive_ptr_release(old);
            }
        };

        reference operator*() const noexcept {
            return *ptr_;
        };

        pointer operator->() const noexcept {
            return ptr_;
        };

        pointer get() const noexcept {
            return ptr_;
        };
        //TODO: boost api
        //pointer detach() noexcept;

        template<class... Ts>
        void emplace(Ts &&... xs) {
            reset(new T(std::forward<Ts>(xs)...));
        }

        pointer release() noexcept {
            auto result = ptr_;
            ptr_ = nullptr;
            return result;
        }

        explicit operator bool() const {
            return ptr_ != nullptr;
        };

        bool operator!() const {
            return ptr_ == nullptr;
        };

        void swap(intrusive_ptr &other) noexcept {
            std::swap(ptr_, other.ptr_);
        };

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
    void swap(intrusive_ptr<T> &a, intrusive_ptr<T> &b) noexcept {
        a.swap(b);
    }

    template<class T>
    T *get_pointer(intrusive_ptr<T> const &p) noexcept {
        return p.get();
    }

    template<class T, class U>
    intrusive_ptr<T> static_pointer_cast(intrusive_ptr<U> const &r) noexcept {
        return r.template upcast<T>();
    } // never throws

    template<class T, class U>
    intrusive_ptr<T> const_pointer_cast(intrusive_ptr<U> const &r) noexcept; // never throws

    template<class T, class U>
    intrusive_ptr<T> dynamic_pointer_cast(intrusive_ptr<U> const &r) noexcept {
        return r.template downcast<T>();
    }
/*
template<class E, class T, class Y>
std::basic_ostream<E, T> &operator<<(std::basic_ostream<E, T> &os, intrusive_ptr<Y> const &p);
*/
}
#endif //INTRUSIVE_PTR_HPP