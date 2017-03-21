#include <iostream>

#include "actor-zeta/contacts/book_contacts.hpp"
#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/channel/channel.hpp"

namespace actor_zeta {
    namespace contacts {

        auto book_contacts::address(const std::string &name) -> const actor::actor_address&  {
            return contacts.at(name);
        }

        auto book_contacts::address(const actor::actor_address &vc) -> void {
            contacts.emplace(vc->type(), vc);
        }

        auto book_contacts::all_view_address() -> void {
            for (auto &i: contacts)
                std::cout << i.first << std::endl;

        }

        auto book_contacts::channel(const std::string &name) ->channel::channel {
            return channels.at(name);
        }

        void book_contacts::channel(channel::channel channel_) {
            channels.emplace(channel_->type(),channel_);
        }
    }
}