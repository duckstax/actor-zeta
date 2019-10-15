#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <iostream>

#include <actor-zeta/core.hpp>

using actor_zeta::basic_async_actor;
using actor_zeta::context;
using actor_zeta::send;
using actor_zeta::abstract_executor;
using actor_zeta::supervisor;
using actor_zeta::message;
using actor_zeta::execution_device;

class dummy_executor final : public abstract_executor {
public:
    dummy_executor():abstract_executor(1,10000){}

    void execute(actor_zeta::executable *ptr) override {
        ptr->run(nullptr, max_throughput());
    }
    void start() override{}
    void stop() override{}
};


class dummy_supervisor final : public supervisor {
public:

    dummy_supervisor(actor_zeta::abstract_executor*ptr)
        : supervisor("dummy_supervisor")
        , ptr_(ptr)
        {
    }

    auto executor() noexcept -> actor_zeta::abstract_executor& override  {
        return *ptr_;
    }

    auto broadcast(message) -> bool override {
        return true;
    }

    auto join(base_actor *) -> actor_zeta::actor::actor_address override {
        return actor_zeta::actor_address();
    }

    void enqueue(message, execution_device *) override {

    }

private:
    actor_zeta::abstract_executor*ptr_;
};

class storage_t final : public basic_async_actor {
public:
    storage_t(dummy_supervisor&ref) : basic_async_actor(ref, "storage") {
        add_handler(
                "update",
                [](context & /*ctx*/, std::string &data) -> void {
                    std::cerr << "update:" << data << std::endl;
                }
        );

        add_handler(
                "find",
                [](context & /*ctx*/) -> void {
                    std::cerr << "find" << std::endl;
                }
        );

        add_handler(
                "remove",
                [](context & /*ctx*/) -> void {
                    std::cerr << "remove" << std::endl;
                }
        );

    }

    ~storage_t() override = default;

};


int main() {
    auto * supervisor =  new dummy_supervisor(new dummy_executor);
    auto* storage = new storage_t(*supervisor);
    send(storage,actor_zeta::actor::actor_address(),"update",std::string("payload"));
    send(storage,actor_zeta::actor::actor_address(),"find",std::string("payload"));
    send(storage,actor_zeta::actor::actor_address(),"remove",std::string("payload"));

    return 0;
}