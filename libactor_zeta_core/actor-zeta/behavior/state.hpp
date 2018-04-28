#ifndef ACTOR_ZETA_STATE_HPP
#define ACTOR_ZETA_STATE_HPP

#include <stack>
#include <cstdint>
#include <actor-zeta/messaging/message.hpp>


namespace actor_zeta { namespace behavior {

        struct state_t final {

            state_t() = default;

            ~state_t() = default;

            state_t(messaging::message &&msg);

            messaging::message message();

            const messaging::message& message() const;

        private:
            messaging::message msg;

        };


    } /// behavior
} /// actor_zeta
#endif //ACTOR_ZETA_STATE_HP
