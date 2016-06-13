#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include "actor-zeta/forwards.hpp"

namespace actor_zeta {

    struct abstract_action {
        virtual void operator()(messaging::message &&msg)=0;

        virtual ~abstract_action() {}
    };

    class action {
    public:
        action() = default;

        action(const action &) = delete;

        action &operator=(const action &)= delete;

        action(action &&) = default;

        action &operator=(action &&)= default;

        ~action() = default;

        action(abstract_action *aa) : action_impl_ptr(aa) {}

        void operator()(messaging::message &&msg) {
            action_impl_ptr->operator()(std::move(msg));
        }

    private:
        std::unique_ptr<abstract_action> action_impl_ptr;
    };


    class behavior {
    public:
        behavior() = default;

        behavior(behavior &&) = default;

        behavior(const behavior &) = default;

        behavior &operator=(behavior &&) = default;

        behavior &operator=(const behavior &) = default;

        ~behavior() = default;

        void insert(const std::string &type, abstract_action *aa);

        void run(messaging::message &&);

        //debug method
        void all_name_view();

    private:
        std::unordered_map<std::string, action> behavioral_reactions;
    };
}

#endif //BEHAVIOR_HPP
