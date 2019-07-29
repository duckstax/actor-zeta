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
            virtual ~abstract_environment()                       = default;

            virtual std::size_t                   start()         = 0;

            virtual executor::abstract_executor & get_executor()  = 0;

            actor::supervisor& manager_supervisor(detail::string_view name);

            template<typename Supervisor,typename... Args>
            auto supervisor(Args... args) -> Supervisor & {
                auto*supervisor = new Supervisor(std::forward<Args>(args)...);
                create_supervisor(supervisor);
                return *supervisor;
            }

            auto ghraht() -> detail::storage_space{
                return storage_space_;
            }

            virtual auto create_supervisor(actor::supervisor* ptr) -> actor::supervisor &;

        protected:
            std::unordered_map<detail::string_view, intrusive_ptr<actor_zeta::actor::supervisor>> supervisors;
            detail::storage_space storage_space_;
        };


///
/// @brief An actors workplace platform 
///

        class environment final {
        public:
            environment() = delete;

            environment(const environment &) = delete;

            environment &operator=(const environment &)= delete;

            environment(environment &&) = default;

            environment &operator=(environment &&)= default;

            ~environment();

            environment(abstract_environment *ptr);

            template<class T>
            environment &operator=(T *ptr) {
                environment tmp{ptr};
                swap(tmp);
                return *this;
            }

            auto operator->() noexcept -> abstract_environment *;

            auto get() noexcept  -> abstract_environment*;

            explicit operator bool() const noexcept;

            bool operator!() const noexcept;

        private:

            void swap(environment &) noexcept;

            std::unique_ptr<abstract_environment> environment_;
        };

        template<typename Env, typename... Args>
        inline auto make_environment(Args... args) -> environment {
            return new Env(std::forward<Args>(args)...);
        }

    } /// environment
} /// actor_zeta
