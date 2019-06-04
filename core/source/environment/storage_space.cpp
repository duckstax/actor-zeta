#include <actor-zeta/environment/storage_space.hpp>
#include <unordered_map>

#include <actor-zeta/actor/abstract_actor.hpp>
#include <actor-zeta/detail/adjacency_list.hpp>
#include <actor-zeta/actor/actor.hpp>


namespace actor_zeta { namespace environment {

        using registry = detail::adjacency_list<detail::stored_vertex, detail::node>;

        class storage final {
        public:

            storage() = default;

            storage(const storage &) = default;

            storage &operator=(const storage &) = default;

            storage(storage &&) = default;

            storage &operator=(storage &&) = default;

            ~storage() = default;

            auto add(actor::abstract_actor *object) -> id_t {
                id_t id = inc();
                body.emplace(id, actor::actor(object));
                return id;
            }

            auto get_actor(id_t id) -> actor::actor_address {
                return body.at(id).address();
            }


        private:
            auto inc() -> id_t {
                id_t tmp = counter;
                ++counter;
                return tmp;
            }

            id_t counter{0};
            std::unordered_map<id_t, actor::actor> body;
        };

        class storage_space::impl final {
        public:
            impl() = default;

            ~impl() = default;

            storage actors;
            registry registry_;
        };

        storage_space::storage_space() : pimpl(new storage_space::impl) {}

        auto storage_space::add(actor::abstract_actor *t) -> id_t {
            auto index = pimpl->actors.add(t);
            pimpl->registry_.add_vertex(index);
            return index;
        }

        auto storage_space::create_link(id_t id, id_t id1) -> void {
            pimpl->registry_.add_edge(id, id1);
        }

        auto storage_space::get(id_t id) -> actor::actor_address {
            return pimpl->actors.get_actor(id);
        }

        auto storage_space::current_layer(id_t id) -> std::vector<actor::actor_address> {
            auto all_id_current_layer = pimpl->registry_.finding_adjacency(id);
            std::vector<actor::actor_address> tmp;
            tmp.reserve(tmp.size());
            for (auto &i:all_id_current_layer) {
                tmp.push_back(pimpl->actors.get_actor(i));
            }
            return tmp;
        }
    }
}
