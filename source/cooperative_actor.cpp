#include <iostream>
#include <cassert>

// clang-format off
#include <address_t.hpp>
#include <message.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/executor/execution_device.hpp>
#include <abstract_supervisor.hpp>
#include <cooperative_actor.hpp>
// clang-format on

namespace actor_zeta {

        inline void error(){
            std::cerr << " WARNING " << std::endl;
            std::cerr << " WRONG ADDRESS " << std::endl;
            std::cerr << " WARNING " << std::endl;
        }

        executor::executable_result cooperative_actor::run(executor::execution_device *e, size_t max_throughput) {
            executor_ = e;
            //---------------------------------------------------------------------------

            {

                message msg_ptr;
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

        void cooperative_actor::enqueue_base(message msg, executor::execution_device *e) {
            mailbox().put(std::move(msg));
            if (e != nullptr) {
                executor_ = e;
                executor_->execute(this);
            } else {
                supervisor_->executor().execute(this);
            }

        }

        cooperative_actor::cooperative_actor(
            supervisor env
            , detail::string_view name
        )
                : abstract_actor(name)
                , mailbox_(new mailbox_type())
                , supervisor_(env)
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

        auto cooperative_actor::has_next_message() -> bool {
            message msg_ptr = mailbox().get();
            return push_to_cache(std::move(msg_ptr));
        }

        auto cooperative_actor::push_to_cache(message msg_ptr) -> bool {
            return mailbox().push_to_cache(std::move(msg_ptr));
        }

        auto cooperative_actor::pop_to_cache() -> message {
            return mailbox().pop_to_cache();
        }

        auto cooperative_actor::mailbox() -> cooperative_actor::mailbox_type & {
            return *mailbox_;
        }

        void cooperative_actor::next_message() {
           current_message_ =  mailbox().get();
        }

        cooperative_actor::~cooperative_actor(){

        }

        auto cooperative_actor::current_message() -> message & {
            return current_message_;
        }
    }

