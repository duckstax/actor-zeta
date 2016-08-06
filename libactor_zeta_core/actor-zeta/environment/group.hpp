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

            template<class T>
            group(const std::string &name, T* actor):name_(name) {
                std::string entry_address = actor->type();
                unique_actors.emplace(actor->type(), actor);
                entry_point = entry_address;
            }

            ~group() = default;

            std::string name_entry_point() const;

            group &add(actor::actor &&);

            template<class T>
            group &add(T* actor) {
                unique_actors.emplace(actor->type(), actor);
                return *this;
            };

            template <class T>
            group &add(const std::string &root_name, T * actor){
                actor_zeta::actor::actor_address address = actor->address();
                unique_actors.emplace(actor->type(), actor);
                unique_actors[root_name]->async_send(
                        messaging::make_message(
                                std::string("sync_contacts"),
                                address
                        )
                );
                return *this;
            }
            group &add_shared_address(actor::actor_address);

            void sync(std::initializer_list<std::string>);

            void sync();

            actor::actor_address address_entry_point() const;

            void async_send(messaging::message &&);

            void async_send_all(messaging::message &&);

            const std::string &name() const;

        private:
            const std::string name_;
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
