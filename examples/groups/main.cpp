#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <iostream>

#include <actor-zeta/actor/actor.hpp>
#include <actor-zeta/actor/basic_actor.hpp>
#include <actor-zeta/environment/abstract_environment.hpp>
#include <actor-zeta/environment/cooperation.hpp>
#include <actor-zeta/executor/abstract_coordinator.hpp>


using actor_zeta::behavior::make_handler;
using actor_zeta::behavior::context;
using actor_zeta::messaging::make_message;
using actor_zeta::environment::abstract_environment;
using actor_zeta::actor::basic_async_actor;


class dummy_environmentl final : public abstract_environment {
public:

    int start() override {
      return 0;
    }

    actor_zeta::executor::abstract_coordinator &manager_execution_device() override {
        return *e_.get();
    }

    actor_zeta::environment::cooperation &manager_group() override {
        return cooperation_;
    }

    ~dummy_environmentl() override = default;

protected:
    actor_zeta::environment::cooperation cooperation_;
    std::unique_ptr<actor_zeta::executor::abstract_coordinator> e_;
};

class storage_t final : public basic_async_actor {
public:
    storage_t(abstract_environment *ptr): basic_async_actor(ptr,"storage"){
        attach(
                make_handler(
                        "update",
                        [this]( context& ctx,int&dummy ) -> void {


                        }
                )
        );

        attach(
                make_handler(
                        "find",
                        [this]( context& ctx,int&dummy ) -> void {


                        }
                )
        );

        attach(
                make_handler(
                        "remove",
                        [this]( context& ctx,int&dummy ) -> void {

                        }
                )
        );



    }

    ~storage_t() override = default;

private:
    std::unordered_map<std::string,std::string> storage_;

};

class network_t final : public basic_async_actor {
public:
    ~network_t() override = default;

    explicit network_t(abstract_environment *ptr): basic_async_actor(ptr,"network"){

    }
};

int main() {

    auto* env = new dummy_environmentl;

    actor_zeta::environment::environment environment(env);

    auto& group_storage = environment->manager_group().created_group( new storage_t(env));

    auto& group_fake_network = environment->manager_group().created_group(new network_t(env));

    actor_zeta::environment::link(group_fake_network,group_storage);
    actor_zeta::environment::link(group_storage,group_fake_network);

    return 0;
}