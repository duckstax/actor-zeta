#include <cassert>

#include <map>
#include <vector>
#include <unordered_set>

#include <actor-zeta/core.hpp>

using actor_zeta::basic_async_actor ;
using actor_zeta::abstract_executor;
using actor_zeta::context;
using actor_zeta::supervisor;

using actor_zeta::join;
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

class supervisor_lite final : public supervisor {
public:
    explicit supervisor_lite(dummy_executor *ptr)
            : supervisor("network")
            , e_(ptr)
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

    auto join(actor_zeta::actor t) -> actor_zeta::actor_address final {
        auto tmp = std::move(t);
        auto address = tmp->address();
        actors_.push_back(std::move(tmp));
        return address;
    }

    auto enqueue(message msg, actor_zeta::execution_device *) -> void final {
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
        set_current_message(std::move(msg));
        dispatch().execute(*this);
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
    std::vector<actor_zeta::actor> actors_;
    std::size_t cursor;
    std::unordered_set<actor_zeta::detail::string_view> system_;
};

class storage_t final : public basic_async_actor {
public:
    explicit storage_t(supervisor_lite&ref) : basic_async_actor(ref, "storage") {
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

    explicit network_t(supervisor_lite &ref) : basic_async_actor(ref, "network") {}
};

int main() {

    std::unique_ptr<supervisor_lite> supervisor(new supervisor_lite(new dummy_executor));

    auto storage = join<storage_t>(*supervisor);

    auto network = join<network_t>(*supervisor);

    actor_zeta::link(storage,network);

    std::unique_ptr<supervisor_lite> supervisor1(new supervisor_lite(new dummy_executor));

    actor_zeta::link(*supervisor,*supervisor1);

    auto storage1 = join<storage_t>(*supervisor1);

    auto network1 = join<network_t>(*supervisor1);

    actor_zeta::link(storage1,network1);

    return 0;
}