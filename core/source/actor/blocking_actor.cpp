#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/blocking_actor.hpp>

namespace actor_zeta { namespace actor {

        executor::executable_result
        blocking_actor::run(executor::execution_device *e, size_t /*max_throughput*/) {

            attach(e);
            for (;;) {

                messaging::message msg_ptr = next_message();
                if (msg_ptr) {
                    dispatch().execute(*this);
                } else {
                    return executor::executable_result::done;
                }
            }
            return executor::executable_result::done;

        }
/*
        void blocking_actor::launch(executor::execution_device *e, bool hide) {
            attach(e);
            if (hide) {//TODO:???
                attach(e);
                attach()->execute(this);
            } else {
                this->run(e,std::numeric_limits<std::size_t>::max());
            }
        }
*/
        blocking_actor::blocking_actor(supervisor &env,mailbox_type* mail, detail::string_view type)
            : abstract_actor(env, type)
            , mailbox_(mail)
        {

        }

        messaging::message blocking_actor::next_message() {
            return mailbox().get();
        }

        blocking_actor::~blocking_actor() {}

        blocking_actor::mailbox_type &blocking_actor::mailbox() {
            return *mailbox_;
        }

    }
}
