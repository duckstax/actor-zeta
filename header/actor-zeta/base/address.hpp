#pragma once

#include "forwards.hpp"
#include <type_traits>

namespace actor_zeta { namespace base {
    ///
    /// @brief A compact location expressor
    ///
    class address_t final {
    public:
        address_t(address_t&& other) noexcept;
        address_t(const address_t& other);
        address_t& operator=(address_t&& other) noexcept;
        address_t& operator=(const address_t& other);
        bool operator==(const address_t& rhs) noexcept;
        ~address_t() noexcept;
        explicit address_t(actor_abstract*);
        explicit address_t(supervisor_abstract*);
        static auto empty_address() -> address_t;

        inline actor_abstract* operator->() const noexcept {
            return ptr_;
        }

        operator bool() const noexcept;
        auto operator!() const noexcept -> bool;
        void swap(address_t& other);
        actor_abstract* get() const;

    private:
        address_t() noexcept;
        actor_abstract* ptr_;
    };

    bool operator==(const address_t& lhs, const address_t& rhs) noexcept;

    static_assert(!std::is_default_constructible<address_t>::value, "");
    static_assert(std::is_move_constructible<address_t>::value, "");
    static_assert(std::is_move_assignable<address_t>::value, "");
    static_assert(std::is_copy_constructible<address_t>::value, "");
    static_assert(std::is_copy_assignable<address_t>::value, "");

}} // namespace actor_zeta::base
