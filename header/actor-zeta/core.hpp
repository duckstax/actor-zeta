#pragma once

// clang-format off
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/base/actor_abstract.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on

#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/scheduler/policy/work_sharing.hpp>
#include <actor-zeta/scheduler/scheduler.hpp>
#include <actor-zeta/mailbox/id.hpp>
#include <actor-zeta/base/cooperative_actor.hpp>

namespace actor_zeta {

    using base::actor_abstract;
    using base::address_t;
    using base::cooperative_supervisor;
    using base::make_handler;
    using base::supervisor_abstract;
    using base::basic_actor;
    using base::behavior_t;
    using base::make_behavior;
    using base::actor_t;
    using base::supervisor_t;

    using mailbox::message;
    using mailbox::message_ptr;
    using mailbox::message_id;
    using mailbox::make_message_id;

    using scheduler::execution_unit;
    using scheduler::scheduler_abstract_t;
    using scheduler::scheduler_t;
    using scheduler::work_sharing;

/*
    template<
        class T,
        class = type_traits::enable_if_t<std::is_base_of<actor_abstract, T>::value>>
    actor_t make_actor(intrusive_ptr<T> ptr){

    }

    template<
        class T,
        class = type_traits::enable_if_t<std::is_base_of<actor_abstract, T>::value>>
    actor_t make_actor(T* ptr){

    }


    template<
        class T,
        class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract, T>::value>>
    supervisor_t make_supervisor(intrusive_ptr<T> ptr){

    }

    template<
        class T,
        class = type_traits::enable_if_t<std::is_base_of<supervisor_abstract, T>::value>>
    supervisor_t make_supervisor(T* ptr){

    }
*/
} // namespace actor_zeta
