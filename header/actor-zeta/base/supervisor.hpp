#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/forwards.hpp>
#include <functional>

namespace actor_zeta { namespace base {

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
            class = type_traits::enable_if_t<std::is_base_of<supervisor_t, T>::value>>
        supervisor(detail::intrusive_ptr<T> ptr)
            : ptr_(std::move(ptr)) {}

        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_t, T>::value>>
        supervisor(T* ptr)
            : ptr_(ptr) {}

        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_t, T>::value>>
        supervisor& operator=(detail::intrusive_ptr<T> ptr) {
            supervisor tmp{std::move(ptr)};
            swap(tmp);
            return *this;
        }

        template<
            class T,
            class = type_traits::enable_if_t<std::is_base_of<supervisor_t, T>::value>>
        supervisor& operator=(T* ptr) {
            supervisor tmp{ptr};
            swap(tmp);
            return *this;
        }

        actor_address address() const noexcept;

        ~supervisor();

        inline supervisor_t* operator->() const noexcept {
            return ptr_.get();
        }

        inline supervisor_t* get() const noexcept {
            return ptr_.get();
        }

        inline explicit operator bool() const noexcept {
            return static_cast<bool>(ptr_);
        }

        auto type() const -> detail::string_view;

        inline bool operator!() const noexcept {
            return !ptr_;
        }

    private:
        void swap(supervisor&) noexcept;

        detail::intrusive_ptr<supervisor_t> ptr_;
    };

}} // namespace actor_zeta::base