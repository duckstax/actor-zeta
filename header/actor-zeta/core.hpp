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
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/executor.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>

namespace actor_zeta {

    using base::actor;
    using base::actor_abstract;
    using base::address_t;
    using base::basic_async_actor;
    using base::make_handler;
    using base::supervisor;
    using base::supervisor_abstract;
    using base::message;
    using base::message_ptr;

    using executor::abstract_executor;
    using executor::executable;
    using executor::execution_device;
    using executor::executor_t;
    using executor::work_sharing;

} // namespace actor_zeta
