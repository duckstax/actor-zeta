#ifndef GROUP_HPP
#define GROUP_HPP

#include <unordered_map>
#include <string>

#include "actor-zeta/forwards.hpp"
#include "actor-zeta/actor/actor.hpp"
#include "shared_group.hpp"

// TODO:  groupt(*) <- abstract_group

namespace actor_zeta {
    namespace environment {
        class group {
        public:
            group() = default;

            group(const group &) = delete;

            group(group &&) = default;

            group &operator=(const group &) = delete;

            group &operator=(group &&) = default;

            group(const std::string &name, actor::abstract_actor* actor);

            ~group() = default;

            void add(actor::actor &&);

            void add(actor::abstract_actor*);

            void add(const std::string &, actor::abstract_actor *);

            void add_shared(actor::abstract_actor*);

            actor::actor_address entry_point() const;

            void send(messaging::message *);

            void send_current(const std::string&, messaging::message *);

            void send_all(messaging::message *);

            const std::string &name() const;

        private:
            const std::string name_;
            std::unordered_map<std::string, actor::actor> unique_actors;
            shared_group shared_group_;
            std::string name_entry_point;
        };

    }
}
#endif //GROUP_HPP
