#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {
    namespace behavior {

        struct response::impl final {

            impl() = default;
            impl(impl&&)= default;
            impl&operator=(impl&&)= default;
            impl(const impl &t) = delete;
            impl &operator=(const impl &t) = delete;
            ~impl() = default;

            impl(actor::actor_address address, messaging::message &&message) {}

            actor::actor_address receiver_;
            messaging::message msg;
        };


        response::operator bool(){
            return !pimpl;
        }


        messaging::message response::message() {
            auto tmp = std::move(pimpl->msg);
            return tmp;
        }

        response::response(actor::actor_address receiver_, messaging::message&&msg) :pimpl(new impl(receiver_,std::move(msg))) {}

        actor::actor_address response::receiver() const {
            return pimpl->receiver_;
        }

        response::~response() = default;

        response::response()  = default;

        response &response::operator=(response &&) = default;

        response::response(response &&)  = default;
    }
}

