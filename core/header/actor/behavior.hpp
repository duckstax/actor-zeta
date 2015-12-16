#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <map>
#include <functional>
#include <iostream>
#include <vector>
#include "fwd.hpp"

namespace actor_model {

    class behavior {
    public:

        using action=std::function<void(actor_model::book_contacts &, messaging::message &&)>;

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
