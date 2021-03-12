// clang-format off
#include <actor-zeta/context.hpp>
#include <actor-zeta/actor_address.hpp>
#include <actor-zeta/mail_box//message.hpp>
#include <actor-zeta/supervisor.hpp>
// clang-format on

namespace actor_zeta { namespace base {

    supervisor_t::supervisor_t(detail::string_view name)
        : communication_module(name, sub_type_t::supervisor) {}

    supervisor_t::~supervisor_t() {}

    auto supervisor_t::current_message() -> message* {
        return current_message_;
    }

    auto supervisor_t::set_current_message(message_ptr msg) -> void {
        current_message_ = msg.release();
    }

}} // namespace actor_zeta::base