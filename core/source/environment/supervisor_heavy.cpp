#include <actor-zeta/environment/supervisor_heavy.hpp>
#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/environment/abstract_environment.hpp>

namespace actor_zeta { namespace environment {

        void supervisor_heavy::join(supervisor &g) {
            entry_point()->send(
                    messaging::make_message(
                            g.entry_point(),
                            "sync_contacts",
                            g.entry_point()
                    )
            );
            if (!storage_space_.current_layer(entry_point_).empty()) {
                for (auto &i:storage_space_.current_layer(entry_point_)) {
                    i->send(
                            messaging::make_message(
                                    g.entry_point(),
                                    "sync_contacts",
                                    g.entry_point()
                            )
                    );
                }
            }
        }

        auto supervisor_heavy::entry_point() -> actor::actor_address {
            return storage_space_.get(entry_point_);
        }

        void supervisor_heavy::add(actor::abstract_actor *t) {
            if (!shared_point.empty()) {
                for (auto &i:shared_point) {
                    t->send(
                            messaging::make_message(
                                    t->address(),
                                    "sync_contacts",
                                    storage_space_.get(i)
                            )
                    );
                }
            }
            auto index = storage_space_.add(t);
            storage_space_.create_link(entry_point_, index);
        }

        auto supervisor_heavy::send(message msg) -> bool {
            auto tmp_address = storage_space_.current_layer(entry_point_);
            if (!tmp_address.empty()) {
                tmp_address[cursor]->send(std::move(msg));
                ++cursor;
                if (cursor >= tmp_address.size()) {
                    cursor = 0;
                }
                return true;
            }
            return false;
        }

        auto supervisor_heavy::broadcast(message msg) -> bool {
            auto tmp_address = storage_space_.current_layer(entry_point_);
            if (!tmp_address.empty()) {
                for(auto& i : tmp_address){
                    i->send(msg.clone());
                }
                return true;
            }
            return false;
        }

        auto supervisor_heavy::id() const -> id_t {
            return entry_point_;
        }

        void supervisor_heavy::add_shared(const actor::actor_address &address) {
            storage_space_.get(entry_point_)->send(
                    messaging::make_message(
                            address,
                            "sync_contacts",
                            actor::actor_address(address)
                    )
            );
            for (auto &i:storage_space_.current_layer(entry_point_)) {
                i->send(
                        messaging::make_message(
                                address,
                                "sync_contacts",
                                actor::actor_address(address)
                        )
                );
            }
        }

        supervisor_heavy::supervisor_heavy(abstract_environment*env,detail::storage_space ss, actor::abstract_actor *t):
            cursor(0),
            storage_space_(ss),env_(env) {
            entry_point_ = ss.add(t);
            type_.type = abstract::supervisor;
        }

        auto supervisor_heavy::shutdown() noexcept -> void {

        }

        auto supervisor_heavy::startup() noexcept -> void {

        }

        auto supervisor_heavy::executor() noexcept -> executor::abstract_executor & {
            return env_->get_executor();
        }

        bool supervisor_heavy::send(messaging::message, executor::execution_device *) {
            return false;
        }

}}