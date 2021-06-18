#include "link.hpp"
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
using actor_zeta::context;

using actor_zeta::abstract_executor;
using actor_zeta::executor_t;
using actor_zeta::work_sharing;

using actor_zeta::make_message;

template<typename Task, typename... Args>
inline auto make_task(actor_zeta::supervisor& executor_, const std::string& command, Args... args) -> void {
    executor_->enqueue(std::move(make_message(executor_->address(), command, std::move(Task(std::forward<Args>(args)...)))));
}

template<typename Task, typename... Args>
inline auto make_task_broadcast(actor_zeta::supervisor& executor_, const std::string& command, Args... args) -> void {
    executor_->broadcast(make_message(executor_->address(), command, std::move(Task(std::forward<Args>(args)...))));
}

auto thread_pool_deleter = [](abstract_executor* ptr) {
    ptr->stop();
    delete ptr;
};

const int max_queue = 100;
struct spawn_task final {
    spawn_task() = default;
    ~spawn_task() = default;
};

class worker_t final : public actor_zeta::basic_async_actor {
public:
    explicit worker_t(actor_zeta::supervisor_abstract* ptr)
        : actor_zeta::basic_async_actor(ptr, "bot") {
        add_handler("on_spawn", &worker_t::on_spawn);
    }

    ~worker_t() override = default;

    /**
     * this will be called by a supervisor when it spawns new actor and broadcasts it
     * */
    auto on_spawn(actor_zeta::basic_async_actor* ptr) -> void {
        //worker should link only with worker, here we check what we got from a broadcast
        auto wrkr = dynamic_cast<worker_t*>(ptr); //what to do with rtti?
        if (wrkr) {
            actor_zeta::link(*this, wrkr);
        } else {
            std::cout << "not my type, won't link\n";
        }
    }

private:
};

/// non thread safe
class supervisor_lite final : public actor_zeta::supervisor_abstract {
public:
    explicit supervisor_lite()
        : supervisor_abstract("network")
        , e_(new executor_t<work_sharing>(1, max_queue),
             thread_pool_deleter)
        , system_{"add_link",
                  "remove_link",
                  "spawn_actor"} {
        add_handler("spawn_worker", &supervisor_lite::spawn_worker);
        e_->start();
    }

    ~supervisor_lite() override = default;

    auto executor_impl() noexcept -> actor_zeta::abstract_executor* final { return e_.get(); }

    auto add_actor_impl(actor_zeta::actor t) -> void final {
        actors_.emplace_back(std::move(t));
    }

    auto add_supervisor_impl(actor_zeta::supervisor t) -> void final {
        supervisor_.emplace_back(std::move(t));
    }

    auto spawn_worker(spawn_task& t_) -> void {
        auto t = std::move(t_);
        actor_zeta::spawn_actor<worker_t>(*this);
    }

    auto enqueue_base(actor_zeta::message_ptr msg, actor_zeta::execution_device*) -> void final {
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

    std::unique_ptr<abstract_executor, decltype(thread_pool_deleter)> e_;
    std::vector<actor_zeta::actor> actors_;
    std::vector<actor_zeta::supervisor> supervisor_;
    std::unordered_set<actor_zeta::detail::string_view> system_;
};

using namespace std::chrono_literals;

auto main() -> int {
    actor_zeta::supervisor supervisor(new supervisor_lite());

    int const actors = 5;

    worker_t wrkr(supervisor.get()); //this actor will recieve broadcasts with actors from supervisor

    for (auto i = actors - 1; i > 0; --i) {
        make_task<spawn_task>(supervisor, "spawn_worker"); //ask for spawns from supervisor
    }

    std::this_thread::sleep_for(180s);

    std::cerr << " Finish " << std::endl;
    return 0;
}
