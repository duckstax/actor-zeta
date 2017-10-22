#ifndef BEHAVIOR_REQUEST_HPP
#define BEHAVIOR_REQUEST_HPP

#include "actor-zeta/contacts/book_contacts.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace behavior {
///
/// @brief Represents output message entity
///
        class request {
        public:

            request() = default;

            request(const request &) = delete;

            request &operator=(const request &) = delete;

            request(request &&);

            request &operator=(request &&);

            ~request();

            request(contacts::book_contacts &, messaging::message&&);

            messaging::message message();

            contacts::book_contacts &contacts();

            operator bool();

        private:
            struct impl;
            std::unique_ptr<impl>pimpl;
        };
    }
}
#endif //REQUEST_HPP
