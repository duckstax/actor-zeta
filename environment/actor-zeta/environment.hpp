#pragma once

#include <memory>
#include <unordered_map>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/detail/storage_space.hpp>
#include <actor-zeta/actor/supervisor.hpp>

namespace actor_zeta { namespace environment {
///
/// @brief
///

        class abstract_environment {
        public:
            virtual ~abstract_environment()                   = default;

            virtual std::size_t                   start()     = 0;

            virtual executor::abstract_executor & executor()  = 0;

            actor::supervisor& manager_supervisor(detail::string_view name);

            template<typename Supervisor,typename... Args>
            inline auto supervisor(Args&&... args) -> Supervisor* {
                auto*supervisor = new Supervisor(std::forward<Args>(args)...);
                create_supervisor(supervisor);
                return supervisor;
            }

            auto graph() -> detail::storage_space;

            auto create_supervisor(actor::supervisor* ptr) -> actor::supervisor &;

        protected:
            std::unordered_map<detail::string_view, intrusive_ptr<actor_zeta::actor::supervisor>> supervisors;
            detail::storage_space storage_space_;
        };


///
/// @brief An actors workplace platform 
///

        template<class Env, typename... Args>
        inline auto make_environment(Args... args) -> std::unique_ptr<abstract_environment> {
            return std::unique_ptr<abstract_environment>(new Env(std::forward<Args>(args)...));
        }

}} /// environment /// actor_zeta
