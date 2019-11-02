#include <iostream>
#include <cassert>

#include <actor-zeta/actor/context.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/execution_device.hpp>
#include <actor-zeta/actor/supervisor.hpp>
#include <actor-zeta/actor/cooperative_actor.hpp>

namespace actor_zeta { namespace actor {

        inline void error(){
            std::cerr << " WARNING " << std::endl;
            std::cerr << " WRONG ADDRESS " << std::endl;
            std::cerr << " WARNING " << std::endl;
        }

        executor::executable_result cooperative_actor::run(executor::execution_device *e, size_t max_throughput) {
            attach(e);
            //---------------------------------------------------------------------------

            {

                messaging::message msg_ptr;
                for (size_t handled_msgs = 0; handled_msgs < max_throughput;) {
                    msg_ptr = pop_to_cache();
                    if (msg_ptr) {
                        {
                            dispatch().execute(*this); /** context processing */
                        }
                        ++handled_msgs;
                        continue;
                    }

                   next_message();
                    if (current_message()) {
                        {
                            dispatch().execute(*this); /** context processing */
                        }
                        ++handled_msgs;

                    } else {
                        return executor::executable_result::awaiting;
                    }
                }

            }

            //---------------------------------------------------------------------------

            next_message();
            while (current_message()) {
                push_to_cache(std::move(current_message()));
                next_message();
            }

            //---------------------------------------------------------------------------

            if (has_next_message()) {
                return executor::executable_result::awaiting;
            }

            return executor::executable_result::resume;
        }

        void cooperative_actor::enqueue(messaging::message mep, executor::execution_device *e) {
            mailbox().put(std::move(mep));
            /// add a reference count to this actor and coordinator it
            intrusive_ptr_add_ref(this);
            if (e != nullptr) {
                attach(e);
                attach()->execute(this);
            } else {
                env().executor().execute(this);
            }

        }


        void cooperative_actor::intrusive_ptr_add_ref_impl() {
            ref();
        }

        void cooperative_actor::intrusive_ptr_release_impl() {
            deref();
        }

        cooperative_actor::cooperative_actor(
                  supervisor &env
                , mailbox_type* mail_ptr
                , detail::string_view name
        )
                : executable_actor(env, name)
                , mailbox_(mail_ptr)
        {
        }

        /*
        void cooperative_actor::launch(executor::execution_device *e, bool hide) {
            attach(e);

            if (hide) {//TODO:???
                /// coordinator has a reference count to the actor as long as
                /// it is waiting to get scheduled
                intrusive_ptr_add_ref(this);
                attach()->execute(this);
            } else {
                auto max_throughput = std::numeric_limits<size_t>::max();
                while (run(attach(), max_throughput) != executor::executable_result::awaiting) {
                }
            }
        }
        */

        bool cooperative_actor::has_next_message() {
            messaging::message msg_ptr = mailbox().get();
            return push_to_cache(std::move(msg_ptr));
        }

        bool cooperative_actor::push_to_cache(messaging::message msg_ptr) {
            return mailbox().push_to_cache(std::move(msg_ptr));
        }

        messaging::message cooperative_actor::pop_to_cache() {
            return mailbox().pop_to_cache();
        }

        cooperative_actor::mailbox_type &cooperative_actor::mailbox() {
            return *mailbox_;
        }

        void cooperative_actor::next_message() {
           current_message_ =  mailbox().get();
        }

        cooperative_actor::~cooperative_actor(){

        }

        auto cooperative_actor::current_message() -> messaging::message & {
            return current_message_;
        }
    }
}

