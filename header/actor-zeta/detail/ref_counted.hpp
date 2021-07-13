#pragma once

#include <atomic>
#include <cstddef>

namespace actor_zeta {
    ///
    /// @brief This class represents reference counter
    ///
    class ref_counted {
    public:
        virtual ~ref_counted();

        ref_counted();

        ref_counted(const ref_counted&);

        ref_counted& operator=(const ref_counted&);

        void ref() const noexcept {
            rc_.fetch_add(1, std::memory_order_relaxed);
        }

        void deref() const noexcept {
            if (unique() || rc_.fetch_sub(1, std::memory_order_acq_rel) == 1)
                delete this;
        }

        /// Queries whether there is exactly one reference.
        bool unique() const noexcept {
            return rc_ == 1;
        }

        size_t get_reference_count() const noexcept {
            return rc_;
        }

    protected:
        mutable std::atomic<size_t> rc_;
    };

    inline void intrusive_ptr_add_ref(const ref_counted* p) {
        p->ref();
    }

    inline void intrusive_ptr_release(const ref_counted* p) {
        p->deref();
    }

} // namespace actor_zeta
