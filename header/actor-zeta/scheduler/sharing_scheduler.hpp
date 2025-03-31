#pragma once

#include <cstddef>

#include <memory>

#include <actor-zeta/detail/memory.hpp>
#include <actor-zeta/detail/memory_resource.hpp>

namespace actor_zeta { namespace scheduler {

    std::unique_ptr<scheduler_t,pmr::deleter_t> make_sharing_scheduler(
        actor_zeta::pmr::memory_resource* /* resource */,
        std::size_t /*num_worker_threads*/,
        std::size_t /*max_throughput*/
    );

}} // namespace actor_zeta::scheduler
