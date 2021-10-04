#pragma once
#include <actor-zeta/detail/ref_counted.hpp>

namespace actor_zeta {

    ref_counted::~ref_counted() {}

    ref_counted::ref_counted()
        : rc_(1) {}

    ref_counted::ref_counted(const ref_counted&)
        : rc_(1) {}

    ref_counted& ref_counted::operator=(const ref_counted&) {
        return *this;
    }
} // namespace actor_zeta
