#include "actor-zeta/standard_handlers/skip.hpp"

#include <iostream>
#include "actor-zeta/behavior/request.hpp"
#include "actor-zeta/behavior/response.hpp"

namespace actor_zeta {

    void error(const std::string& _error_){
        std::cerr << "WARNING" << std::endl;
        std::cerr << _error_ << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    skip::skip() : abstract_action("skip") {}// TODO: "skip" -> "" ?

    behavior::response skip::operator()(behavior::request &&r) {
        error(r.message().type().to_string());
        return behavior::response();
    }
}
