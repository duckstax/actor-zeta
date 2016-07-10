#ifndef COOPERATION_HPP
#define COOPERATION_HPP

#include <unordered_map>
#include <string>
#include <vector>

#include "actor-zeta/messaging/message.hpp"
#include "group.hpp"

namespace actor_zeta {
    namespace environment {

        class cooperation {
        public:
            cooperation() = default;

            cooperation(const cooperation &a) = delete;

            cooperation(cooperation &&) = default;

            cooperation &operator=(const cooperation &a) = delete;

            cooperation &operator=(cooperation &&) = default;

            ~cooperation() {};

            cooperation &add(group &&);

            void sync(std::initializer_list<std::string>);

            void sync();

            void async_send(messaging::message &&);

            void async_send(const std::string &, messaging::message &&);

            void async_send_all(messaging::message &&);

            cooperation &set_exeutor(const std::string &, abstract_coordinator *);

            cooperation &set_exeutor_all(abstract_coordinator *);

            cooperation &add_sharet_address(actor::actor_address);

        private:
            std::string entry_point;
            std::unordered_map<std::string, group> cooperation_groups;
        };


        template<class V>
        inline void send(actor_zeta::environment::cooperation &c, std::string commanda, V value) {
            c.async_send(std::move(messaging::make_message(commanda, value)));
        }
    }
}
#endif //COOPERATION_HPP
