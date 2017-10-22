#include "actor-zeta/environment/abstract_group.hpp"
#include "actor-zeta/environment/group.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace environment {
        auto abstract_group::type() const -> const std::string & {
            return type_;
        }

        auto abstract_group::id() const -> id_t {
            return entry_point_;
        }

        auto abstract_group::entry_point() -> actor::actor_address {
            return storage_space_.get(entry_point_);
        }

        void abstract_group::add(actor::abstract_actor *t) {
            if (!shared_point.empty()) {
                for (auto &i:shared_point) {
                    t->send(
                            std::move(
                                    messaging::make_message(
                                            t->address(),
                                            "sync_contacts",
                                            storage_space_.get(i)
                                    )
                            )
                    );
                }
            }
            auto index = storage_space_.add(t);
            storage_space_.create_link(entry_point_, index);
        }

        void abstract_group::add_shared(actor::abstract_actor *t) {
            actor::actor_address address = t->address();
            auto id = storage_space_.add(t);
            shared_point.push_back(id);
            storage_space_.get(entry_point_)->send(
                    std::move(
                            messaging::make_message(
                                    t->address(),
                                    "sync_contacts",
                                    actor::actor_address(address)
                            )
                    )
            );
            for (auto &i:storage_space_.current_layer(entry_point_)) {
                i->send(
                        std::move(
                                messaging::make_message(
                                        t->address(),
                                        "sync_contacts",
                                        actor::actor_address(address)
                                )
                        )
                );
            }
        }

        void abstract_group::join(group &g) {
            entry_point()->send(
                    std::move(
                            messaging::make_message(
                                    g->entry_point(),
                                    "sync_contacts",
                                    g->entry_point()
                            )
                    )
            );
            if (!storage_space_.current_layer(entry_point_).empty()) {
                for (auto &i:storage_space_.current_layer(entry_point_)) {
                    i->send(
                            std::move(
                                    messaging::make_message(
                                            g->entry_point(),
                                            "sync_contacts",
                                            g->entry_point()
                                    )
                            )
                    );
                }
            }
        }

        abstract_group::abstract_group(storage_space ss, actor::abstract_actor *t)
                : storage_space_(ss), type_(t->type()), cursor(0) {
            t->send(std::move(std::move(messaging::make_message(t->address(),"add_channel", channel()))));
            entry_point_ = ss.add(t);
        }

        auto abstract_group::channel() -> channel::channel {
            return channel::channel{static_cast<channel::abstract_channel *>(this)};
        }

        auto abstract_group::send(messaging::message&& msg) -> bool {
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
    }
}

