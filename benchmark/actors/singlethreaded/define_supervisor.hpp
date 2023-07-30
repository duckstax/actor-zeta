#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <actor-zeta.hpp>

#include "enums.hpp"
#include "define_actor.hpp"

class supervisor_t final : public actor_zeta::cooperative_supervisor<supervisor_t> {
    using Actor = actor_t;
    std::map<name_t, actor_zeta::address_t> address_book_;
    std::map<name_t, Actor*> actors_;

public:
    supervisor_t(
        actor_zeta::pmr::memory_resource* resource)
        : actor_zeta::cooperative_supervisor<supervisor_t>(resource) {
    }

    auto make_type() const noexcept -> const char* const {
        return "collection";
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case actor_zeta::make_message_id(command_t::prepare): {
                        auto address_0 = spawn_actor([this](Actor* ptr) {
                            actors_.emplace(name_t::actor_0, ptr);
                        });
                        auto address_1 = spawn_actor([this](Actor* ptr) {
                            actors_.emplace(name_t::actor_1, ptr);
                        });
                        address_book_.emplace(name_t::actor_0, std::move(address_0));
                        address_book_.emplace(name_t::actor_1, std::move(address_1));

                        actor_zeta::send(address_book_.at(name_t::actor_0), address(), command_t::add_address, address_book_.at(name_t::actor_1), name_t::actor_1);
                        actor_zeta::send(address_book_.at(name_t::actor_1), address(), command_t::add_address, address_book_.at(name_t::actor_0), name_t::actor_0);

                        break;
                    }
                    case actor_zeta::make_message_id(command_t::send): {
                        assert(actors_.size() == 2);
                        actor_zeta::send(actors_.at(name_t::actor_0), address(), command_t::start);
                        //actors_.at(name_t::actor_0)->start();

                        break;
                    }
                    default: {
                        std::cerr << "unknown command" << std::endl;
                    }
                }
            });
    }

    auto make_scheduler() noexcept -> actor_zeta::scheduler_abstract_t* {
        return nullptr;
    }

protected:
    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        set_current_message(std::move(msg));
        behavior()(current_message());
    }
};
