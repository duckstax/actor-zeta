#pragma once

// clang-format off
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/base/actor.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/scheduler/policy/work_sharing.hpp>
#include <actor-zeta/scheduler/scheduler.hpp>
#include <actor-zeta/mailbox/id.hpp>

namespace actor_zeta {

    using base::actor;
    using base::actor_abstract;
    using base::address_t;
    using base::basic_async_actor;

//    template<typename actor_traits>
//    using cooperative_supervisor = base::cooperative_supervisor<actor_traits>;

    using base::make_handler;
//    template<typename actor_traits>
//    using supervisor = base::supervisor<actor_traits>;

    //template<typename actor_traits>
    //using supervisor_abstract = base::supervisor_abstract<actor_traits>;

    using mailbox::message;
    using mailbox::message_ptr;
    using mailbox::message_id;
    using mailbox::make_message_id;

    using scheduler::execution_unit;
    using scheduler::scheduler_abstract_t;
    using scheduler::scheduler_t;
    using scheduler::work_sharing;

} // namespace actor_zeta
