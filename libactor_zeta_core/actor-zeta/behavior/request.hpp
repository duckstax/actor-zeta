#ifndef BEHAVIOR_REQUEST_HPP
#define BEHAVIOR_REQUEST_HPP

#include "actor-zeta/contacts/book_contacts.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace behavior {
        class request {
        private:
            contacts::book_contacts &contacts_;
            messaging::message *msg;
        public:

            request() = default;

            request(const request &) = default;

            request &operator=(const request &) = default;

            request(request &&) = default;

            request &operator=(request &&) = default;

            ~request() = default;

            request(contacts::book_contacts &contacts_, messaging::message *msg) : msg(msg), contacts_(contacts_) {}

            messaging::message *message() {
                return msg;
            };

            contacts::book_contacts &contacts() {
                return contacts_;
            }
        };
    }
}
#endif //REQUEST_HPP
