#pragma once

#include <actor-zeta/forwards.hpp>
#include <unordered_map>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/detail/storage_space.hpp>
#include <actor-zeta/actor/supervisor.hpp>

namespace actor_zeta { namespace environment {
///
/// @brief
///

        class abstract_environment {
        public:
            virtual ~abstract_environment() = default;

            virtual std::size_t                   start()         = 0;

            virtual executor::abstract_executor & get_executor()  = 0;

            actor::supervisor& manager_supervisor(detail::string_view name);

            auto created_group(actor::abstract_actor *t) -> actor::supervisor &;

        protected:
            std::unordered_map<detail::string_view, intrusive_ptr<actor_zeta::actor::supervisor>> supervisors;
            detail::storage_space storage_space_;
        };

}}
