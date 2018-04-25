#include <actor-zeta/behavior/context.hpp>

namespace actor_zeta { namespace behavior {

        state_t &context::state() const {
            return *current_state.get();
        }

        state_t *context::get_state() {
            return current_state.release();
        }

        context::~context() {
            if( ptr.get() != nullptr ){
                auto* tmp_1 =  ptr.release();
                tmp_1 = nullptr;
            }

            if( current_state.get() != nullptr ){
                auto* tmp_2 =  current_state.release();
                tmp_2 = nullptr;
            }
        }

        auto context::operator->() noexcept -> context_t * {
            return ptr.get();
        }

        auto context::operator->() const noexcept -> context_t * {
            return ptr.get();
        }

        auto context::operator*() noexcept -> context_t & {
            return *ptr.get();
        }

        auto context::operator*() const noexcept -> context_t & {
            return *ptr.get();
        }

        context::context(context_t *ptr, messaging::message &&msg) :
                ptr(ptr),
                current_state(new state_t(std::move(msg))) {

        }
    } /// behavior
} /// actor_zeta