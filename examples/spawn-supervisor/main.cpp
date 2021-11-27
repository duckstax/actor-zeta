#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/memory_resource.hpp>

using actor_zeta::detail::pmr::get_default_resource;
using actor_zeta::detail::pmr::memory_resource;

class manager_database_t;
class manager_dispatcher_t;
class database_t;

std::atomic_int count_actor;
std::atomic_int count_supervisor;
const int max_queue = 100;

#define TRACE(msg) \
    { std::cerr << __FILE__ << ":" << __LINE__ << "::" << __func__ << " : " << msg << std::endl; }

class dummy_executor final : public actor_zeta::abstract_executor {
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

auto thread_pool_deleter = [](dummy_executor* ptr) -> void {
    ptr->stop();
    delete ptr;
};

class dispatcher_t final : public actor_zeta::basic_async_actor {
public:
    dispatcher_t(manager_dispatcher_t* ptr, std::string name)
        : actor_zeta::basic_async_actor(ptr, std::move(name), 0) {
        count_actor++;
        add_handler("create_database", &dispatcher_t::create_database);
        add_handler("create_collection", &dispatcher_t::create_collection);
        add_handler("insert", &dispatcher_t::insert);
    }
    void insert(std::string& name, int key, int value) {
      ///  actor_zeta::send(address_book("collection_test"), address(), "insert", std::move(name), key, value);
    }

    void create_database(std::string& name) {
        std::cerr << "dispatcher_t::create_database : " << name << std::endl;
    ///    actor_zeta::send(address_book("mdb"), address(), "create", std::move(name));
    }

    void create_collection(std::string& name_database, std::string& name_collection) {
        std::cerr << "dispatcher_t::create_collection : "
                  << "database : " << name_database
                  << " collection : " << name_collection
                  << std::endl;
        ///auto database = address_book(name_database);
    ///    actor_zeta::send(database, address(), "create", std::move(name_collection));
    }
};

class collection_t final : public actor_zeta::basic_async_actor {
public:
    collection_t(database_t* ptr, std::string& name)
        : actor_zeta::basic_async_actor(ptr, std::move(name), 0) {
        count_actor++;
        add_handler("insert", [this](int key, int value) {
            std::cerr << "collection_t::insert : key : " << key << " value : " << value << std::endl;
            storage_.emplace(key, value);
        });
    }

private:
    std::unordered_map<int, int> storage_;
};

class database_t final : public actor_zeta::cooperative_supervisor<database_t> {
public:
    database_t(manager_database_t* ptr, std::string name, int64_t id);

    void create(std::string& name) {
        std::cerr << "database_t::create : " << name << std::endl;
        auto token = std::move(name);
        spawn_actor<collection_t>([this](collection_t* ptr) {
            actors_.emplace_back(ptr);
        },token);
    }

protected:
    auto executor_impl() noexcept -> actor_zeta::abstract_executor* final {
        return e_;
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_device*) -> void final {
        set_current_message(std::move(msg));
        execute();
    }

private:
    actor_zeta::abstract_executor* e_;
    std::vector<actor_zeta::actor> actors_;
};

class manager_database_t final : public actor_zeta::cooperative_supervisor<manager_database_t> {
public:
    manager_database_t(memory_resource* mr)
        : cooperative_supervisor(mr, "mdb", 0)
        , e_(new dummy_executor(1, max_queue)) {
        e_->start();
        add_handler("create", &manager_database_t::create);
        count_supervisor++;
    }

    void create(std::string& name) {
        std::cerr << "mdb_t::create : " << name << std::endl;
        spawn_supervisor<database_t>([this](database_t* ptr) {
            auto type = ptr -> type();
            supervisor_.emplace_back(ptr);
            std::cerr << "add_supervisor_impl::add_supervisor_impl : " << type << std::endl;
        },std::move(name),0);
    }

protected:
    auto executor_impl() noexcept -> actor_zeta::abstract_executor* final {
        return e_.get();
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_device*) -> void final {
        {
            set_current_message(std::move(msg));
            execute();
        }
    }

private:
    std::unique_ptr<actor_zeta::abstract_executor> e_;
    std::vector<actor_zeta::supervisor> supervisor_;
};

database_t::database_t(manager_database_t* ptr, std::string name, int64_t id)
    : cooperative_supervisor(ptr, std::move(name), id)
    , e_(ptr->executor()) {
    add_handler("create", &database_t::create);
    count_supervisor++;
}

class manager_dispatcher_t final : public actor_zeta::cooperative_supervisor<manager_dispatcher_t> {
public:
    manager_dispatcher_t(memory_resource* mr)
        : cooperative_supervisor(mr, "mdispatcher", 0)
        , e_(new dummy_executor(1, max_queue)) {
        e_->start();
        add_handler("create", &manager_dispatcher_t::create);
        count_supervisor++;
    }

    void create(std::string& name) {
        std::cerr << "mdispatcher_t::create : " << name << std::endl;
        auto dispather = spawn_actor<dispatcher_t>([this](dispatcher_t* ptr) {
            auto type = ptr->type();
            actors_.emplace_back(ptr);
            std::cerr << "mdispatcher_t::add_actor_impl : " << type << std::endl;
        },std::move(name));
        ///auto address_mdb = address_book("mdb");
        //actor_zeta::link(address_mdb, dispather);
    }

protected:
    auto executor_impl() noexcept -> actor_zeta::abstract_executor* final {
        return e_.get();
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_device*) -> void final {
        {
            set_current_message(std::move(msg));
            execute();
        }
    }

private:
    std::unique_ptr<actor_zeta::abstract_executor> e_;
    std::vector<actor_zeta::actor> actors_;
};

auto main() -> int {
    const auto sleep_time = std::chrono::milliseconds(60);
    auto* mr = get_default_resource();
    auto mdb = actor_zeta::spawn_supervisor<manager_database_t>(mr);
    auto md = actor_zeta::spawn_supervisor<manager_dispatcher_t>(mr);
    /*
    actor_zeta::link(mdb, mdispatcher);
    actor_zeta::send(mdispatcher, actor_zeta::address_t::empty_address(), "create", std::string("dispatcher"));
    actor_zeta::delegate_send(mdispatcher, "dispatcher", "create_database", std::string("database_test"));
    actor_zeta::delegate_send(mdispatcher, "dispatcher", "create_collection", std::string("database_test"), std::string("collection_test"));
    actor_zeta::delegate_send(mdispatcher, "dispatcher", "insert", std::string("collection_test"), 1, 5);
     */
    ///  std::this_thread::sleep_for(sleep_time);
    std::cerr << "Count Actor : " << count_actor << std::endl;
    std::cerr << "Count SuperVisor : " << count_supervisor << std::endl;
    return 0;
}