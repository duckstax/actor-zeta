#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <memory>

#include <actor-zeta/behavior/type_action.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/any.hpp>
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

            message(actor::actor_address /*sender*/, const std::string& /*name*/, any &&/*body*/);

            auto command() const noexcept -> const behavior::type_action &;

            auto sender() const -> actor::actor_address ;

            template<typename T>
            auto body() -> T {
                return get_body().get<T>();
            }

            auto clone() const -> message;

            operator bool();

        private:
            message(const message_header &header, const any &body);

            auto get_body() -> any &;

            struct impl;

            std::unique_ptr<impl> pimpl;
        };

        template <typename T>
        inline auto make_message(actor::actor_address sender_,const std::string &name, T &&data) -> message {
            return message(sender_,name, std::forward<T>(data));
        }

    }
}
#endif
