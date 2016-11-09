#ifndef WRITE_HPP
#define WRITE_HPP

#include "actor-zeta/network/multiplexer.hpp"
#include "actor-zeta/behavior/abstract_action.hpp"

namespace actor_zeta {
    namespace network {
        class write final : public behavior::abstract_action {
        public:
            write(shared_multiplexer_ptr);

            behavior::response *operator()(behavior::request *) override final;

        private:
            shared_multiplexer_ptr multiplexer_;
        };
    }
}
#endif //WRITE_HPP
