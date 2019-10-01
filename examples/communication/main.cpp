#include <cassert>

#include <map>
#include <vector>
#include <unordered_set>

#include <actor-zeta/core.hpp>

using actor_zeta::basic_async_actor ;
using actor_zeta::abstract_executor;
using actor_zeta::context;
using actor_zeta::supervisor;

using actor_zeta::environment::abstract_environment;
using actor_zeta::environment::environment;
using actor_zeta::make_actor;
using actor_zeta::link;
using actor_zeta::message;

class dummy_executor final : public abstract_executor {
public:
    dummy_executor():abstract_executor(1,10000){}

    void execute(actor_zeta::executable *ptr) override {
        ptr->run(nullptr, max_throughput());
    }
    void start() override{}
    void stop() override{}
};

class dummy_environment final {
public:
    explicit dummy_environment(actor_zeta::abstract_executor* ptr):e_(ptr){

    }

    std::size_t start() {
        return 0;
    }

    actor_zeta::abstract_executor &executor() {
        return *e_;
    }

    auto get_executor() noexcept -> actor_zeta::abstract_executor * { return e_.get(); }

    ~dummy_environment() = default;

protected:
    std::unique_ptr<actor_zeta::abstract_executor> e_;
};

class supervisor_lite final : public supervisor {
public:
    explicit supervisor_lite(dummy_environment *ptr)
            : supervisor("network")
            , e_(ptr->get_executor())
            , cursor(0)
            , system_{"sync_contacts", "add_link", "remove_link"}
    {
    }

    ~supervisor_lite() override = default;

    auto shutdown() noexcept -> void {
        e_->stop();
    }

    auto startup() noexcept -> void {
        e_->start();
    }

    auto executor() noexcept -> actor_zeta::abstract_executor & final { return *e_; }

    auto broadcast(message msg) -> bool final {

        for (auto &i:contacts) {
            i.second->enqueue(std::move(msg));
        }

        return true;
    }

    using actor_zeta::actor::supervisor::join;

    auto join(actor_zeta::actor::base_actor *t) -> actor_zeta::actor::actor_address final {
        actor_zeta::actor::actor tmp(t);
        auto address = tmp->address();
        actors_.push_back(std::move(tmp));
        return address;
    }

    auto enqueue(message msg, actor_zeta::executor::execution_device *) -> void final {
        auto msg_ = std::move(msg);
        auto it = system_.find(msg_.command());
        if (it != system_.end()) {
            local(std::move(msg_));
        } else {
            redirect_robin(std::move(msg_));
        }
    }

private:
    auto local(message msg) -> void {
        context tmp(this, std::move(msg));
        dispatch().execute(tmp);
    }

    auto redirect_robin(message msg) -> void {
        if (!actors_.empty()) {
            actors_[cursor]->enqueue(std::move(msg));
            ++cursor;
            if (cursor >= actors_.size()) {
                cursor = 0;
            }
        }
    }

    abstract_executor *e_;
    std::vector<actor_zeta::actor::actor> actors_;
    std::size_t cursor;
    std::unordered_set<actor_zeta::detail::string_view> system_;
};

class storage_t final : public basic_async_actor {
public:
    explicit storage_t(supervisor_lite*ptr) : basic_async_actor(ptr, "storage") {
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

    explicit network_t(supervisor_lite *ptr) : basic_async_actor(ptr, "network") {}
};

int main() {

    std::unique_ptr<dummy_environment> env(new dummy_environment(new dummy_executor));

    auto*supervisor = env->supervisor<supervisor_lite>(env.get());

    auto storage = make_actor<storage_t>(supervisor);

    auto network = make_actor<network_t>(supervisor);

    actor_zeta::link(storage,network);

    auto*supervisor1 = env->supervisor<supervisor_lite>(env.get());

    actor_zeta::link(supervisor,supervisor1);

    auto storage1 = make_actor<storage_t>(supervisor1);

    auto network1 = make_actor<network_t>(supervisor1);

    actor_zeta::link(storage1,network1);

    return 0;
}