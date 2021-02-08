#pragma once

#include <actor-zeta/abstract_supervisor.hpp>

namespace actor_zeta {

    class supervisor final {
    public:
        supervisor() = default;

        supervisor(const supervisor& a) = delete;

        supervisor(supervisor&& a) = default;

        supervisor& operator=(const supervisor& a) = delete;

        supervisor& operator=(supervisor&& a) = default;

        supervisor(std::nullptr_t);

        supervisor& operator=(std::nullptr_t);

        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<abstract_supervisor, T>::value>>
        supervisor(T* ptr)
            : ptr_(ptr) {}
        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<abstract_supervisor, T>::value>>
        supervisor& operator=(T* ptr) {
            supervisor tmp{ptr};
            swap(tmp);
            return *this;
        }

        auto address() const noexcept -> address_t;

        ~supervisor();

        inline abstract_supervisor* operator->() const noexcept {
            return ptr_.get();
        }

        inline explicit operator bool() const noexcept {
            return static_cast<bool>(ptr_);
        }

        auto name() const -> detail::string_view;

        inline bool operator!() const noexcept {
            return !ptr_;
        }

        abstract_supervisor* get();

    private:
        void swap(supervisor&) noexcept;

        std::unique_ptr<abstract_supervisor> ptr_;
    };
}