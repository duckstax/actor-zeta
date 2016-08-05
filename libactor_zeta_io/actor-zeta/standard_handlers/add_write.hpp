#ifndef REG_WRITE_HPP
#define REG_WRITE_HPP

#include <unordered_map>

#include "actor-zeta/connection_handler.hpp"
#include "actor-zeta/messaging/message.hpp"

namespace actor_zeta {
    namespace network {
        class add_write final : public behavior::interface_action {
        public:
            add_write(std::unordered_map<std::string, write_handler> &actions) : actions(actions),name_("add_write") {}

            void operator()(messaging::message &&msg) override final {
                write_handler element = msg.get<write_handler>();
                actions.emplace(element.id(), std::move(element));
            }

            const std::string& name() const override final{
                return name_;
            };

        private:
            std::unordered_map<std::string, write_handler> &actions;
            std::string name_;
        };
    }
}
#endif //WRITE_HPP
