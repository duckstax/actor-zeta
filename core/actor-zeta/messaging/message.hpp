#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <memory>

#include <actor-zeta/behavior/type_action.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message_body.hpp>
#include <actor-zeta/messaging/message_priority.hpp>
#include <actor-zeta/messaging/message_header.hpp>

namespace actor_zeta {
    namespace messaging {
///
/// @brief
///
        class message final {
        public:
            message();

            message(const message &) = delete;

            message &operator=(const message &) = delete;

            message(message &&) noexcept ;

            message &operator=(message &&) noexcept ;

            ~message();

            message(actor::actor_address /*sender*/, const std::string& /*name*/, message_body &&/*body*/);

            message(actor::actor_address /*sender*/, const std::string& /*name*/, message_body &&/*body*/, actor::actor_address /*address*/);

            message(actor::actor_address /*sender*/, const std::string& /*name*/, message_body &&/*body*/, message_priority /*priority*/);

            message(actor::actor_address /*sender*/, const std::string& /*name*/, message_body &&/*body*/, message_priority /*priority*/, actor::actor_address /*address*/);

            auto priority() const -> message_priority;

            auto command() const noexcept -> const behavior::type_action &;

            auto recipient() const -> actor::actor_address ;

            auto sender() const -> actor::actor_address ;

            auto is_callback() const -> bool;

            template<typename T>
            auto get() -> T {
                return get_body().get<T>();
            }

            auto clone() const -> message;

            operator bool();

        private:
            message(const message_header &header, const message_body &body);

            auto get_body() -> message_body &;

            struct impl;

            std::unique_ptr<impl> pimpl;
        };

        template <typename T>
        inline auto make_message(actor::actor_address sender_,const std::string &name, T &&data) -> message {
            return message(sender_,name, std::forward<T>(data));
        }

        template <typename T>
        inline auto make_message(actor::actor_address sender_,const std::string &name, T &&data, actor::actor_address address) -> message {
            return message(sender_,name, std::forward<T>(data), address);
        }
    }
}
#endif
