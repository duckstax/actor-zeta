#ifndef COOPERATION_HPP
#define COOPERATION_HPP

#include <map>
#include <string>
#include <vector>
#include "messaging/message.hpp"
#include "fwd.hpp"

namespace actor_model {
    class cooperation {
    public:
        cooperation() = default;

        cooperation(const cooperation &a) = delete;

        cooperation(cooperation &&) = default;

        cooperation &operator=(const cooperation &a) = delete;

        cooperation &operator=(cooperation &&) = default;

        ~cooperation() { };

        explicit cooperation(std::initializer_list<actor_address>);

        cooperation &add(const std::string &, abstract_actor *);

        cooperation &add(const std::string &, actor &&);

        cooperation &add(group &&);

        void sync(std::initializer_list<std::string>);

        void sync();

        void async_send(messaging::message &&);

        void async_send(const std::string &, messaging::message &&);

        void async_send_all(messaging::message &&);

        cooperation &set_exeutor(const std::string &, abstract_coordinator_ptr);

        cooperation &set_exeutor_all(abstract_coordinator_ptr);

        cooperation &put_sharet(actor_address);

    private:
        std::string entry_point;
        std::map<std::string, group> cooperation_groups;
        std::vector<actor_address> sharet_contacts;
    };


    template<class V>
    inline void send(actor_model::cooperation &c, std::string commanda, V value) {
        c.async_send(std::move(messaging::make_message(commanda, value)));
    }
}
#endif //COOPERATION_HPP
