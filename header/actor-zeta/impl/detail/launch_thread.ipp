#pragma once

#include <sys/prctl.h>

#include <thread>
#include <type_traits>

namespace actor_zeta { namespace detail {

    void set_thread_name(const char* name) {
        prctl(PR_SET_NAME, name, 0, 0, 0);
    }

}} // namespace actor_zeta::detail