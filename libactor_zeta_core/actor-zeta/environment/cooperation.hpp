#ifndef COOPERATION_HPP
#define COOPERATION_HPP

#include <unordered_map>
#include "actor-zeta/messaging/message.hpp"
#include "group.hpp"


namespace actor_zeta {
    namespace environment {
        class cooperation final {
        public:
            cooperation() = default;

            cooperation(const cooperation &) = default;

            cooperation &operator=(const cooperation &) = default;

            cooperation(cooperation &&) = default;

            cooperation &operator=(cooperation &&) = default;

            ~cooperation() = default;

            auto created_group(actor::abstract_actor *t) -> group &;

            auto created_entry_group(actor::abstract_actor *t) -> group &;

            auto created_end_group(actor::abstract_actor *t) -> group &;

            auto create_link(group &g1, group &g2) -> void;

        private:
            std::unordered_map<std::string, group> groups;
            storage_space storage_space_;
            layer input_entry_point;
            layer output_end_point;
        };
    }
}
#endif
