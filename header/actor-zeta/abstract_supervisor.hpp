#pragma once

#include <actor-zeta/forwards.hpp>
#include <communication_module.hpp>
#include <actor-zeta/message.hpp>

namespace actor_zeta {

    class supervisor;

    class abstract_supervisor : public communication_module {
    public:
        abstract_supervisor(detail::string_view);

        abstract_supervisor(supervisor, detail::string_view);

        ~abstract_supervisor() override;

        virtual auto executor() noexcept -> executor::abstract_executor& = 0;

        virtual auto join(actor) -> address_t = 0;

        virtual auto join(supervisor) -> address_t = 0;

        using communication_module::broadcast;

        auto address() -> address_t {
            return address_t(this);
        }

        auto enqueue(message) -> void;

        void enqueue(message, executor::execution_device*);

    protected:
        auto set_current_message(message) -> void;
        auto current_message() -> message&;

        virtual void enqueue_base(message, executor::execution_device*) = 0;

    private:
        message current_message_;
    };


        template<class T>
        auto spawn() -> void {

        }

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

        address_t address() const noexcept;

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

    private:
        void swap(supervisor&) noexcept;

        std::unique_ptr<abstract_supervisor> ptr_;
    };

} // namespace actor_zeta::base