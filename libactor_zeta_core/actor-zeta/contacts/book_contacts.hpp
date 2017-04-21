#ifndef BOOKCONTACTS_HPP
#define BOOKCONTACTS_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "actor-zeta/actor/actor_address.hpp"
#include "actor-zeta/channel/channel.hpp"

namespace actor_zeta {
    namespace contacts {
///
/// @brief Navigation map for actor & groups
///
        class book_contacts final {
        public:
            book_contacts() = default;

            book_contacts(const book_contacts &) = delete;

            book_contacts &operator=(const book_contacts &)= delete;

            book_contacts(book_contacts &&) = default;

            book_contacts &operator=(book_contacts &&)= default;

            auto address(const actor::actor_address &) -> void;

            auto address(const std::string &) -> const actor::actor_address &;

            auto channel(channel::channel) -> void;

            auto channel(const std::string &) -> channel::channel;

            /*
            * debug method
            */
            auto all_view_address() -> void;

        private:
            std::unordered_map<std::string, actor::actor_address> contacts;
            std::unordered_map<std::string, channel::channel> channels;
        };
    }
}
#endif