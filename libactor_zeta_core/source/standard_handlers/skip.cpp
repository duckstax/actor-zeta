#include "actor-zeta/standard_handlers/skip.hpp"

#include <iostream>

namespace actor_zeta {

    inline void error(const std::string& _error_){
        std::cerr << "WARNING" << std::endl;
        std::cerr << _error_ << std::endl;
        std::cerr << "WARNING" << std::endl;
    }

    skip::skip() : abstract_action("skip") {}// TODO: "skip" -> "" ?

    void skip::invoke(behavior::context &r) {
        error(r.message().command().to_string());

    }
}
