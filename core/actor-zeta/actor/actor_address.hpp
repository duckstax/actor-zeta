#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/communication_module.hpp>
#include <actor-zeta/detail/intrusive_ptr.hpp>

namespace actor_zeta { namespace actor {
///
/// @brief A compact location expressor
///
        class actor_address final {
        public:
            actor_address() = default;

            actor_address(actor_address &&) = default;

            actor_address(const actor_address &) = default;

            actor_address &operator=(actor_address &&) = default;

            actor_address &operator=(const actor_address &) = default;

            explicit actor_address(communication_module *);

            ~actor_address();

            inline communication_module *operator->() const noexcept {
                return ptr_.get();
            }

            inline  operator bool() const noexcept {
                return static_cast<bool>(ptr_);
            }

            inline  bool operator!() const noexcept {
                return !ptr_;
            }

        private:
            intrusive_ptr<communication_module> ptr_;
        };

}}
