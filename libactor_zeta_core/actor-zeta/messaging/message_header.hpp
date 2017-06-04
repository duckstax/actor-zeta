#ifndef MESSAGING_MESSAGE_HEADER_HPP
#define MESSAGING_MESSAGE_HEADER_HPP

#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/behavior/type_action.hpp"
#include "message_priority.hpp"

namespace actor_zeta {
    namespace messaging {
///
/// @brief
///
        class message_header final {
        public:
            ///TODO: sender
            message_header() = delete;

            message_header(const message_header &) = default;

            message_header &operator=(const message_header &) = default;

            message_header(message_header &&) = default;

            message_header &operator=(message_header &&) = default;

            ~message_header() = default;

            template<std::size_t N>
            explicit message_header(const char(&aStr)[N])
                    : type_(aStr), prioritie(message_priority::normal), callback(false) {}

            template<std::size_t N>
            message_header(const char(&aStr)[N], actor::actor_address aa)
                    : type_(aStr), prioritie(message_priority::normal), callback(true), address(aa) {}

            template<std::size_t N>
            message_header(const char(&aStr)[N], message_priority p)
                    :type_(aStr), prioritie(p), callback(false) {}

            template<std::size_t N>
            message_header(const char(&aStr)[N], message_priority p, actor::actor_address aa)
                    : type_(aStr), prioritie(p), callback(true), address(aa) {}

            message_header(const char *str, std::size_t len);

            message_header(const char *str, std::size_t len, actor::actor_address aa);

            message_header(const char *str, std::size_t len, message_priority p);

            message_header(const char *str, std::size_t len, message_priority p, actor::actor_address aa);

            message_priority priorities() const;

            auto type() const noexcept -> const behavior::type_action &;

            actor::actor_address return_address() const;

            bool is_callback() const;

        private:
            bool callback;
            behavior::type_action type_;
            actor::actor_address address;
            message_priority prioritie;
        };
    }
}
#endif //MESSAGE_HEADER_HPP
