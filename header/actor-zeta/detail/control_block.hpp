#pragma once

#include <atomic>

#include "intrusive_ptr.hpp"
#include "weak_intrusive_ptr.hpp"

namespace actor_zeta {

    template<class Data>
    struct control_block final {
        using data_destructor = void (*)(Data*);
        using block_destructor = void (*)(control_block*);

        control_block(data_destructor ddtor, block_destructor bdtor)
        : strong_refs(1)
        , weak_refs(1)
        , data_dtor(ddtor)
        , block_dtor(bdtor) {
            // nop
        }

        control_block(const control_block&) = delete;
        control_block& operator=(const control_block&) = delete;

        std::atomic<size_t> strong_refs;
        std::atomic<size_t> weak_refs;
        const data_destructor data_dtor;
        const block_destructor block_dtor;

        static_assert(sizeof(std::atomic<size_t>) == sizeof(void*),"std::atomic not lockfree on this platform");

        static_assert(sizeof(intrusive_ptr<int>) == sizeof(int*),"intrusive_ptr<T> and T* have different size");

        static_assert(sizeof(data_destructor) == sizeof(void*),"functiion pointer and regular pointers have different size");

        Data* get() {
            return reinterpret_cast<Data*>(reinterpret_cast<intptr_t>(this)+ CACHE_LINE_SIZE);
        }
    };

    template<class Data>
    control_block<Data>* from(const Data* ptr) {
        return reinterpret_cast<control_block<Data>*>(reinterpret_cast<intptr_t>(ptr) - CACHE_LINE_SIZE);
    }

    template<class Data>
    bool intrusive_ptr_upgrade_weak(control_block<Data>* x) {
        auto count = x->strong_refs.load();
        while (count != 0)
            if (x->strong_refs.compare_exchange_weak(count, count + 1,std::memory_order_relaxed)) {
                return true;
            }
        return false;
    }

    template<class Data>
    void intrusive_ptr_release_weak(control_block<Data>* x) {
        if (x->weak_refs == 1|| x->weak_refs.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            x->block_dtor(x);
        }
    }

    template<class Data>
    void intrusive_ptr_release(control_block<Data>* x) {
        if (x->strong_refs.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            x->data_dtor(x->get());
            intrusive_ptr_release_weak(x);
        }
    }

    template<class Data>
    void intrusive_ptr_add_weak_ref(control_block<Data>* x) {
        x->weak_refs.fetch_add(1, std::memory_order_relaxed);
    }



    template<class Data>
    void intrusive_ptr_add_ref(control_block<Data>* x) {
        x->strong_refs.fetch_add(1, std::memory_order_relaxed);
    }

}