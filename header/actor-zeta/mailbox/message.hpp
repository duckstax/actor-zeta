#pragma once

#include <cassert>

#include <actor-zeta/base/address.hpp>

#include <actor-zeta/base/forwards.hpp>
#include <actor-zeta/mailbox/priority.hpp>
#include <actor-zeta/detail/rtt.hpp>
#include <actor-zeta/mailbox/id.hpp>

namespace actor_zeta { namespace mailbox {

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
        message(base::address_t /*sender*/, message_id /*name*/);
        message(base::address_t /*sender*/, message_id /*name*/, detail::rtt /*body*/);
        message* next;
        message* prev;
        auto command() const noexcept -> message_id;
        auto sender() & noexcept -> base::address_t&;
        auto sender() && noexcept -> base::address_t&&;
        auto sender() const& noexcept -> base::address_t const&;

        auto body() -> detail::rtt&;
        auto clone() const -> message*;
        operator bool();
        void swap(message& other) noexcept;
        bool is_high_priority() const;

    private:
        base::address_t sender_;
        message_id command_;
        detail::rtt body_;
    };

    static_assert(std::is_move_constructible<message>::value, "");
    static_assert(not std::is_copy_constructible<message>::value, "");

    using message_ptr = std::unique_ptr<message>;

}} // namespace actor_zeta::mailbox

inline void swap(actor_zeta::mailbox::message& lhs, actor_zeta::mailbox::message& rhs) noexcept {
    lhs.swap(rhs);
}
