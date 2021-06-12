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

    supervisor_t::supervisor_t(detail::pmr::memory_resource* memory_resource, std::string name)
        : communication_module(std::move(name), sub_type_t::supervisor)
        , memory_resource_(memory_resource) {
        add_handler("spawn_actor", &supervisor_t::spawn_actor);
        add_handler("spawn_supervisor", &supervisor_t::spawn_supervisor);
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
        return executor_impl();
    }
    auto supervisor_t::spawn_actor(default_spawn_actor& construct) -> void {
        auto actor_tmp = std::move(construct(memory_resource_));
        add_actor_impl(std::move(actor_tmp));
    }

    auto supervisor_t::spawn_supervisor(default_spawn_supervisor& construct) -> void {
        auto supervisor = std::move(construct(memory_resource_));
        add_supervisor_impl(std::move(supervisor));
    }

}} // namespace actor_zeta::base