#pragma once

#include <actor-zeta/detail/intrusive_ptr.hpp>

#include <type_traits>

namespace actor_zeta { namespace base {

    /**
     * @class supervisor
     * @brief
     *
     * @tparam actor_traits
     */
    template<typename actor_traits>
    class supervisor final {
    public:
        using supervisor_abstract_t = supervisor_abstract<actor_traits>;
        using supervisor_abstract_ptr = supervisor_abstract_t*;

        supervisor() = default;

        supervisor(const supervisor& a) = delete;

        supervisor(supervisor&& a) = default;

        supervisor& operator=(const supervisor& a) = delete;

        supervisor& operator=(supervisor&& a) = default;

        supervisor(std::nullptr_t)
            : ptr_(nullptr) {}

        supervisor& operator=(std::nullptr_t) {
            ptr_.reset();
            return *this;
        }

        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract_t, T>::value>>
        supervisor(intrusive_ptr<T> ptr)
            : ptr_(std::move(ptr)) {}

        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract_t, T>::value>>
        supervisor(T* ptr)
            : ptr_(ptr) {}

        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract_t, T>::value>>
        supervisor& operator=(intrusive_ptr<T> ptr) {
            supervisor tmp{std::move(ptr)};
            swap(tmp);
            return *this;
        }

        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract_t, T>::value>>
        supervisor& operator=(T* ptr) {
            supervisor tmp{ptr};
            swap(tmp);
            return *this;
        }

        inline address_t address() const noexcept { return address_t(ptr_.get()); }

        ~supervisor() {}

        inline supervisor_abstract_ptr operator->() const noexcept {
            return ptr_.get();
        }

        inline supervisor_abstract_ptr get() const noexcept {
            return ptr_.get();
        }

        inline explicit operator bool() const noexcept {
            return static_cast<bool>(ptr_);
        }

        inline auto type() const -> const char* const { return ptr_->type(); }

        inline bool operator!() const noexcept {
            return !ptr_;
        }

    private:
        inline void swap(supervisor& other) noexcept {
            using std::swap;
            ptr_.swap(other.ptr_);
        }

        intrusive_ptr<supervisor_abstract_t> ptr_;
    };

//    static_assert(std::is_move_constructible<supervisor<actor_traits>>::value, ""); // @TODO static_assert !!!
//    static_assert(not std::is_copy_constructible<supervisor<actor_traits>>::value, ""); // @TODO static_assert !!!

}} // namespace actor_zeta::base
