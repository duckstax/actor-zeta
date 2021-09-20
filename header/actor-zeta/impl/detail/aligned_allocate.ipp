#pragma once

#include <actor-zeta/detail/aligned_allocate.hpp>

#ifdef __GNUC__
#include <features.h>
#endif

namespace actor_zeta { namespace detail {

    void* align(std::size_t alignment, std::size_t size, void*& ptr, std::size_t& space) {
#ifdef __GNUC__
#if __GNUC_PREREQ(5, 0)
        //      If  gcc_version >= 5.0
        return std::align(alignment, size, ptr, space);
#elif __GNUC_PREREQ(4, 0)
        //       If gcc_version >= 4.0
        auto pn = reinterpret_cast<std::size_t>(ptr);
        auto aligned = (pn + alignment - 1) & -alignment;
        auto new_space = space - (aligned - pn);
        if (new_space < size)
            return nullptr;
        space = new_space;
        return ptr = reinterpret_cast<void*>(aligned);

#else
        //       Else
        return std::align(alignment, size, ptr, space);
#endif
#else
        //    If not gcc
        return std::align(alignment, size, ptr, space);
#endif
    }

}

} // namespace actor_zeta::detail
