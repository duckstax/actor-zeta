#ifndef WRITE_HPP
#define WRITE_HPP

#include <map>

namespace actor_zeta {
    namespace network {
        class write : public abstract_action {
        public:
            write(std::map<std::string, write_handler> &actions) : actions(actions) {}

            void operator()(messaging::message &&msg) {
                //name/blob data
                auto element = msg.get<std::pair<std::string, std::string>>();
                auto wh = *(actions.find(element.first));
                wh.second(element.second);
            }

        private:
            std::map<std::string, write_handler> &actions;
        };
    }
}
#endif //WRITE_HPP
