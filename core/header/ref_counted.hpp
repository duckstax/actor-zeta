#ifndef REF_COUNTED_HPP
#define REF_COUNTED_HPP

#include <atomic>
#include <cstddef>


namespace actor_model {


    class ref_counted {
    public:
        ~ref_counted();

        ref_counted();

        ref_counted(const ref_counted &);

        ref_counted &operator=(const ref_counted &);

        inline void ref() noexcept {
            rc_.fetch_add(1, std::memory_order_relaxed);
        }

        void deref() noexcept;

        inline bool unique() const noexcept {
            return rc_ == 1;
        }

        inline size_t get_reference_count() const noexcept {
            return rc_;
        }

    protected:
        std::atomic<size_t> rc_;
    };

    inline void intrusive_ptr_add_ref(ref_counted *p) {
        p->ref();
    }


    inline void intrusive_ptr_release(ref_counted *p) {
        p->deref();
    }

}

#endif // REF_COUNTED_HPP
