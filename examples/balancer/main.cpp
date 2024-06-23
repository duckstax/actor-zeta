#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <actor-zeta.hpp>

std::atomic_int count_collection_part{0};
std::atomic_int count_collection{0};
std::atomic_int count_balancer{0};
std::atomic_int count_insert{0};
std::atomic_int count_find{0};

auto thread_pool_deleter = [](actor_zeta::scheduler_abstract_t* ptr) {
    ptr->stop();
    delete ptr;
};

class collection_part_t;

enum class collection_method : uint64_t {
    insert = 0x00,
    remove,
    update,
    find
};

class collection_t final : public actor_zeta::cooperative_supervisor<collection_t> {
public:
    collection_t(actor_zeta::pmr::memory_resource* resource, actor_zeta::scheduler_abstract_t* scheduler)
        : actor_zeta::cooperative_supervisor<collection_t>(resource)
        , e_(scheduler) {
        ++count_collection;
    }

    void create() {
        spawn_actor([this](collection_part_t* ptr) {
            actors_.emplace_back(ptr);
        });
    }

    const char* make_type() const noexcept {
        return "collection";
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case actor_zeta::make_message_id(collection_method::insert):
                    case actor_zeta::make_message_id(collection_method::remove):
                    case actor_zeta::make_message_id(collection_method::update):
                    case actor_zeta::make_message_id(collection_method::find): {
                        auto index = cursor_ % actors_.size();
                        actors_[index]->enqueue(current_message_own());
                        ++cursor_;
                        ++count_balancer;
                        break;
                    }
                    default: {
                        std::cerr << "unknown command" << std::endl;
                    }
                }
            });
    }

    auto make_scheduler() noexcept -> actor_zeta::scheduler_abstract_t* {
        return e_;
    }

protected:
    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        set_current_message(std::move(msg));
        behavior()(current_message());
    }

private:
    actor_zeta::scheduler_abstract_t* e_;
    uint32_t cursor_ = 0;
    std::vector<actor_zeta::actor_t> actors_;
};

class collection_part_t final : public actor_zeta::basic_actor<collection_part_t> {
public:
    collection_part_t(collection_t* ptr)
        : actor_zeta::basic_actor<collection_part_t>(ptr)
        , insert_(actor_zeta::make_behavior(resource(), collection_method::insert, [this](std::string& key, std::string& value) -> void {
            data_.emplace(key, value);
            std::cerr << id() << " " << key << " " << value << std::endl;
            ++count_insert;
        }))
        , remove_(actor_zeta::make_behavior(resource(), collection_method::remove, [this](std::string& key) -> void {
            data_.erase(key);
        }))
        , update_(actor_zeta::make_behavior(resource(), collection_method::update, [this](std::string& key, std::string& value) -> void {
            data_[key] = value;
        }))
        , find_(actor_zeta::make_behavior(resource(), collection_method::find, [this](std::string& key) -> std::string {
            return data_[key];
        })) {
        ++count_collection_part;
    }

    const char* make_type() const noexcept {
        return "collection";
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case actor_zeta::make_message_id(collection_method::insert): {
                        insert_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(collection_method::remove): {
                        remove_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(collection_method::update): {
                        update_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(collection_method::find): {
                        find_(msg);
                        break;
                    }
                }
            });
    }

private:
    actor_zeta::behavior_t insert_;
    actor_zeta::behavior_t remove_;
    actor_zeta::behavior_t update_;
    actor_zeta::behavior_t find_;
    std::unordered_map<std::string, std::string> data_;
};

static constexpr auto sleep_time = std::chrono::milliseconds(60);

auto main() -> int {
    auto* resource = actor_zeta::pmr::get_default_resource();
    std::unique_ptr<actor_zeta::scheduler_abstract_t, decltype(thread_pool_deleter)> scheduler(
        new actor_zeta::scheduler_t<actor_zeta::work_sharing>(1, 100),
        thread_pool_deleter);
    auto collection = actor_zeta::spawn_supervisor<collection_t>(resource, scheduler.get());
    collection->create();
    collection->create();
    collection->create();
    actor_zeta::send(collection, actor_zeta::address_t::empty_address(), collection_method::insert, std::string("1"), std::string("5"));
    actor_zeta::send(collection, actor_zeta::address_t::empty_address(), collection_method::insert, std::string("1"), std::string("5"));
    actor_zeta::send(collection, actor_zeta::address_t::empty_address(), collection_method::insert, std::string("1"), std::string("5"));

    scheduler->start();

    std::this_thread::sleep_for(sleep_time);

    std::cerr << "Count Collection : " << count_collection << std::endl;
    std::cerr << "Count Collection Part : " << count_collection_part << std::endl;
    std::cerr << "Count Balancer : " << count_balancer << std::endl;
    std::cerr << "Count Insert : " << count_balancer << std::endl;

    return 0;
}