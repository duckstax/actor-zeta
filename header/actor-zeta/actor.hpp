#pragma once

#include <memory>

#include <actor-zeta/detail/type_list.hpp>
#include <actor-zeta/forwards.hpp>

//smart actor
namespace actor_zeta {
    ///
    /// @brief An Actor's entity container
    ///
    class actor final {
    public:
        actor() = default;

        actor(const actor& a) = delete;

        actor(actor&& a) = default;

        actor& operator=(const actor& a) = delete;

        actor& operator=(actor&& a) = default;

        actor(std::nullptr_t);

        actor& operator=(std::nullptr_t);

        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<abstract_actor, T>::value>>
        actor(T* ptr)
            : ptr_(ptr) {}
/*
        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<abstract_actor, T>::value>>
        actor& operator=(intrusive_ptr<T> ptr) {
            actor tmp{std::move(ptr)};
            swap(tmp);
            return *this;
        }
*/
        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<abstract_actor, T>::value>>
        actor& operator=(T* ptr) {
            actor tmp{ptr};
            swap(tmp);
            return *this;
        }

        explicit operator bool() const {
            return static_cast<bool>(ptr_);
        }

        bool operator!() const {
            return !ptr_;
        }

        address_t address() const noexcept;

        void swap(actor& other) noexcept;

        inline abstract_actor* operator->() const noexcept {
            return ptr_.get();
        }



    private:
        std::unique_ptr<abstract_actor> ptr_;
    };
} // namespace actor_zeta::base
