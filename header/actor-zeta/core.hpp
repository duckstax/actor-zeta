#pragma once

// clang-format off
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/actor.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
// clang-format on

#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/scheduler/scheduler.hpp>
#include <actor-zeta/scheduler/policy/work_sharing.hpp>

namespace actor_zeta {

    using base::actor;
    using base::actor_abstract;
    using base::address_t;
    using base::basic_async_actor;
    using base::make_handler;
    using base::supervisor;
    using base::supervisor_abstract;
    using base::cooperative_supervisor;
    using base::message;
    using base::message_ptr;

    using scheduler::scheduler_abstract_t;
    using scheduler::scheduler_t;
    using scheduler::work_sharing;
    using scheduler::execution_unit;

} // namespace actor_zeta
