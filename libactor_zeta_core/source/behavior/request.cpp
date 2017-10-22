#include "actor-zeta/behavior/request.hpp"


namespace actor_zeta {
    namespace behavior {
        struct request::impl final {
            impl() = default;
            impl(impl&&)= default;
            impl&operator=(impl&&)= default;
            impl(const impl &t) = delete;
            impl &operator=(const impl &t) = delete;
            ~impl() = default;

            impl(contacts::book_contacts &contacts, messaging::message &&message):contacts_(contacts),msg(std::move(message)) {}

            contacts::book_contacts &contacts_;
            messaging::message msg;
        };

        request::request(contacts::book_contacts &contacts_, messaging::message &&msg) :pimpl(new impl(contacts_,std::move(msg)) ){}

        messaging::message request::message() {
            auto tmp = std::move(pimpl->msg);
            return tmp;
        }

        contacts::book_contacts &request::contacts() {
            return pimpl->contacts_;
        }

        request::operator bool() {
            return !pimpl;
        }

        request &request::operator=(request &&)  = default;

        request::request(request &&)  = default;

        request::~request() = default;
    }
}

