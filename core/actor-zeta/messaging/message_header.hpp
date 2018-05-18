#ifndef MESSAGING_MESSAGE_HEADER_HPP
#define MESSAGING_MESSAGE_HEADER_HPP

#include <actor-zeta/behavior/type_action.hpp>
#include <actor-zeta/messaging/message_priority.hpp>
#include <actor-zeta/actor/actor_address.hpp>

namespace actor_zeta {
    namespace messaging {
///
/// @brief
///
        class message_header final {
        public:
            message_header() = default;

            message_header(const message_header &) = default;

            message_header &operator=(const message_header &) = default;

            message_header(message_header &&) noexcept = default;

            message_header &operator=(message_header &&) noexcept = default;

            ~message_header() = default;

            message_header(actor::actor_address sender_, const std::string& name);

            message_header(actor::actor_address sender_, const std::string& name, message_priority p);

            auto  priorities() const -> message_priority;

            auto command() const noexcept -> const behavior::type_action &;

            auto sender() const -> actor::actor_address ;

        private:
            actor::actor_address sender_;
            behavior::type_action command_;
            message_priority prioritie;
        };
    }
}
#endif //MESSAGE_HEADER_HPP
