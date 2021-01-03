#include <utility>

#include <actor-zeta/base/address_type.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/messaging/message_header.hpp>

namespace actor_zeta { namespace messaging {

        auto message_header::command() const noexcept -> detail::string_view {
            return command_;
        }

        message_header::message_header(base::address_type sender_, detail::string_view name)
                :sender_(std::move(sender_)), command_(name) {}

        auto message_header::sender() const -> base::address_type {
            return sender_;
        }

        message_header::operator bool() {
            return !command_.empty() || bool(sender_);
        }

    }}