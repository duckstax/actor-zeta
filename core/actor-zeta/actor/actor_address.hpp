#pragma once

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/actor/abstract_async_container.hpp>
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

            explicit actor_address(abstract_async_container *);

            ~actor_address();

            inline abstract_async_container *operator->() const noexcept {
                return ptr_.get();
            }

            inline  operator bool() const noexcept {
                return static_cast<bool>(ptr_);
            }

            inline  bool operator!() const noexcept {
                return !ptr_;
            }

        private:
            intrusive_ptr<abstract_async_container> ptr_;
        };

}}
