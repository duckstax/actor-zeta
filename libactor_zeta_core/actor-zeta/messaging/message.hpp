#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <memory>
#include "message_header.hpp"
#include "message_body.hpp"

namespace actor_zeta {
    namespace messaging {
///
/// @brief Class to represent messages 
///        
        class message final {
        public:
            message() = delete;

            message(const message &) = delete;

            message &operator=(const message &) = delete;

            message(message &&) = default;

            message &operator=(message &&) = default;

            ~message() = default;

            template<std::size_t N, typename T>
            message(const char(&aStr)[N], const T &t)
                    : header_(aStr), body_(t) {}

            template<std::size_t N, typename T>
            message(const char(&aStr)[N], const T &t, actor::actor_address aa)
                    : header_(aStr, aa), body_(t) {}

            template<std::size_t N, typename T>
            message(const char(&aStr)[N], const T &t, message_priority p)
                    :header_(aStr, p), body_(t) {}

            template<std::size_t N, typename T>
            message(const char(&aStr)[N], const T &t, message_priority p, actor::actor_address aa)
                    : header_(aStr, p, aa), body_(t) {}

            template<typename T>
            message(const char *str, std::size_t len, const T &t)
                    : header_(str, len), body_(t) {}

            template<typename T>
            message(const char *str, std::size_t len, const T &t, actor::actor_address aa)
                    : header_(str, len, aa), body_(t) {}

            template<typename T>
            message(const char *str, std::size_t len, const T &t, message_priority p)
                    :header_(str, len, p), body_(t) {}

            template<typename T>
            message(const char *str, std::size_t len, const T &t, message_priority p, actor::actor_address aa)
                    :header_(str, len, p, aa), body_(t) {}

            message_priority priority() const;

            auto type() const noexcept -> const behavior::type_action &;

            actor::actor_address return_address() const;

            bool is_callback() const;

            template<typename T>
            auto get() -> T {
                return body_.get<T>();
            }

            auto clone() const -> message * {
                return new message(body_, header_);
            }

        private:
            message(const message_body &body_, const message_header &header_);

            message_body body_;
            message_header header_;
        };

        template<std::size_t N, typename T>
        inline message *make_message(const char(&aStr)[N], T data) {
            return new message(aStr, data);
        }

        template<typename T>
        inline message *make_message(const std::string &type, T data) {
            return new message(type.c_str(), type.length(), data);
        }

        template<typename T>
        inline message *make_message(const std::string &type, T data, actor::actor_address address) {
            return new message(type.c_str(), type.length(), data, address);
        }

        template<std::size_t N, typename T>
        inline message *make_message(const char(&aStr)[N], T data, actor::actor_address address) {
            return new message(aStr, data, address);
        }
    }
}
#endif