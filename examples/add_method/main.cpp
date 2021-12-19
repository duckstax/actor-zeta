#include <cassert>

#include <set>
#include <string>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/memory_resource.hpp>

using actor_zeta::detail::pmr::memory_resource;
class dummy_supervisor;

class storage_t final : public actor_zeta::basic_async_actor {
public:
    storage_t(dummy_supervisor* ptr)
        : actor_zeta::basic_async_actor(ptr, "storage", 0) {
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
        std::set<std::string> control = {"update", "remove", "find"};
        std::set<std::string> diff;
        std::set_difference(tmp.begin(), tmp.end(), control.begin(), control.end(), std::inserter(diff, diff.begin()));
        assert(diff.empty());
    }

    ~storage_t() override = default;
};

class dummy_executor final : public actor_zeta::scheduler_abstract_t {
public:
    dummy_executor(uint64_t threads, uint64_t throughput)
        : actor_zeta::scheduler_abstract_t(threads, throughput) {}

    void enqueue(actor_zeta::resumable*ptr)override {
        ptr->resume(nullptr, max_throughput());
        intrusive_ptr_release(ptr);
    }

    actor_zeta::clock::clock_t& clock() noexcept {

    }

    void start() override {}
    void stop() override {}
};

class dummy_supervisor final : public actor_zeta::cooperative_supervisor<dummy_supervisor> {
public:
    dummy_supervisor(memory_resource* ptr)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(ptr, "dummy_supervisor", 0)
        , e_(new dummy_executor(1, 1)) {
        e_->start();
        add_handler("create", &dummy_supervisor::create);
    }

    void create() {
        spawn_actor<storage_t>([this](storage_t* ptr) {
            actors_.emplace_back(ptr);
        });
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* {
        return e_.get();
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            execute();
        }
    }

private:
    std::unique_ptr<actor_zeta::scheduler_abstract_t> e_;
    std::vector<actor_zeta::actor> actors_;
};

int main() {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr);
    actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), "create");
    return 0;
}
