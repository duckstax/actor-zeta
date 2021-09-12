#pragma once

#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
    ///
    /// @brief A compact location expressor
    ///
    class address_t final {
    public:
        address_t() noexcept;

        address_t(address_t&& other) noexcept;

        address_t(const address_t& other);

        address_t& operator=(address_t&& other) noexcept;

        address_t& operator=(const address_t& other);

        ~address_t();

        explicit address_t(actor_abstract*);

        explicit address_t(supervisor_abstract*);

        address_t(std::nullptr_t) noexcept;

        auto enqueue(message_ptr) noexcept -> void;

        auto type() const -> detail::string_view;

        operator bool() const noexcept;

        auto operator!() const noexcept -> bool;

        void swap(address_t& other);

        void* get() const;

    private:
        communication_module* ptr_;
    };

    const static auto empty_address  = address_t();

    static_assert(std::is_default_constructible<address_t>::value, "");
    static_assert(std::is_move_constructible<address_t>::value, "");
    static_assert(std::is_move_assignable<address_t>::value, "");
    static_assert(std::is_copy_constructible<address_t>::value, "");
    static_assert(std::is_copy_assignable<address_t>::value, "");

}} // namespace actor_zeta::base
