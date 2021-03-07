#include <utility>

#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message_header.hpp>

namespace actor_zeta { namespace base {

        auto message_header::command() const noexcept -> detail::string_view {
            return detail::string_view(command_.data(),command_.size());
        }

        message_header::message_header(base::actor_address sender_, std::string name)
                :sender_(std::move(sender_)), command_(std::move(name)) {}

        auto message_header::sender() const -> base::actor_address {
            return sender_;
        }

        message_header::operator bool() {
            return !command_.empty() || bool(sender_);
        }

    }}