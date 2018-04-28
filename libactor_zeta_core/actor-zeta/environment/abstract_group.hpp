#ifndef ABSTRACT_GROUP_HPP
#define ABSTRACT_GROUP_HPP

#include "storage_space.hpp"
#include "actor-zeta/channel/abstract_channel.hpp"
#include "actor-zeta/channel/channel.hpp"


namespace actor_zeta { namespace environment {

///
/// @brief
///
        //TODO: not correctly name abstract_group -> local_group ->group(*)
        class abstract_group : public channel::abstract_channel {
        public:
            abstract_group() = delete;

            abstract_group(const abstract_group &) = default;

            abstract_group &operator=(const abstract_group &)= default;

            abstract_group(abstract_group &&) = default;

            abstract_group &operator=(abstract_group &&)= default;

            ~abstract_group() = default;

            abstract_group(storage_space, actor::abstract_actor *);

            auto id() const -> id_t;

            auto entry_point() -> actor::actor_address;

            void add(actor::abstract_actor *);

            void add_shared(actor::abstract_actor *);

            void join(group &);

            auto channel() -> channel::channel;

            auto send(messaging::message &&msg) -> bool override final;

            auto broadcast(messaging::message &&msg) -> bool override final;

        private:
            std::size_t cursor;
            storage_space storage_space_;
            id_t entry_point_;
            layer shared_point;
        };
    }
}
#endif //ABSTRACT_GROUP_HPP
