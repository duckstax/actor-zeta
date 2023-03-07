#pragma once

#include <actor-zeta/detail/memory_resource.hpp>

namespace actor_zeta { namespace detail {

    template<typename Tp_>
    class deleter_t final {
        pmr::memory_resource* mr_;

    public:
        deleter_t(pmr::memory_resource* mr)
            : mr_(mr ? mr : pmr::get_default_resource()) { assert(mr_); }
        void operator()(Tp_* target, std::size_t size = 1) {
            assert(target);
            for (int i = 0; i < size; ++i) {
                target[i].~Tp_();
            }
            pmr::deallocate_ptr(mr_, &target);
        }
    };

} }
