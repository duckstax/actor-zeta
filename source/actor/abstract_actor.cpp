#include <iostream>

// clang-format off
#include <actor-zeta/base/context.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/abstract_actor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta { namespace base {

        abstract_actor::~abstract_actor() {

        }

        abstract_actor::abstract_actor(
                supervisor_t *env,
                detail::string_view name
        )
                : communication_module(name, abstract::actor)
                , supervisor_(env){
        }

        executor::execution_device *abstract_actor::context() const {
            return executor_;
        }

        void abstract_actor::context(executor::execution_device *e) {
            if (e!= nullptr) {
                executor_ = e;
            }
        }

        auto abstract_actor::supervisor() -> supervisor_t* {
            return supervisor_;
        }


}}
