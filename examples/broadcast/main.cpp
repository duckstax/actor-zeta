#include <cassert>

#include <map>
#include <vector>

#include <actor-zeta/core.hpp>
#include <actor-zeta/environment.hpp>
#include <actor-zeta/supervisor_heavy.hpp>

using actor_zeta::basic_async_actor ;
using actor_zeta::abstract_executor;
using actor_zeta::context;

using actor_zeta::abstract_executor;
using actor_zeta::executor_t;
using actor_zeta::work_sharing;

using actor_zeta::environment::abstract_environment;
using actor_zeta::environment::supervisor_heavy;
using actor_zeta::environment::environment;
using actor_zeta::environment::make_environment;


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

class bot_t final : public basic_async_actor {
public:
    explicit bot_t(supervisor_heavy*ptr) : basic_async_actor(ptr, "bot") {
        add_handler(
                "action1",
                [](context & /*ctx*/) -> void {}
        );

        add_handler(
                "action2",
                [](context & /*ctx*/) -> void {}
        );

        add_handler(
                "action2",
                [](context & /*ctx*/) -> void {}
        );
    }

    ~bot_t() override = default;
};



int main() {

    auto *thread_pool = new executor_t<work_sharing>(1, std::numeric_limits<std::size_t>::max());

    auto env = make_environment<dummy_environment>(thread_pool);

    auto *supervisor = env->supervisor<supervisor_heavy>(env.get(),"bot_master");

    int const threads = 10;
    for(auto i = threads - 1; i > 0; --i){
        auto bot = supervisor->join<bot_t>(supervisor);
        actor_zeta::actor::link(supervisor, bot);
    }
    /*


    */
    return 0;

}