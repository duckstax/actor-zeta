#include <actor-zeta/supervisor_heavy.hpp>

#include <cassert>

#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/environment.hpp>

namespace actor_zeta { namespace environment {

        void supervisor_heavy::join(supervisor &g) {
            address()->enqueue(
                    messaging::make_message(
                            g.address(),
                            "sync_contacts",
                            g.address()
                    )
            );
            if (!storage_space_.current_layer(entry_point_).empty()) {
                for (auto &i:storage_space_.current_layer(entry_point_)) {
                    i->enqueue(
                            messaging::make_message(
                                    g.address(),
                                    "sync_contacts",
                                    g.address()
                            )
                    );
                }
            }
        }

        auto supervisor_heavy::join(actor::base_actor *t) -> actor_zeta::actor::actor_address {
            /*
            if (!shared_point.empty()) {
                for (auto &i:shared_point) {
                    t->enqueue(
                            messaging::make_message(
                                    t->address(),
                                    "sync_contacts",
                                    storage_space_.get(i)
                            )
                    );
                }
            }
            */
            auto index = storage_space_.add(t);
            storage_space_.create_link(entry_point_, index.first);
            return index.second;
        }

        auto supervisor_heavy::broadcast(message msg) -> bool {
            auto tmp_address = storage_space_.current_layer(entry_point_);
            if (!tmp_address.empty()) {
                for(auto& i : tmp_address){
                    i->enqueue(msg.clone());
                }
                return true;
            }
            return false;
        }

        auto supervisor_heavy::id() const -> id_t {
            return entry_point_;
        }

        void supervisor_heavy::add_shared(const actor::actor_address &address) {
            /*actor::enqueue(
                    storage_space_.get(entry_point_),
                    address,
                    "sync_contacts",
                    actor::actor_address(address)
            );
            */

            storage_space_.get(entry_point_)->enqueue(
                    messaging::make_message(
                            address,
                            "sync_contacts",
                            actor::actor_address(address)
                    )
            );
            
            for (auto &i:storage_space_.current_layer(entry_point_)) {
                i->enqueue(
                        messaging::make_message(
                                address,
                                "sync_contacts",
                                actor::actor_address(address)
                        )
                );
            }
        }

        supervisor_heavy::supervisor_heavy(abstract_environment*env,char const*name)
            : supervisor(detail::string_view(name))
            , cursor(0)
            , storage_space_(env->graph())
            , env_(env)
        {
        }

        auto supervisor_heavy::shutdown() noexcept -> void {

        }

        auto supervisor_heavy::startup() noexcept -> void {

        }

        auto supervisor_heavy::executor() noexcept -> executor::abstract_executor & {
            return env_->executor();
        }

        void supervisor_heavy::enqueue(messaging::message msg, executor::execution_device *) {
            auto tmp_address = storage_space_.current_layer(entry_point_);
            if (!tmp_address.empty()) {
                tmp_address[cursor]->enqueue(std::move(msg));
                ++cursor;
                if (cursor >= tmp_address.size()) {
                    cursor = 0;
                }
            }
            assert(false);
        }

}}