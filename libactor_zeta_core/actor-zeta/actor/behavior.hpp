#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <map>
#include <functional>
#include <vector>
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {

    class behavior {
    public:

        using action=std::function<void(actor_zeta::book_contacts &, messaging::message &&)>;

        behavior() = default;

        behavior(behavior &&) = default;

        behavior(const behavior &) = default;

        behavior &operator=(behavior &&) = default;

        behavior &operator=(const behavior &) = default;

        behavior(std::initializer_list<std::pair<std::string, action >> handlers);

        void insert(std::string type, action &&f);

        void run(book_contacts &, messaging::message &&);

        //debug method
        void all_name_view();

    private:
        std::map<std::string, action> behavioral_reactions;
    };
}

#endif //BEHAVIOR_HPP
