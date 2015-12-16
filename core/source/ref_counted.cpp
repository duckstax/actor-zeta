#include "ref_counted.hpp"

namespace actor_model {

    ref_counted::~ref_counted() {
        // nop
    }

    ref_counted::ref_counted() : rc_(1) {
        // nop
    }

    ref_counted::ref_counted(const ref_counted &) : rc_(1) {
        // nop; don't copy reference count
    }

    ref_counted &ref_counted::operator=(const ref_counted &) {
        // nop; intentionally don't copy reference count
        return *this;
    }

    void ref_counted::deref() noexcept {
        if (unique()) {
            delete this; //TODO: жесть
            return;
        }
        if (rc_.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            delete this; //TODO: жесть
        }
    }

} //
