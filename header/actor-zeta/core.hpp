#pragma once

// clang-format off
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/actor.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
// clang-format on

#include <actor-zeta/base/actor_schedule.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/detail/any.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>
#include <actor-zeta/scheduler/scheduler.hpp>
#include <actor-zeta/scheduler/policy/work_sharing.hpp>

namespace actor_zeta {

    using base::actor;
    using base::actor_abstract;
    using base::address_t;
    using base::supervisor;
    using base::supervisor_abstract;
    using base::cooperative_supervisor;
    using base::actor_schedule;
    using base::behavior_t;

    using base::message;
    using base::message_ptr;

    using scheduler::scheduler_abstract_t;
    using scheduler::execution_unit;
    using scheduler::scheduler_t;
    using scheduler::work_sharing;
    using scheduler::resumable;

} // namespace actor_zeta
