#include <iostream>
#include <map>
#include <vector>

#include <actor-zeta.hpp>

using actor_zeta::abstract_executor;
using actor_zeta::basic_async_actor;
using actor_zeta::execution_device;
using actor_zeta::message_ptr;
using actor_zeta::send;
using actor_zeta::supervisor_abstract;

class dummy_executor final : public abstract_executor {
public:
    dummy_executor()
        : abstract_executor(1, 10000) {}

    void execute(actor_zeta::executable* ptr) override {
        ptr->run(nullptr, max_throughput());
    }
    void start() override {}
    void stop() override {}
};

class dummy_supervisor final : public supervisor_abstract {
public:
    dummy_supervisor()
        : supervisor_abstract("dummy_supervisor")
        , ptr_(new dummy_executor) {
    }

    auto executor_impl() noexcept -> actor_zeta::abstract_executor* override {
        return ptr_;
    }

    auto add_actor_impl(actor_zeta::actor) -> void override {}
    auto add_supervisor_impl(actor_zeta::supervisor) -> void override {}

    void enqueue_base(message_ptr, actor_zeta::execution_device*) override {
    }

private:
    actor_zeta::abstract_executor* ptr_;
};

class storage_t final : public basic_async_actor {
public:
    storage_t(actor_zeta::supervisor_abstract* ptr)
        : basic_async_actor(ptr, "storage") {
        add_handler(
            "update",
            &storage_t::update);

        add_handler(
            "find",
            &storage_t::find);

        add_handler(
            "remove",
            &storage_t::remote);

        add_handler(
            "status",
            [](storage_t& ctx) {
                ctx.status();
            });
    }

    void status() {
        std::cerr << "status" << std::endl;
    }

    ~storage_t() override = default;

private:
    void update(std::string& data) {
        std::cerr << "update:" << data << std::endl;
    }

    void find() {
        std::cerr << "find" << std::endl;
    }

    void remote() {
        std::cerr << "remote" << std::endl;
    }
};

int main() {
    actor_zeta::supervisor supervisor(new dummy_supervisor());
    actor_zeta::spawn_actor<storage_t>(supervisor);
    ///send(storage, actor_zeta::actor_address(), "update", std::string("payload"));
    //send(storage, actor_zeta::actor_address(), "find");
    //send(storage, actor_zeta::actor_address(), "remove");
    ///send(storage, actor_zeta::actor_address(), "status");
    return 0;
}