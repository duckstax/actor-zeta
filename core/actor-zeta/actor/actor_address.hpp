#ifndef ACTOR_ADDRESS_HPP
#define ACTOR_ADDRESS_HPP


#include <actor-zeta/intrusive_ptr.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/forwards.hpp>

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

            explicit actor_address(abstract_actor *aa);

            ~actor_address();

            inline abstract_actor *operator->() const noexcept {
                return ptr_.get();
            }

            inline explicit operator bool() const noexcept {
                return static_cast<bool>(ptr_);
            }

            inline bool operator!() const noexcept {
                return !ptr_;
            }

        private:
            intrusive_ptr<abstract_actor> ptr_;
        };

        inline void send(actor_address& address, messaging::message&& msg){
            address->send(std::move(msg));
        }

    }
}
#endif //ACTOR_ADDRESS_HPP
