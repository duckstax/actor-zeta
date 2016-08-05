#ifndef REMOVE_WRITE_HPP
#define REMOVE_WRITE_HPP

#include <unordered_map>

#include "actor-zeta/behavior/interface_action.hpp"
#include "actor-zeta/connection_handler.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace network {
        class remove_write final : public behavior::interface_action {
        public:
            remove_write(std::unordered_map<std::string, write_handler> &actions) : actions(actions),name_("remove_write") {}

            void operator()(messaging::message &&msg) override final {
                std::string key = msg.get<std::string>();
                actions.erase(key);
            }

            const std::string& name() const override final {
                return name_;
            };

        private:
            std::string name_;
            std::unordered_map<std::string, write_handler> &actions;
        };
    }
}
#endif //REMOVE_WRITE_HPP
