// clang-format off
#include <actor-zeta/base/handler.hpp>
#include <actor-zeta/base/address.hpp>
#include <actor-zeta/base/message.hpp>
#include <actor-zeta/base/basic_actor.hpp>
#include <actor-zeta/base/supervisor.hpp>
#include <actor-zeta/impl/handler.ipp>
// clang-format on
#include <actor-zeta/base/actor.hpp>
#include <actor-zeta/base/supervisor_abstract.hpp>
#include <actor-zeta/detail/aligned_allocate.hpp>
#include <actor-zeta/link.hpp>

namespace actor_zeta { namespace base {

    using detail::DEFAULT_ALIGNMENT;

    using detail::aligned_allocate;
    using detail::aligned_deallocate;
    using detail::is_supported_alignment;

    class new_delete_resource final : public detail::pmr::memory_resource {
    public:
    private:
        void* do_allocate(std::size_t bytes, std::size_t alignment = DEFAULT_ALIGNMENT) override {
            alignment = (is_supported_alignment(alignment)) ? alignment : DEFAULT_ALIGNMENT;
            return aligned_allocate(bytes, alignment, [](std::size_t size) { return ::operator new(size); });
        }

        void do_deallocate(void* p, std::size_t bytes, std::size_t alignment = DEFAULT_ALIGNMENT) override {
            aligned_deallocate(p, bytes, alignment, [](void* p) { ::operator delete(p); });
        }

        bool do_is_equal(const memory_resource& other) const noexcept override { return &other == this; }
    };

    supervisor_abstract::supervisor_abstract(std::string name, detail::pmr::memory_resource* memory_resource)
        : communication_module(std::move(name))
        , memory_resource_(memory_resource) {
        add_handler("spawn_actor", &supervisor_abstract::spawn_actor);
        add_handler("spawn_supervisor", &supervisor_abstract::spawn_supervisor);
        add_handler("delegate", &supervisor_abstract::redirect);
    }

    supervisor_abstract::supervisor_abstract(std::string name)
        : communication_module(std::move(name))
        , memory_resource_(new new_delete_resource) {
        add_handler("spawn_actor", &supervisor_abstract::spawn_actor);
        add_handler("spawn_supervisor", &supervisor_abstract::spawn_supervisor);
        add_handler("delegate", &supervisor_abstract::redirect);
    }

    supervisor_abstract::supervisor_abstract(supervisor_abstract* ptr, std::string name)
        : communication_module(std::move(name))
        , memory_resource_(ptr->resource()) {
        add_handler("spawn_actor", &supervisor_abstract::spawn_actor);
        add_handler("spawn_supervisor", &supervisor_abstract::spawn_supervisor);
        add_handler("delegate", &supervisor_abstract::redirect);
    }
    supervisor_abstract::~supervisor_abstract() {}

    auto supervisor_abstract::current_message() -> message* {
        return current_message_;
    }

    auto supervisor_abstract::set_current_message(message_ptr msg) -> void {
        current_message_ = msg.release();
    }

    auto supervisor_abstract::resource() const -> detail::pmr::memory_resource* {
        return memory_resource_;
    }

    auto supervisor_abstract::executor() noexcept -> executor::abstract_executor* {
        return executor_impl();
    }

    auto supervisor_abstract::spawn_actor(default_spawn_actor& construct) -> void {
        auto actor_tmp = std::move(construct(this));
        auto address = actor_tmp->address();
        add_actor_impl(std::move(actor_tmp));
        link(*this, address);
        if (this != current_message()->sender().get()) {
            link(current_message()->sender(), address);
        }
    }

    auto supervisor_abstract::spawn_supervisor(default_spawn_supervisor& construct) -> void {
        auto supervisor = std::move(construct(this));
        auto address = supervisor->address();
        add_supervisor_impl(std::move(supervisor));
        link(*this, address);
    }

    auto supervisor_abstract::redirect(std::string& type, message* msg) -> void {
        message_ptr tmp(std::move(msg));
        auto type_t = std::move(type);
        tmp->sender() = std::move(address());
        send(address_book(type_t.c_str()), std::move(tmp));
    }

    auto supervisor_abstract::address() noexcept -> address_t {
        return address_t(this);
    }
}} // namespace actor_zeta::base
