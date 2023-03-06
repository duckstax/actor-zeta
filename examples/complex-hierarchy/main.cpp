#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <actor-zeta.hpp>

using actor_zeta::pmr::get_default_resource;
using actor_zeta::pmr::memory_resource;

class manager_database_t;
class manager_dispatcher_t;
class database_t;

std::atomic_int count_actor{0};
std::atomic_int count_supervisor{0};

std::atomic_int count_database{0};
std::atomic_int count_collection{0};
std::atomic_int count_dispatcher{0};

const int max_queue = 100;

auto thread_pool_deleter = [](actor_zeta::scheduler_abstract_t* ptr) {
    ptr->stop();
    delete ptr;
};

class collection_t final : public actor_zeta::cooperative_supervisor<database_t> {
public:
    collection_t(actor_zeta::pmr::memory_resource * resource, std::string name)
        : actor_zeta::cooperative_supervisor<collection_t>(resource){

    }

    void create(std::string& name) {
        std::cerr << "database_t::create : " << name << std::endl;
        auto token = std::move(name);
        auto tmp =  spawn_actor<collection_t>([this](collection_t* ptr) {
            actors_.emplace_back(ptr);
        },token,count_collection.fetch_add(1));
        actor_zeta::send(current_message()->sender(),address(),"add_address",tmp);
        address_book_.emplace(tmp.type(),tmp);
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* final {
        return e_;
    }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> bool final {
        set_current_message(std::move(msg));
        execute();
        return true;
    }

private:
    actor_zeta::scheduler_abstract_t* e_;
    std::vector<actor_zeta::actor> actors_;
    std::unordered_map<actor_zeta::detail::string_view,actor_zeta::address_t> address_book_;
    void add_link() {
        auto& address = current_message()->sender();
        if (address && this != address.get()) {
            auto name = address.type();
            address_book_.emplace(name, std::move(address));
        }
    }
};

class collection_part_t final : public actor_zeta::basic_actor<collection_part_t> {
public:
    collection_t(collection_t* ptr, std::string& name,int64_t id)
        : actor_zeta::basic_actor<collection_part_t>(ptr) {
        add_handler("insert", [this](int key, int value) {
            std::cerr << "collection_t::insert : key : " << key << " value : " << value << std::endl;
            storage_.emplace(key, value);
        });
        add_handler("add_link",&collection_t::add_link);
        count_actor++;
    }

private:
    std::unordered_map<int, int> storage_;
    std::unordered_map<actor_zeta::detail::string_view,actor_zeta::address_t> address_book_;
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