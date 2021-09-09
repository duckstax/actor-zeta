#include <actor-zeta/make_message.hpp>
#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <actor-zeta.hpp>
#include <actor-zeta/link.hpp>

using actor_zeta::abstract_executor;
using actor_zeta::basic_async_actor;
using actor_zeta::supervisor;

using actor_zeta::abstract_executor;
using actor_zeta::executor_t;
using actor_zeta::work_sharing;

using actor_zeta::make_message;

std::atomic_int count_actor;
const int max_queue = 100;

#define TRACE(msg) \
    { std::cout << __FILE__ << ":" << __LINE__ << "::" << __func__ << " : " << msg << std::endl; }

class dummy_executor final : public abstract_executor {
public:
    dummy_executor(uint64_t threads, uint64_t throughput)
        : abstract_executor(threads, throughput) {}

    void execute(actor_zeta::executable* ptr) override {
        TRACE("execute(actor_zeta::executable* ptr) +++");
        ptr->run(nullptr, max_throughput());
        intrusive_ptr_release(ptr);
        TRACE("execute(actor_zeta::executable* ptr) ---");
    }

    void start() override {}

    void stop() override {}
};
/*
auto thread_pool_deleter = [](actor_zeta::abstract_executor* ptr) -> void {
    ptr->stop();
    delete ptr;
};
*/

auto thread_pool_deleter = [](dummy_executor* ptr) -> void {
    ptr->stop();
    delete ptr;
};

class dispatcher_t final : public actor_zeta::basic_async_actor {
public:
    explicit dispatcher_t(actor_zeta::supervisor_abstract* ptr)
        : actor_zeta::basic_async_actor(ptr, "dispatcher") {
        count_actor++;
        add_handler("create_database", &dispatcher_t::create_database);
        add_handler("create_collection", &dispatcher_t::create_collection);
    }

    void create_database(std::string& name) {
        std::cerr << "dispatcher_t::create_database : " << name << std::endl;
        actor_zeta::send(address_book("mdb"), address(), "create", std::move(name));
    }

    void create_collection(std::string& name_database, std::string& name_collection) {
        std::cerr << "dispatcher_t::create_collection : "<< "database : " << name_database << " collection : " << name_collection << std::endl;
        for (auto& i : all_view_address()) {
            std::cerr << "i : " << i << std::endl;
        }
        auto database = address_book(name_database);
        std::cerr << "!" << std::endl;
        actor_zeta::send(database, address(), "create", std::move(name_collection));
    }
};

class collection_t final : public actor_zeta::basic_async_actor {
public:
    collection_t(actor_zeta::supervisor_abstract* ptr, std::string& name)
        : actor_zeta::basic_async_actor(ptr, std::move(name)) {
        count_actor++;
    }
};

class database_t final : public actor_zeta::supervisor_abstract {
public:
    database_t(actor_zeta::supervisor_abstract* ptr, std::string name)
        : supervisor_abstract(ptr, std::move(name))
        , e_(ptr->executor()) {

    }

    auto executor_impl() noexcept -> actor_zeta::abstract_executor* final {
        return e_;
    }

    auto add_actor_impl(actor_zeta::actor t) -> void final {
        actors_.emplace_back(std::move(t));
    }

    auto add_supervisor_impl(actor_zeta::supervisor t) -> void final {
        std::cerr << "name : " << t.type() << std::endl;
        supervisor_.emplace_back(std::move(t));
    }

    auto enqueue_base(actor_zeta::message_ptr msg, actor_zeta::execution_device*) -> void final {
        set_current_message(std::move(msg));
        execute();
    }

private:
    abstract_executor* e_;
    std::vector<actor_zeta::actor> actors_;
    std::vector<actor_zeta::supervisor> supervisor_;
};

class mdb_t final : public actor_zeta::supervisor_abstract {
public:
    mdb_t()
        : supervisor_abstract("mdb")
        , e_(new dummy_executor(1, max_queue)) {
        e_->start();
        add_handler("create", &mdb_t::create);
    }

    void create(std::string& name) {
        std::cerr << "mdb_t::create : " << name << std::endl;
        actor_zeta::spawn_supervisor<database_t>(reinterpret_cast<actor_zeta::supervisor_abstract*>(this), current_message()->sender(), std::move(name));
    }

    auto executor_impl() noexcept -> actor_zeta::abstract_executor* final {
        return e_.get();
    }

    auto add_actor_impl(actor_zeta::actor t) -> void final {
        std::cerr << "add_actor_impl::add_actor_impl : " << t.type() << std::endl;
        actors_.emplace_back(std::move(t));
    }

    auto add_supervisor_impl(actor_zeta::supervisor t) -> void final {
        std::cerr << "add_supervisor_impl::add_supervisor_impl : " << t.type() << std::endl;
        supervisor_.emplace_back(std::move(t));
    }

    auto enqueue_base(actor_zeta::message_ptr msg, actor_zeta::execution_device*) -> void final {
        {
            set_current_message(std::move(msg));
            execute();
        }
    }

private:
    std::unique_ptr<abstract_executor> e_;
    std::vector<actor_zeta::actor> actors_;
    std::vector<actor_zeta::supervisor> supervisor_;
};

auto main() -> int {
    const auto sleep_time = std::chrono::milliseconds(60);
    auto mdb = actor_zeta::spawn_supervisor<mdb_t>();
    actor_zeta::spawn_actor<dispatcher_t>(mdb);
    actor_zeta::delegate_send(mdb, "dispatcher", "create_database", std::string("database_test"));
    actor_zeta::delegate_send(mdb, "dispatcher", "create_collection", std::string("database_test"), std::string("collection_test"));
    std::this_thread::sleep_for(sleep_time);

    return 0;
}
