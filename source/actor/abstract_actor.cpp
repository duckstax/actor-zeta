#include <iostream>

// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/abstract_actor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

namespace actor_zeta { namespace base {

        abstract_actor::~abstract_actor() {

        }

        abstract_actor::abstract_actor(detail::string_view type)
                : communication_module(type, sub_type_t::actor)
                {
        }


}}
