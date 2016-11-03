#include "actor-zeta/standard_handlers/skip.hpp"

namespace actor_zeta {

    skip::skip() : abstract_action("skip") {}// TODO: "skip" -> "" ?
    void skip::operator()(messaging::message *msg) {}
}
