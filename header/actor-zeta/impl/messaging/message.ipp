#pragma once
#include <utility>

#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>

namespace actor_zeta { namespace base {

    auto message::command() const noexcept -> detail::string_view {
        return detail::string_view(command_.data(), command_.size());
    }

    auto message::clone() const -> message* {
        return new message(sender_, command_, body_);
    }

    message::operator bool() {
        return !command_.empty() || bool(sender_) || body_.has_value();
    }

    message::message(address_t sender, std::string name)
        : sender_(std::move(sender))
        , command_(std::move(name))
        , body_() {}

    message::message(address_t sender, std::string name, detail::any body)
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
        return false;
    }

    auto message::body() -> detail::any& {
        assert(body_.has_value());
        return body_;
    }

    auto message::sender() & noexcept -> address_t& {
        return sender_;
    }

    auto message::sender() && noexcept -> address_t&& {
        return std::move(sender_);
    }

    auto message::sender() const& noexcept -> address_t const& {
        return sender_;
    }

}} // namespace actor_zeta::base
