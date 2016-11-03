#ifndef WRITE_HPP
#define WRITE_HPP

#include "actor-zeta/network/multiplexer.hpp"
#include "actor-zeta/behavior/abstract_action.hpp"

namespace actor_zeta {
    namespace network {
        class write final : public behavior::abstract_action {
        public:
            write(std::shared_ptr<multiplexer>);

            void operator()(messaging::message *msg) override final;

        private:
            actor_zeta::network::shared_multiplexer_ptr multiplexer_;
        };
    }
}
#endif //WRITE_HPP
