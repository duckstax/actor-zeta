#ifndef WRITE_HPP
#define WRITE_HPP

#include "actor-zeta/network/multiplexer.hpp"
#include "actor-zeta/behavior/interface_action.hpp"

namespace actor_zeta {
    namespace network {
        class write final : public behavior::interface_action {
        public:
            write(std::shared_ptr<multiplexer> multiplexer_);

            void operator()(messaging::message *msg) override final;

            const std::string &name() const final;

        private:
            actor_zeta::network::shared_multiplexer_ptr multiplexer_;
            std::string name_;
        };
    }
}
#endif //WRITE_HPP
