#include "actor-zeta/standard_handlers/skip.hpp"


namespace actor_zeta {

    skip::skip() : abstract_action("skip") {}// TODO: "skip" -> "" ?

    behavior::response *skip::operator()(behavior::request *) {
        return nullptr;
    }
}
