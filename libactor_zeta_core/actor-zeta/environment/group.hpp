#ifndef GROUP_HPP
#define GROUP_HPP

#include <unordered_map>
#include <string>
#include "actor-zeta/messaging/message.hpp"
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {
    namespace environment {
        class group {
        public:
            group() = default;

            group(const group &a) = delete;

            group(group &&) = default;

            group &operator=(const group &a) = delete;

            group &operator=(group &&) = default;

            group(actor::abstract_actor *);

            ~group() {};

            std::string name_entry_point() const;

            group &add(actor::actor &&);

            group &add(actor::abstract_actor *);

            group &add(const std::string &, actor::abstract_actor *);

            group &add_shared_address(actor::actor_address);

            void sync(std::initializer_list<std::string>);

            void sync();

            actor::actor_address address_entry_point();

            void async_send(messaging::message &&);

            void async_send_all(messaging::message &&);

            group &set_exeutor(const std::string &, abstract_coordinator *);

            group &set_exeutor_all(abstract_coordinator *);

        private:
            std::unordered_map<std::string, actor::actor> unique_actors;
            std::string entry_point;
        };


        template<class V>
        inline void send(actor_zeta::environment::group &g, std::string commanda, V value) {
            g.async_send(std::move(messaging::make_message(commanda, value)));
        }
    }
}
#endif //GROUP_HPP
