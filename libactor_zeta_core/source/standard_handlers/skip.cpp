#include "actor-zeta/standard_handlers/skip.hpp"

#include <iostream>
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {

    skip::skip() : abstract_action("skip") {}// TODO: "skip" -> "" ?

    behavior::response *skip::operator()(behavior::request *r) {
        std::cerr << "WARNING" << std::endl;
        std::cerr << r->message()->type().to_string() << std::endl;
        std::cerr << "WARNING" << std::endl;
        return nullptr;
    }
}
