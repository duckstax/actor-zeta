#include <cassert>

#include <map>
#include <vector>

#include <actor-zeta/core.hpp>
#include <actor-zeta/environment.hpp>
#include <actor-zeta/supervisor_heavy.hpp>

using actor_zeta::basic_async_actor ;
using actor_zeta::abstract_executor;
using actor_zeta::context;

using actor_zeta::environment::abstract_environment;
using actor_zeta::environment::supervisor_heavy;
using actor_zeta::environment::environment;
using actor_zeta::environment::make_environment;

class dummy_executor final : public abstract_executor {
public:
    dummy_executor():abstract_executor(1,10000){}

    void execute(actor_zeta::executable *ptr) override {
        ptr->run(nullptr, max_throughput());
    }
    void start() override{}
    void stop() override{}
};

class dummy_environment final : public abstract_environment {
public:
    explicit dummy_environment(actor_zeta::abstract_executor* ptr):e_(ptr){

    }

    std::size_t start() override {
        return 0;
    }

    actor_zeta::abstract_executor &get_executor() override {
        return *e_;
    }

    ~dummy_environment() override = default;

protected:
    std::unique_ptr<actor_zeta::abstract_executor> e_;
};

class storage_t final : public basic_async_actor {
public:
    explicit storage_t(supervisor_heavy*ptr) : basic_async_actor(ptr, "storage") {
        add_handler(
                "update",
                [](context & /*ctx*/) -> void {}
        );

        add_handler(
                "find",
                [](context & /*ctx*/) -> void {}
        );

        add_handler(

                "remove",
                [](context & /*ctx*/) -> void {}
        );
    }

    ~storage_t() override = default;
};

class network_t final : public basic_async_actor {
public:
    ~network_t() override = default;

    explicit network_t(supervisor_heavy*ptr) : basic_async_actor(ptr, "network") {}
};

int main() {

    auto env = make_environment<dummy_environment>(new dummy_executor);

    auto*supervisor = env->supervisor<supervisor_heavy>(env.get(),"");

    auto storage = supervisor->join<storage_t>(supervisor);

    auto network = supervisor->join<network_t>(supervisor);

    actor_zeta::actor::link(storage,network);

    auto*supervisor1 = env->supervisor<supervisor_heavy>(env.get(),"");

    supervisor->join(*supervisor1);

    supervisor1->join(*supervisor);

    auto storage1 = supervisor1->join<storage_t>(supervisor);

    auto network1 = supervisor1->join<network_t>(supervisor);

    actor_zeta::actor::link(storage1,network1);

    return 0;
}