#pragma once
#include <utility>

#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/rtt_message.hpp>

namespace actor_zeta { namespace base {

    auto rtt_message::command() const noexcept -> detail::string_view {
        return detail::string_view(command_.data(), command_.size());
    }

    auto rtt_message::clone() const -> rtt_message* {
        return new rtt_message(sender_, command_, body_);
    }

    rtt_message::operator bool() {
        return !command_.empty() || bool(sender_) || !body_.empty();
    }

    rtt_message::rtt_message(address_t sender, std::string name)
        : sender_(std::move(sender))
        , command_(std::move(name))
        , body_() {}

    rtt_message::rtt_message(address_t sender, std::string name, detail::rtt body)
        : sender_(std::move(sender))
        , command_(std::move(name))
        , body_(std::move(body)) {}

    void rtt_message::swap(rtt_message& other) noexcept {
        using std::swap;
        swap(sender_, other.sender_);
        swap(command_, other.command_);
        swap(body_, other.body_);
    }

    rtt_message::rtt_message()
        : next(nullptr)
        , prev(nullptr)
        , sender_(address_t::empty_address()) {}

    bool rtt_message::is_high_priority() const {
        return false;
    }

    auto rtt_message::body() -> detail::rtt& {
        assert(!body_.empty());
        return body_;
    }

    auto rtt_message::sender() & noexcept -> address_t& {
        return sender_;
    }

    auto rtt_message::sender() && noexcept -> address_t&& {
        return std::move(sender_);
    }

    auto rtt_message::sender() const& noexcept -> address_t const& {
        return sender_;
    }

}} // namespace actor_zeta::base
