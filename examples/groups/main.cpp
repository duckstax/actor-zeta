#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <iostream>

#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/actor/basic_actor.hpp>
#include <actor-zeta/abstract_environment.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/environment.hpp>

using actor_zeta::actor::context;
using actor_zeta::environment::abstract_environment;
using actor_zeta::actor::basic_async_actor;


class dummy_environmentl final : public abstract_environment {
public:

    int start() override {
        return 0;
    }

    actor_zeta::executor::abstract_executor &get_executor() override {
        return *e_;
    }

    ~dummy_environmentl() override = default;

protected:
    std::unique_ptr<actor_zeta::executor::abstract_executor> e_;
};

class storage_t final : public basic_async_actor {
public:
    explicit storage_t(abstract_environment *ptr) : basic_async_actor(ptr, "storage") {
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

private:
    std::unordered_map<std::string, std::string> storage_;

};

class network_t final : public basic_async_actor {
public:
    ~network_t() override = default;

    explicit network_t(abstract_environment *ptr) : basic_async_actor(ptr, "network") {}
};

int main() {

    auto *env = new dummy_environmentl;

    actor_zeta::environment::environment environment(env);

    auto &group_storage = environment->created_group(new storage_t(env));

    auto &group_fake_network = environment->created_group(new network_t(env));

    actor_zeta::actor::link(group_fake_network, group_storage);
    actor_zeta::actor::link(group_storage, group_fake_network);

    return 0;
}