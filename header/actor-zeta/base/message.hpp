#pragma once

#include <cassert>

#include <string>

#include <actor-zeta/base/priority.hpp>
#include <actor-zeta/detail/rtt.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {

    ///
    /// @brief
    ///

    class message final {
    public:
        // https://github.com/duckstax/actor-zeta/issues/118
        // @TODO Remove default ctors for actor_zeta::base::message and actor_zeta::detail::rtt (message body) #118
        message();
        message(const message&) = delete;
        message& operator=(const message&) = delete;
        message(message&& other) = default;
        message& operator=(message&&) = default;
        ~message() = default;
        message(address_t /*sender*/, std::string /*name*/);
        message(address_t /*sender*/, std::string /*name*/, detail::rtt /*body*/);
        message* next;
        message* prev;
        auto command() const noexcept -> detail::string_view;
        auto sender() & noexcept -> address_t&;
        auto sender() && noexcept -> address_t&&;
        auto sender() const& noexcept -> address_t const&;

        auto body() -> detail::rtt&;
        auto clone() const -> message*;
        operator bool();
        void swap(message& other) noexcept;
        bool is_high_priority() const;

    private:
        address_t sender_;
        std::string command_;
        detail::rtt body_;
        priority priority_ = priority::normal;
    };

    static_assert(std::is_move_constructible<message>::value, "");
    static_assert(not std::is_copy_constructible<message>::value, "");

}} // namespace actor_zeta::base

inline void swap(actor_zeta::base::message& lhs, actor_zeta::base::message& rhs) noexcept {
    lhs.swap(rhs);
}
