// clang-format off
#include <address_t.hpp>
#include <message.hpp>
#include <abstract_supervisor.hpp>
// clang-format on

namespace actor_zeta {

    abstract_supervisor::abstract_supervisor(detail::string_view name)
        : communication_module(name) {}

    abstract_supervisor::~abstract_supervisor() {}

    auto abstract_supervisor::current_message() -> message& {
        return current_message_;
    }

    auto abstract_supervisor::set_current_message(message msg) -> void {
        current_message_ = std::move(msg);
    }

    void abstract_supervisor::enqueue(message msg, executor::execution_device* ptr) {
        enqueue_base(std::move(msg), ptr);
    }

    void abstract_supervisor::enqueue(message msg) {
        enqueue(std::move(msg), nullptr);
    }

} // namespace actor_zeta::base