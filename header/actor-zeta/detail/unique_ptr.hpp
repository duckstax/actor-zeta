#pragma once

#include <memory>

namespace actor_zeta { namespace detail {

    template<typename Tp_, typename _Alloc = std::allocator<Tp_>>
    class deleter_t final {
        _Alloc* allocator_;

    public:
        deleter_t(_Alloc* allocator) : allocator_(allocator) {}
        void operator()(Tp_* target, std::size_t size = 1) {
            for (int i = 0; i < size; ++i) {
                std::allocator_traits<_Alloc>::destroy(*allocator_, &target[i]);
            }
            std::allocator_traits<_Alloc>::deallocate(*allocator_, target, sizeof(Tp_) * size);
        }
    };

} }
