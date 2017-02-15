#ifndef COOPERATION_HPP
#define COOPERATION_HPP

#include <unordered_map>
#include <string>
#include <vector>

#include "actor-zeta/messaging/message.hpp"
#include "group.hpp"
#include "shared_group.hpp"

// TODO:  cooperation(*) <- abstract_cooperation

namespace actor_zeta {
    namespace environment {
        class cooperation {
        public:
            cooperation() = default;

            cooperation(const cooperation &a) = delete;

            cooperation(cooperation &&) = default;

            cooperation &operator=(const cooperation &a) = delete;

            cooperation &operator=(cooperation &&) = default;

            ~cooperation() = default;

            void add(group &&);

            actor_zeta::actor::actor_address get(const std::string &) const;

            void send(messaging::message *);

            void send_current(const std::string &, messaging::message *);

            void send_all(messaging::message *);

            void add_shared(actor::abstract_actor *);

        private:
            std::string entry_point;
            std::unordered_map<std::string, group> cooperation_groups;
            shared_group shared_group_;
        };


        template<class V>
        inline void send(actor_zeta::environment::cooperation &c, std::string commanda, V value) {
            c.send(std::move(messaging::make_message(commanda, value)));
        }
    }
}
#endif //COOPERATION_HPP
