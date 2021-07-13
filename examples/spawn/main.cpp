#include "link.hpp"
#include "send.hpp"
#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <queue>
#include <thread>
#include <unordered_set>
#include <vector>

#include <actor-zeta.hpp>

using actor_zeta::abstract_executor;

using actor_zeta::abstract_executor;
using actor_zeta::executor_t;
using actor_zeta::work_sharing;

using actor_zeta::make_message;
using namespace std::chrono_literals;

std::atomic_int count;
const int max_queue = 100;

template<typename Task, typename... Args>
inline auto make_task(actor_zeta::supervisor& executor_, const std::string& command, Args... args) -> void {
    actor_zeta::send(executor_, executor_->address(), command, std::move(Task(std::forward<Args>(args)...)));
}

template<typename Task, typename... Args>
inline auto make_task_broadcast(actor_zeta::supervisor& executor_, const std::string& command, Args... args) -> void {
    executor_->broadcast(make_message(executor_->address(), command, std::move(Task(std::forward<Args>(args)...))));
}

auto thread_pool_deleter = [](abstract_executor* ptr) {
    ptr->stop();
    delete ptr;
};

class worker_t2;
class worker_t3;

class worker_t final : public actor_zeta::basic_async_actor {
public:
    explicit worker_t(actor_zeta::supervisor_abstract* ptr)
        : actor_zeta::basic_async_actor(ptr, "bot1") {
        count++;
        add_handler("spawn_worker", &worker_t::spawn_worker);
    }

    auto spawn_worker() -> void {
        actor_zeta::spawn_actor<worker_t2>(addresses("manager-2"));
        actor_zeta::spawn_actor<worker_t3>(addresses("manager-2"));
    }
};

class worker_t2 final : public actor_zeta::basic_async_actor {
public:
    explicit worker_t2(actor_zeta::supervisor_abstract* ptr)
        : actor_zeta::basic_async_actor(ptr, "bot2") {
        count++;
        std::cout << "bot2 created\n";
    }
};

class worker_t3 final : public actor_zeta::basic_async_actor {
public:
    explicit worker_t3(actor_zeta::supervisor_abstract* ptr)
        : actor_zeta::basic_async_actor(ptr, "bot3") {
        count++;
        std::cout << "bot3 created\n";
    }
};

class supervisor_lite final : public actor_zeta::supervisor_abstract {
public:
    explicit supervisor_lite(std::string name)
        : supervisor_abstract(std::move(name))
        , e_(new executor_t<work_sharing>(1, max_queue),
             thread_pool_deleter)
        , system_{"add_link",
                  "remove_link",
                  "spawn_actor"} {
        e_->start();
    }

    auto executor_impl() noexcept -> actor_zeta::abstract_executor* final { return e_.get(); }

    auto add_actor_impl(actor_zeta::actor t) -> void final {
        actors_.emplace_back(std::move(t));
    }

    auto add_supervisor_impl(actor_zeta::supervisor t) -> void final {
        supervisor_.emplace_back(std::move(t));
    }

    auto enqueue_base(actor_zeta::message_ptr msg, actor_zeta::execution_device*) -> void final {
        std::lock_guard<std::mutex> lock(mt);
        auto msg_ = std::move(msg);
        auto it = system_.find(msg_->command());
        if (it != system_.end()) {
            local(std::move(msg_));
        }
    }

private:
    auto local(actor_zeta::message_ptr msg) -> void {
        set_current_message(std::move(msg));
        execute(*this);
    }

    std::mutex mt;
    std::unique_ptr<abstract_executor, decltype(thread_pool_deleter)> e_;
    std::vector<actor_zeta::actor> actors_;
    std::vector<actor_zeta::supervisor> supervisor_;
    std::unordered_set<actor_zeta::detail::string_view> system_;
};

auto main() -> int {
    //TODO: broadcast handling in actors when spawn happens in supervisor
    //TODO: link existing actors with spawned ones when their type follows some predicate (based on name?)
    //TODO: "manager-2" has to be known in "bot1" names scope

    //1. manager-1 spawns 5 actors named "bot1"
    //2. each bot1 must send spawn request for types "bot2" and "bot3" to manager-2 upon spawning
    //3. manager-2 must spawn bot2 and bot3 actors on each request
    //4. manager-2 must link bot2 to bot3 upon each spawning
    //5. manager-2 must broatcast bots names to bot1 instances
    //6. bot1 must link itself with type "bot2" and ignore "bot3"
    //7. spawned actors count must be equal 5*3
    /*
        ┌──manager-1────┐◄────────────►┌────────────manager-2───────┐
        │               │              │                            │
        │ ┌─bot-1───┐   │              │  ┌─bot-2────┐   ┌─bot-3──┐ │
        │ │         ◄───┼──────────────┼──►          ◄───►        │ │
        │ │         │   │              │  │          │   │        │ │
        │ └─────────┘   │              │  └──────────┘   └────────┘ │
        │               │              │                            │
        └───────────────┘              └────────────────────────────┘
     */
    actor_zeta::supervisor supervisor1(new supervisor_lite("manager-1"));
    actor_zeta::supervisor supervisor2(new supervisor_lite("manager-2"));
    actor_zeta::link(supervisor1, supervisor2);

    int const actors = 15;
    count = 0;

    actor_zeta::spawn_actor<worker_t>(supervisor1); //actor creator, "bot1"

    for (auto i = actors - 1; i > 0; --i) {
        actor_zeta::send(supervisor1, "bot1", "spawn_worker");
    }

    std::this_thread::sleep_for(10s);
    std::cerr << " Finish " << std::endl;

    assert(count == actors);
    return 0;
}
