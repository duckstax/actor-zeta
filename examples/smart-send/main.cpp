#include <cassert>

#include <unordered_set>
#include <queue>
#include <vector>
#include <iostream>

#include <actor-zeta/core.hpp>
#include <actor-zeta/environment.hpp>
#include <actor-zeta/supervisor_heavy.hpp>

using actor_zeta::basic_async_actor;
using actor_zeta::abstract_executor;
using actor_zeta::supervisor;
using actor_zeta::context;

using actor_zeta::abstract_executor;
using actor_zeta::executor_t;
using actor_zeta::work_sharing;

using actor_zeta::message;
using actor_zeta::make_message;

using actor_zeta::environment::abstract_environment;
using actor_zeta::environment::supervisor_heavy;
using actor_zeta::environment::environment;
using actor_zeta::environment::make_environment;

/// non thread safe
class generator_task final {
public:

    generator_task(supervisor& e)
        : executor_(e)
        , enabled_(true)
        {
    }

    ~generator_task() {
        enabled_ = false;
    }

    void stop() {
        enabled_ = false;
    }

    template<typename Task, typename ...Args>
    auto reg_task_type(const std::string &command, Args... args) -> void {
        queue_.push(std::move(make_message(executor_.address(), command, std::move(Task(std::forward<Args>(args)...)))));
    }

    void run() {
        while (enabled_) {
            while (!queue_.empty()) {
                auto task = std::move(queue_.front());
                queue_.pop();
                executor_.enqueue(std::move(task));
            }
        }
    }

private:
    supervisor& executor_;
    bool enabled_;
    std::queue<message> queue_;
};

/// non thread safe
class supervisor_lite final : public supervisor {
public:
    explicit supervisor_lite(abstract_executor *ptr)
            : supervisor(actor_zeta::detail::string_view("network"))
            , e_(ptr)
            , cursor(0)
            , system_{"sync_contacts", "add_link", "remove_link"}
            {

    }

    ~supervisor_lite() final {
        shutdown();
    }

    auto shutdown() noexcept -> void final {
        e_->stop();
    }

    auto startup() noexcept -> void final {
        e_->start();
    }

    auto executor() noexcept -> actor_zeta::executor::abstract_executor & final { return *e_; }

    auto broadcast(message msg) -> bool final {

        for (auto &i:contacts) {
            i.second->enqueue(std::move(msg));
        }

        return true;
    }

    auto join(supervisor &) -> void final {}

    using actor_zeta::actor::supervisor::join;

    auto join(actor_zeta::actor::base_actor *t) -> actor_zeta::actor::actor_address final {
        actor_zeta::actor::actor tmp(t);
        auto address = tmp->address();
        actors_.push_back(std::move(tmp));
        return address;
    }

    auto enqueue(message msg, actor_zeta::executor::execution_device *) -> bool final {
        auto msg_ = std::move(msg);
        auto it = system_.find(msg_.command());
        if (it != system_.end()) {
            local(std::move(msg_));
        } else {
            redirect_robin(std::move(msg_));
        }
        return true;
    }

private:
    auto local(message msg) -> bool {
        context tmp(this, std::move(msg));
        dispatch().execute(tmp);
        return true;
    }

    auto redirect_robin(message msg) -> bool {
        if (!actors_.empty()) {
            actors_[cursor]->enqueue(std::move(msg));
            ++cursor;
            if (cursor >= actors_.size()) {
                cursor = 0;
            }
            return true;
        }
        return false;
    }

    abstract_executor *e_;
    std::vector<actor_zeta::actor::actor> actors_;
    std::size_t cursor;
    std::unordered_set<actor_zeta::detail::string_view> system_;
};


struct add_like final {

    add_like(const std::string &socialNetwork, const std::string &name)
            : social_network(socialNetwork)
            , name(name)
            {
    }

    ~add_like() = default;

    std::string social_network;
    std::string name;
};

struct add_comment final {

    add_comment(const std::string &socialNetwork, const std::string &name, const std::string &comment)
            : social_network(socialNetwork)
            , name(name)
            , comment(comment)
            {
    }

    ~add_comment() = default;

    std::string social_network;
    std::string name;
    std::string comment;
};

class bot_t final : public basic_async_actor {
public:
    explicit bot_t(supervisor_lite *ptr) : basic_async_actor(ptr, "bot") {
        add_handler(
                "add_like",
                [](context & /*ctx*/, add_like &like) -> void {
                    std::cerr << "social network : " << like.social_network << std::endl;
                    std::cerr << "name : " << like.name << std::endl;
                }
        );

        add_handler(
                "add_comment",
                [](context & /*ctx*/, add_comment &comment) -> void {
                    std::cerr << "social network : " << comment.social_network << std::endl;
                    std::cerr << "name : " << comment.name << std::endl;
                    std::cerr << "comment : " << comment.comment << std::endl;
                }
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

    auto *supervisor = new supervisor_lite(thread_pool);

    int const threads = 10;
    for (auto i = threads - 1; i > 0; --i) {
        auto bot = supervisor->join<bot_t>(supervisor);
        actor_zeta::actor::link(supervisor, bot);
    }

    generator_task task_master(*supervisor);

    int const task = 10000;
    for (auto i = task - 1; i > 0; --i) {
        task_master.reg_task_type<add_like>("add_like", "fb", "jack");
    }

    supervisor->startup();
    task_master.run();
    return 0;
}