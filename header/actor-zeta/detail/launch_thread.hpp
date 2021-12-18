#pragma once

#include <sys/prctl.h>

#include <thread>
#include <type_traits>

namespace actor_zeta { namespace detail {

    void set_thread_name(const char* name) {
        prctl(PR_SET_NAME, name, 0, 0, 0);
    }

    template<class F>
    std::thread launch_thread(const char* thread_name, F fun) {
        auto body = [thread_name, f = std::move(fun)]() {
            set_thread_name(thread_name);
            f();
        };
        return std::thread{std::move(body)};
    }
}} // namespace actor_zeta::detail