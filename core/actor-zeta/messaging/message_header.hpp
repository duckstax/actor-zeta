#pragma once

#include <actor-zeta/actor/type_action.hpp>
#include <actor-zeta/actor/actor_address.hpp>

namespace actor_zeta { namespace messaging {
///
/// @brief
///
        class message_header final {
        public:
            message_header() = default;

            message_header(const message_header &) = default;

            message_header &operator=(const message_header &) = default;

            message_header(message_header &&) = default;

            message_header &operator=(message_header &&) = default;

            ~message_header() = default;

            message_header(actor::actor_address sender_, const std::string& name);

            auto command() const noexcept -> const actor::type_action &;

            auto sender() const -> actor::actor_address ;

        private:
            actor::actor_address sender_;
            actor::type_action command_;
        };
    }
}
