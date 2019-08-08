#pragma once

#include <actor-zeta/actor/basic_actor.hpp>
#include <actor-zeta/actor/supervisor.hpp>

#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/executor.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>

namespace actor_zeta {

    using actor::context;
    using actor::basic_async_actor;
    using actor::actor_address;
    using actor::context;
    using actor::basic_async_actor;
    using actor::supervisor;

    using executor::executor_t;
    using executor::work_sharing;
    using executor::abstract_executor;
    using executor::executable;

    using actor::send;
    
}