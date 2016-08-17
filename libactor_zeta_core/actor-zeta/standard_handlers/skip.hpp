#ifndef SKIP_HPP
#define SKIP_HPP

#include <string>

#include "actor-zeta/behavior/interface_action.hpp"


namespace actor_zeta {
    class skip final : public behavior::interface_action {
    public:
        skip() : name_("skip") {}

        void operator()(messaging::message *msg) override final {}

        const std::string &name() const override final {
            return name_;// TODO: "skip" -> "" ?
        };
    private:
        std::string name_;
    };
}
#endif //SKIP_HPP
