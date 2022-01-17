#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/string_view.hpp>
#include <actor-zeta/detail/memory_resource.hpp>

using actor_zeta::detail::pmr::get_default_resource;
using actor_zeta::detail::pmr::memory_resource;

class manager_database_t;
class manager_dispatcher_t;
class database_t;

std::atomic_int count_actor{0};
std::atomic_int count_supervisor{0};

std::atomic_int count_database{0};
std::atomic_int count_collection{0};
std::atomic_int count_dispatcher{0};

const int max_queue = 100;

class dispatcher_t final : public actor_zeta::basic_async_actor {
public:
    dispatcher_t(manager_dispatcher_t* ptr, std::string name,actor_zeta::address_t manager_database )
        : actor_zeta::basic_async_actor(ptr, std::move(name))
        , manager_database_(manager_database) {
        count_actor++;
        add_handler("create_database", &dispatcher_t::create_database);
        add_handler("create_collection", &dispatcher_t::create_collection);
        add_handler("insert", &dispatcher_t::insert);
        add_handler("add_link",&dispatcher_t::add_link);
        add_handler("add_address",&dispatcher_t::add_address);
    }
    void insert(std::string& name, int key, int value) {
        auto collection_name = std::move(name);
        auto collection = address_book_.at({collection_name.data(),collection_name.size()});
        actor_zeta::send(collection, address(), "insert", key, value);
    }

    void create_database(std::string& name) {
        std::cerr << "dispatcher_t::create_database : " << name << std::endl;
        actor_zeta::send(manager_database_, address(), "create", std::move(name));
    }

    void create_collection(std::string& name_database, std::string& name_collection) {
        std::cerr << "dispatcher_t::create_collection : "
                  << "database : " << name_database
                  << " collection : " << name_collection
                  << std::endl;
        auto database = address_book_.at({name_database.data(),name_database.size()});
        actor_zeta::send(database, address(), "create", std::move(name_collection));
    }

private:
    actor_zeta::address_t manager_database_;
    std::unordered_map<actor_zeta::detail::string_view,actor_zeta::address_t> address_book_;

    void add_link() {
        auto& address = current_message()->sender();
        if (address && this != address.get()) {
            auto name = address->type();
            address_book_.emplace(name, std::move(address));
        }
    }

    void add_address(actor_zeta::address_t address) {
        if (address && this != address.get()) {
            auto name = address->type();
            address_book_.emplace(name, std::move(address));
        }
    }
};

class collection_t final : public actor_zeta::basic_async_actor {
public:
    collection_t(database_t* ptr, std::string& name)
        : actor_zeta::basic_async_actor(ptr, std::move(name)) {
        count_actor++;
        add_handler("insert", [this](int key, int value) {
            std::cerr << "collection_t::insert : key : " << key << " value : " << value << std::endl;
            storage_.emplace(key, value);
        });
        add_handler("add_link",&collection_t::add_link);
    }

private:
    std::unordered_map<int, int> storage_;
    std::unordered_map<actor_zeta::detail::string_view,actor_zeta::address_t> address_book_;
    void add_link() {
        auto& address = current_message()->sender();
        if (address && this != address.get()) {
            auto name = address->type();
            address_book_.emplace(name, std::move(address));
        }
    }
};

class database_t final : public actor_zeta::cooperative_supervisor<database_t> {
public:
    database_t(manager_database_t* ptr, std::string name);

    void create(std::string& name) {
        std::cerr << "database_t::create : " << name << std::endl;
        auto token = std::move(name);
        auto tmp =  spawn_actor<collection_t>([this](collection_t* ptr) {
            actors_.emplace_back(ptr);
        },token);
        actor_zeta::send(current_message()->sender(),address(),"add_address",tmp);
        address_book_.emplace(tmp->type(),tmp);
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* final {
        return e_;
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        set_current_message(std::move(msg));
        execute();
    }

private:
    actor_zeta::scheduler_abstract_t* e_;
    std::vector<actor_zeta::actor> actors_;
    std::unordered_map<actor_zeta::detail::string_view,actor_zeta::address_t> address_book_;
    void add_link() {
        auto& address = current_message()->sender();
        if (address && this != address.get()) {
            auto name = address->type();
            address_book_.emplace(name, std::move(address));
        }
    }
};

auto thread_pool_deleter = [](actor_zeta::scheduler_abstract_t* ptr) {
    ptr->stop();
    delete ptr;
};

class manager_database_t final : public actor_zeta::cooperative_supervisor<manager_database_t> {
public:
    manager_database_t(memory_resource* mr)
        : cooperative_supervisor(mr, "mdb")
        , e_(new actor_zeta::scheduler_t<actor_zeta::work_sharing>(
                 1,
                 100),
             thread_pool_deleter){
        add_handler("create", &manager_database_t::create);
        add_handler("add_link",&manager_database_t::add_link);
        e_->start();
        count_supervisor++;
    }

    void create(std::string& name) {
        std::cerr << "mdb_t::create : " << name << std::endl;
        auto db = spawn_supervisor<database_t>([this](database_t* ptr) {
            auto type = ptr -> type();
            supervisor_.emplace_back(ptr);
            std::cerr << "add_supervisor_impl::add_supervisor_impl : " << type << std::endl;
        },std::move(name));
        actor_zeta::send(current_message()->sender(),address(),"add_address",db);
        address_book_.emplace(db->type(),db);
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* final {
        return e_.get();
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            execute();
        }
    }

private:
    std::unique_ptr<actor_zeta::scheduler_abstract_t, decltype(thread_pool_deleter)> e_;
    std::vector<actor_zeta::supervisor> supervisor_;
    std::unordered_map<actor_zeta::detail::string_view,actor_zeta::address_t> address_book_;
    void add_link() {
        auto& address = current_message()->sender();
        if (address && this != address.get()) {
            auto name = address->type();
            address_book_.emplace(name, std::move(address));
        }
    }
};

database_t::database_t(manager_database_t* ptr, std::string name)
    : cooperative_supervisor(ptr, std::move(name))
    , e_(ptr->scheduler()) {
    add_handler("create", &database_t::create);
    add_handler("add_link",&database_t::add_link);
    count_supervisor++;
}

class manager_dispatcher_t final : public actor_zeta::cooperative_supervisor<manager_dispatcher_t> {
public:
    manager_dispatcher_t(memory_resource* mr)
        : cooperative_supervisor(mr, "mdispatcher")
        , e_(new actor_zeta::scheduler_t<actor_zeta::work_sharing>(
                 1,
                 100),
             thread_pool_deleter){
        add_handler("create", &manager_dispatcher_t::create);
        add_handler("add_link",&manager_dispatcher_t::add_link);
        add_handler("create_database", &manager_dispatcher_t::create_database);
        add_handler("create_collection", &manager_dispatcher_t::create_collection);
        add_handler("insert", &manager_dispatcher_t::insert);
        e_->start();
        count_supervisor++;
    }
    void insert( std::string& database,std::string& name, int key, int value) {
        actor_zeta::send(dispathers_[0], address(), "insert",std::move(database), std::move(name), key, value);
    }

    void create_database(std::string& name) {
        std::cerr << "dispatcher_t::create_database : " << name << std::endl;
        actor_zeta::send(dispathers_[0], address(), "create_database", std::move(name));
    }

    void create_collection(std::string& name_database, std::string& name_collection) {
        std::cerr << "dispatcher_t::create_collection : "
                  << "database : " << name_database
                  << " collection : " << name_collection
                  << std::endl;
        actor_zeta::send(dispathers_[0], address(), "create_collection", std::move(name_database), std::move(name_collection));
    }

    void create(std::string& name) {
        std::cerr << "mdispatcher_t::create : " << name << std::endl;
        auto dispather = spawn_actor<dispatcher_t>([this](dispatcher_t* ptr) {
            auto type = ptr->type();
            actors_.emplace_back(ptr);
            std::cerr << "mdispatcher_t::add_actor_impl : " << type << std::endl;
        },std::move(name),address_book_.at("mdb"));
        actor_zeta::send(address_book_.at("mdb"), dispather,"add_link");
        dispathers_.emplace_back(dispather);
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* final {
        return e_.get();
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        {
            set_current_message(std::move(msg));
            execute();
        }
    }

private:
    std::unique_ptr<actor_zeta::scheduler_abstract_t, decltype(thread_pool_deleter)> e_;
    std::vector<actor_zeta::actor> actors_;
    std::unordered_map<actor_zeta::detail::string_view,actor_zeta::address_t> address_book_;
    std::vector<actor_zeta::address_t> dispathers_;

    void add_link() {
        auto& address = current_message()->sender();
        if (address && this != address.get()) {
            auto name = address.type();
            address_book_.emplace(name, std::move(address));
        }
    }
};

static constexpr auto sleep_time = std::chrono::milliseconds(60);
static constexpr auto sleep_milliseconds_time = std::chrono::milliseconds(10);

auto main() -> int {

    auto* resource = get_default_resource();
    auto manager_database = actor_zeta::spawn_supervisor<manager_database_t>(resource);
    auto manager_dispatcher = actor_zeta::spawn_supervisor<manager_dispatcher_t>(resource);

    actor_zeta::send(manager_dispatcher, manager_database->address(), "add_link");
    std::this_thread::sleep_for(sleep_milliseconds_time);
    actor_zeta::send(manager_database, manager_dispatcher->address(), "add_link");
    std::this_thread::sleep_for(sleep_milliseconds_time);
    actor_zeta::send(manager_dispatcher, actor_zeta::address_t::empty_address(), "create", std::string("dispatcher"));
    std::this_thread::sleep_for(sleep_milliseconds_time);
    actor_zeta::send(manager_dispatcher, actor_zeta::address_t::empty_address(), "create_database", std::string("database_test"));
    std::this_thread::sleep_for(sleep_milliseconds_time);
    actor_zeta::send(manager_dispatcher, actor_zeta::address_t::empty_address(), "create_collection", std::string("database_test"), std::string("collection_test"));
    std::this_thread::sleep_for(sleep_milliseconds_time);
    actor_zeta::send(manager_dispatcher, actor_zeta::address_t::empty_address(), "insert", std::string("database_test"),std::string("collection_test"), 1, 5);

    std::this_thread::sleep_for(sleep_time);

    std::cerr << "Count Actor : " << count_actor << std::endl;
    std::cerr << "Count SuperVisor : " << count_supervisor << std::endl;
    std::cerr << "Count DataBase : " << count_database << std::endl;
    std::cerr << "Count Collection : " << count_collection << std::endl;
    std::cerr << "Count Dispatcher : " << count_dispatcher << std::endl;

    return 0;
}