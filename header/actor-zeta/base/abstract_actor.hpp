#pragma once

#include <actor-zeta/base/communication_module.hpp>
#include <actor-zeta/detail/control_block.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace base {
///
/// @brief Abstract concept of an actor
///

        class abstract_actor : public communication_module  {
        public:
            // allow placement new only
            void* operator new(std::size_t, void* ptr) {
                return ptr;
            }

            control_block<abstract_actor>* ctrl()  const {
                return from<abstract_actor>(this);
            }

            abstract_actor()= delete;



            ~abstract_actor() override;

            ///TODO:
            ///virtual void launch(executor::execution_device*, bool /*hide*/) = 0;
        protected:
            abstract_actor(detail::string_view);

            auto attach(executor::execution_device *) -> void;

            auto attach() const -> executor::execution_device* ;

            auto env() -> supervisor& ;

        private:
                // prohibit copies, assignments, and heap allocations
            void* operator new(size_t);
            void* operator new[](size_t);
            abstract_actor(const abstract_actor&) = delete;
            abstract_actor& operator=(const abstract_actor&) = delete;
        };

}}
