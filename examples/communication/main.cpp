#include <cassert>

#include <map>
#include <unordered_set>
#include <vector>

#include <actor-zeta/core.hpp>
#include <actor-zeta/link.hpp>

class dummy_executor final : public actor_zeta::abstract_executor {
public:
    dummy_executor()
        : abstract_executor(1, 10000) {}

    void execute(actor_zeta::executable* ptr) override {
        ptr->run(nullptr, max_throughput());
    }
    void start() override {}
    void stop() override {}
};

class storage_t final : public actor_zeta::basic_async_actor {
public:
    explicit storage_t(actor_zeta::supervisor_abstract* ptr)
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
    }

    ~storage_t() override = default;
};

class network_t final : public actor_zeta::basic_async_actor {
public:
    ~network_t() override = default;

    explicit network_t(actor_zeta::supervisor_abstract* ptr)
        : actor_zeta::basic_async_actor(ptr, "network") {}
};

class supervisor_lite final : public actor_zeta::supervisor_abstract {
public:
    explicit supervisor_lite(dummy_executor* ptr)
        : supervisor_abstract("network")
        , e_(ptr)
        , cursor(0)
        , system_{"sync_contacts", "add_link", "remove_link"} {
        add_handler("create_network",&supervisor_lite::create_network);
        add_handler("create_storage",&supervisor_lite::create_storage);
    }

    void create_storage() {
        spawn_actor<storage_t>();
    }

    void create_network() {
        spawn_actor<network_t>();
    }

    ~supervisor_lite() override = default;

    auto executor_impl() noexcept -> actor_zeta::abstract_executor* final {
        return e_;
    }

    auto add_actor_impl(actor_zeta::actor) -> void override {

    }

    auto add_supervisor_impl(actor_zeta::supervisor) -> void override {

    }

    void enqueue_base(actor_zeta::message_ptr msg, actor_zeta::execution_device*) final {
        auto msg_ = std::move(msg);
        auto it = system_.find(msg_->command());
        if (it != system_.end()) {
            local(std::move(msg_));
        } else {
            redirect_robin(std::move(msg_));
        }
    }

private:
    auto local(actor_zeta::message_ptr msg) -> void {
        set_current_message(std::move(msg));
        execute();
    }

    auto redirect_robin(actor_zeta::message_ptr msg) -> void {
        if (!actors_.empty()) {
            actors_[cursor]->enqueue(std::move(msg));
            ++cursor;
            if (cursor >= actors_.size()) {
                cursor = 0;
            }
        }
    }

    actor_zeta::abstract_executor* e_;
    std::vector<actor_zeta::actor> actors_;
    std::size_t cursor;
    std::unordered_set<actor_zeta::detail::string_view> system_;
};

int main() {
    actor_zeta::supervisor supervisor_tmp(new supervisor_lite(new dummy_executor));
    actor_zeta::send(supervisor_tmp,actor_zeta::address_t::empty_address(),"create_storage");
    actor_zeta::send(supervisor_tmp,actor_zeta::address_t::empty_address(),"create_network");
    actor_zeta::supervisor supervisor1(new supervisor_lite(new dummy_executor));
    actor_zeta::link(supervisor_tmp, supervisor1);
    actor_zeta::send(supervisor1,actor_zeta::address_t::empty_address(),"create_storage");
    actor_zeta::send(supervisor1,actor_zeta::address_t::empty_address(),"create_network");
    return 0;
}