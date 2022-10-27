#pragma once

#include <actor-zeta/detail/unique_ptr.hpp>
#include <actor-zeta/detail/queue/singly_linked.hpp>
#include <actor-zeta/detail/memory_resource.hpp>

namespace tools {

    struct inode : actor_zeta::detail::singly_linked<inode> {
        int value;
        explicit inode(int x = 0)
            : value(x) {}
    };

    inline bool operator==(const inode& lhs, const inode& rhs) {
        return lhs.value == rhs.value;
    }
    inline bool operator!=(const inode& lhs, const inode& rhs) {
        return !operator==(lhs, rhs);
    }

    auto to_string(const inode& x) -> std::string {
        return std::to_string(x.value);
    }

    template<typename _Alloc>
    struct inode_policy__ {
        using mapped_type = inode;
        using task_size_type = int;
        using deficit_type = int;
        using deleter_type = actor_zeta::detail::deleter_t<mapped_type, _Alloc>;
        using unique_pointer = std::unique_ptr<mapped_type, deleter_type>;

        static inline auto task_size(const mapped_type& x) -> task_size_type {
            return x.value;
        }
    };

    using allocator_t = std::allocator<inode>;
    using allocator_pmr_t = actor_zeta::detail::pmr::polymorphic_allocator<inode>;

    using inode_policy = inode_policy__<allocator_t>;
    using inode_policy_pmr = inode_policy__<allocator_pmr_t>;

}
