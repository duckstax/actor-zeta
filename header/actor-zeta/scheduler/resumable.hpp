#pragma once

#include <type_traits>
#include <cstddef>

#include "forwards.hpp"

namespace actor_zeta {

    using max_throughput_t = size_t;

    namespace scheduler {

    enum class resume_result {
        resume,
        awaiting,
        done,
        shutdown
    };

    struct resumable {
        resumable();
        virtual ~resumable();
        virtual resume_result resume(max_throughput_t) = 0;
        virtual void intrusive_ptr_add_ref_impl() = 0;
        virtual void intrusive_ptr_release_impl() = 0;
    };

    template<class T>
    typename std::enable_if<std::is_same<T*, resumable*>::value>::type
    intrusive_ptr_add_ref(T* ptr) {
        ptr->intrusive_ptr_add_ref_impl();
    }

    template<class T>
    typename std::enable_if<std::is_same<T*, resumable*>::value>::type
    intrusive_ptr_release(T* ptr) {
        ptr->intrusive_ptr_release_impl();
    }

}} // namespace actor_zeta::scheduler