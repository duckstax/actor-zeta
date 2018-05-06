#include <actor-zeta/behavior/context.hpp>

namespace actor_zeta { namespace behavior {

        context::~context() {
            if( ptr.get() != nullptr ){
                auto* tmp_1 =  ptr.release();
                tmp_1 = nullptr;
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
                msg(std::move(msg)) {

        }

        messaging::message& context::message() {
            return msg; /// TODO hack
        }

        const messaging::message &context::message() const {
            return msg;
        }
    } /// behavior
} /// actor_zeta