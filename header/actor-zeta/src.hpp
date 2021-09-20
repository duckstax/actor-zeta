#pragma once

// clang-format off
#include <actor-zeta.hpp>

#include <cstdint>
#include <actor-zeta/detail/impl/pmr/default_resource.ipp>
#include <actor-zeta/detail/pmr/polymorphic_allocator.hpp>

#include <actor-zeta/impl/actor/actor.ipp>
#include <actor-zeta/impl/actor/actor_abstract.ipp>
#include <actor-zeta/impl/actor/address.ipp>
#include <actor-zeta/impl/actor/communication_module.ipp>
#include <actor-zeta/impl/actor/cooperative_actor.ipp>
#include <actor-zeta/impl/actor/supervisor.ipp>
#include <actor-zeta/impl/actor/supervisor_abstract.ipp>

#include <actor-zeta/impl/detail/pmr/memory_resource.ipp>
#include <actor-zeta/impl/detail/aligned_allocate.ipp>
#include <actor-zeta/impl/detail/ref_counted.ipp>
#include <actor-zeta/impl/detail/string_view.ipp>

#include <actor-zeta/impl/executor/abstract_executor.ipp>
#include <actor-zeta/impl/executor/executable.ipp>
#include <actor-zeta/impl/executor/execution_device.ipp>
#include <actor-zeta/impl/executor/work_sharing.ipp>

#include <actor-zeta/impl/messaging/message.ipp>

#include <actor-zeta/impl/link.ipp>
#include <actor-zeta/impl/send.ipp>
// clang-format on