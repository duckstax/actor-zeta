#pragma once
#include <utility>

#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>

namespace actor_zeta { namespace mailbox {

    auto message::command() const noexcept -> message_id {
        return command_;
    }

    auto message::clone() const -> message* {
        return new message(sender_, command_, body_);
    }

    message::operator bool() {
        return bool(sender_) || body_.has_value();
    }

    message::message(address_t sender, message_id name)
        : sender_(std::move(sender))
        , command_(std::move(name))
        , body_() {}

    message::message(address_t sender, message_id name, detail::any body)
        : sender_(std::move(sender))
        , command_(std::move(name))
        , body_(std::move(body)) {}

    void message::swap(message& other) noexcept {
        using std::swap;
        swap(sender_, other.sender_);
        swap(command_, other.command_);
        swap(body_, other.body_);
    }

    message::message()
        : next(nullptr)
        , prev(nullptr)
        , sender_(address_t::empty_address())
    {}

    bool message::is_high_priority() const {
        return command_.category() == message_id::urgent_message_category;
    }

    auto message::body() -> detail::any& {
        assert(body_.has_value());
        return body_;
    }

    auto message::sender() & noexcept -> base::address_t& {
        return sender_;
    }

    auto message::sender() && noexcept -> base::address_t&& {
        return std::move(sender_);
    }

    auto message::sender() const& noexcept -> base::address_t const& {
        return sender_;
    }

}} // namespace actor_zeta::base
