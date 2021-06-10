// clang-format off
#include <actor-zeta/base/context.hpp>
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/actor_address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on
#include <actor-zeta/base/actor.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>

namespace actor_zeta { namespace base {

    supervisor_t::supervisor_t(std::string name, detail::pmr::memory_resource* memory_resource)
        : communication_module(std::move(name), sub_type_t::supervisor)
        , memory_resource_(memory_resource) {
        add_handler("join_actor", &supervisor_t::join_actor);
        add_handler("join_supervisor", &supervisor_t::join_supervisor);
    }

    supervisor_t::~supervisor_t() {}

    auto supervisor_t::current_message() -> message* {
        return current_message_;
    }

    auto supervisor_t::set_current_message(message_ptr msg) -> void {
        current_message_ = msg.release();
    }

    auto supervisor_t::resource() const -> detail::pmr::memory_resource* {
        return memory_resource_;
    }
    auto supervisor_t::executor() noexcept -> executor::abstract_executor* {
        return executor_imp();
    }
    auto supervisor_t::join_actor(default_spawn_actor& construct) -> actor_address {
        auto actor = std::move(construct(memory_resource_));
        return join_imp(std::move(actor));
    }

    auto supervisor_t::join_supervisor(default_spawn_supervisor& construct) -> actor_address {
        auto supervisor = std::move(construct(memory_resource_));
        return join_imp(std::move(supervisor));
    }

}} // namespace actor_zeta::base