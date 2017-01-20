#ifndef GROUP_HPP
#define GROUP_HPP

#include <unordered_map>
#include <string>

#include "actor-zeta/forwards.hpp"
#include "actor-zeta/actor/actor.hpp"

// TODO:  groupt(*) <- abstract_group

namespace actor_zeta {
    namespace environment {
        class group {
        public:
            group() = default;

            group(const group &a) = delete;

            group(group &&) = default;

            group &operator=(const group &a) = delete;

            group &operator=(group &&) = default;

            group(const std::string &name, actor::abstract_actor* actor);

            ~group() = default;

            std::string name_entry_point() const;

            void add(actor::actor &&);

            void add(actor::abstract_actor* actor);

            void add(const std::string &, actor::abstract_actor *);

            void add_shared_address(actor::actor_address);

            void sync(std::initializer_list<std::string>);

            void sync();

            actor::actor_address address_entry_point() const;

            void send(messaging::message *);

            void send_all(messaging::message *);

            const std::string &name() const;

        private:
            const std::string name_;
            std::unordered_map<std::string, actor::actor> unique_actors;
            std::string entry_point;
        };

    }
}
#endif //GROUP_HPP
