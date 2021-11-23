#include <cassert>

#include <set>
#include <string>

#include <actor-zeta/core.hpp>
#include <actor-zeta/send.hpp>
#include <iostream>

class storage_t final : public actor_zeta::basic_async_actor {
public:
    storage_t(actor_zeta::supervisor_abstract* ptr)
        : actor_zeta::basic_async_actor(ptr, "storage") {
        add_handler(
            "update",
            []() -> void {});

        add_handler(
            "find",
            []() -> void {});

        add_handler(
            "remove",
            []() -> void {});

        assert(actor_zeta::detail::string_view("storage") == type());

        auto tmp = message_types();

        std::set<std::string> control = {"add_link", "remove_link", "update", "remove", "find"};

        std::set<std::string> diff;

        std::set_difference(tmp.begin(), tmp.end(), control.begin(), control.end(), std::inserter(diff, diff.begin()));

        assert(diff.empty());
    }

    ~storage_t() override = default;
};

class dummy_executor final : public actor_zeta::abstract_executor {
public:
    dummy_executor(uint64_t threads, uint64_t throughput)
        : abstract_executor(threads, throughput) {}

    void execute(actor_zeta::executable* ptr) override {
        ptr->run(nullptr, max_throughput());
        intrusive_ptr_release(ptr);
    }

    void start() override {}

    void stop() override {}
};

class dummy_supervisor  final : public actor_zeta::supervisor_abstract {
public:
    dummy_supervisor()
        : supervisor_abstract("dummy_supervisor")
        , e_(new dummy_executor(1, 1)) {
        e_->start();
        add_handler("create", &dummy_supervisor::create);
    }

    void create() {
        spawn_actor<storage_t>();
    }

    auto executor_impl() noexcept -> actor_zeta::abstract_executor* final {
        return e_.get();
    }

    auto add_actor_impl(actor_zeta::actor t) -> void final {
        actors_.emplace_back(std::move(t));
    }

    auto add_supervisor_impl(actor_zeta::supervisor t) -> void final {
        supervisor_.emplace_back(std::move(t));
    }

    auto enqueue_base(actor_zeta::message_ptr msg, actor_zeta::execution_device*) -> void final {
        {
            set_current_message(std::move(msg));
            execute();
        }
    }

private:
    std::unique_ptr<actor_zeta::abstract_executor> e_;
    std::vector<actor_zeta::actor> actors_;
    std::vector<actor_zeta::supervisor> supervisor_;
};

int main() {
    actor_zeta::supervisor supervisor(new dummy_supervisor());
   actor_zeta::send(supervisor,actor_zeta::address_t::empty_address(),"create");

    return 0;
}
