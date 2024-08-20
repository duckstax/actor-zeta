#pragma once

#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/scheduler/scheduler_abstract.hpp>
#include <actor-zeta/detail/memory_resource.hpp>

namespace actor_zeta { namespace test {

    class supervisor_abstract: public actor_zeta::base::actor_abstract{
    public:
        auto scheduler() noexcept -> scheduler::scheduler_abstract_t*;
        auto resource() const noexcept -> pmr::memory_resource*;

    protected:
        virtual auto scheduler_impl() noexcept -> scheduler::scheduler_abstract_t* = 0;
        virtual auto resource_impl() const noexcept -> pmr::memory_resource* = 0;
    };

}} // namespace actor_zeta::base
