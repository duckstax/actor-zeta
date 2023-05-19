#pragma once

#include "test/tooltestsuites/scheduler_test.hpp"
#include <actor-zeta.hpp>
#include <iostream>
#include <list>

#define TRACE(msg) \
    { std::cout << __FILE__ << ":" << __LINE__ << "::" << __func__ << " : " << msg << std::endl; }

class storage_t;
class test_handlers;

enum class dummy_supervisor_command : uint64_t {
    create_storage = 1,
    create_test_handlers = 2
};

class dummy_supervisor final
    : public actor_zeta::cooperative_supervisor<dummy_supervisor> {
public:
    static uint64_t constructor_counter;
    static uint64_t destructor_counter;
    static uint64_t executor_impl_counter;
    static uint64_t add_actor_impl_counter;
    static uint64_t add_supervisor_impl_counter;
    static uint64_t enqueue_base_counter;

    explicit dummy_supervisor(actor_zeta::pmr::memory_resource* mr, uint64_t threads, uint64_t throughput)
        : actor_zeta::cooperative_supervisor<dummy_supervisor>(mr)
        , create_storage_(actor_zeta::make_behavior(resource(), dummy_supervisor_command::create_storage, this, &dummy_supervisor::create_storage))
        , create_test_handlers_(actor_zeta::make_behavior(resource(), dummy_supervisor_command::create_test_handlers, this, &dummy_supervisor::create_test_handlers))
        , executor_(new actor_zeta::test::scheduler_test_t(threads, throughput)) {
        scheduler()->start();
        constructor_counter++;
    }

    auto make_type() const noexcept -> const char* const {
        return "dummy_supervisor";
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case actor_zeta::make_message_id(dummy_supervisor_command::create_storage): {
                        create_storage_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(dummy_supervisor_command::create_test_handlers): {
                        create_test_handlers_(msg);
                        break;
                    }
                }
            });
    }

    auto scheduler_test() noexcept -> actor_zeta::test::scheduler_test_t* {
        return executor_.get();
    }

    void create_storage();
    void create_test_handlers();
    ~dummy_supervisor() override = default;

    void start() {}
    void stop() {}

    auto make_scheduler() noexcept -> actor_zeta::scheduler_abstract_t* {
        TRACE("+++");
        executor_impl_counter++;
        return executor_.get();
    }

    auto actors_count() const -> size_t {
        return actors_.size();
    }

    auto supervisors_count() const -> size_t {
        return supervisor_.size();
    }

    auto last_actor() -> actor_zeta::actor_t& {
        assert(actors_count() > 0);
        TRACE("+++");
        return actors_.back();
    }

    auto last_supervisor() -> actor_zeta::supervisor_t& {
        assert(supervisors_count() > 0);
        return supervisor_.back();
    }

    void enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) override {
        enqueue_base_counter++;
        set_current_message(std::move(msg));
        behavior()(current_message());
    }

private:
    actor_zeta::behavior_t create_storage_;
    actor_zeta::behavior_t create_test_handlers_;
    std::unique_ptr<actor_zeta::test::scheduler_test_t> executor_;
    std::list<actor_zeta::actor_t> actors_;
    std::list<actor_zeta::supervisor_t> supervisor_;
};

uint64_t dummy_supervisor::constructor_counter = 0;
uint64_t dummy_supervisor::destructor_counter = 0;

uint64_t dummy_supervisor::executor_impl_counter = 0;

uint64_t dummy_supervisor::add_actor_impl_counter = 0;
uint64_t dummy_supervisor::add_supervisor_impl_counter = 0;

uint64_t dummy_supervisor::enqueue_base_counter = 0;

enum class storage_names : uint64_t {
    init = 0x00,
    search,
    add,
    delete_table,
    create_table
};

class storage_t final : public actor_zeta::basic_actor<storage_t> {
public:
    static uint64_t constructor_counter;
    static uint64_t destructor_counter;

    static uint64_t init_counter;
    static uint64_t search_counter;
    static uint64_t add_counter;
    static uint64_t delete_table_counter;
    static uint64_t create_table_counter;

public:
    explicit storage_t(dummy_supervisor* ptr)
        : actor_zeta::basic_actor<storage_t>(ptr)
        , init_(actor_zeta::make_behavior(
              resource(),
              storage_names::init, this,
              &storage_t::init))
        , search_(actor_zeta::make_behavior(
              resource(),
              storage_names::search,
              this,
              &storage_t::search))
        , add_(actor_zeta::make_behavior(
              resource(),
              storage_names::add,
              this,
              &storage_t::add))
        , delete_table_(actor_zeta::make_behavior(
              resource(),
              storage_names::delete_table,
              this,
              &storage_t::delete_table))
        , create_table_(actor_zeta::make_behavior(
              resource(),
              storage_names::create_table,
              this,
              &storage_t::create_table)) {
        constructor_counter++;
    }

    auto make_type() const noexcept -> const char* const {
        return "storage";
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command().integer_value()) {
                    case actor_zeta::make_message_id(storage_names::init): {
                        init_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(storage_names::search): {
                        search_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(storage_names::add): {
                        add_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(storage_names::delete_table): {
                        delete_table_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(storage_names::create_table): {
                        create_table_(msg);
                        break;
                    }
                }
            });
    }

    ~storage_t() override {
        destructor_counter++;
    }

private:
    void init() {
        init_counter++;
        TRACE("+++");
    }

    void search(std::string& key) {
        search_counter++;
        std::cerr << __func__ << " :: "
                  << "key: " << key
                  << std::endl;
    }

    void add(const std::string& key, const std::string& value) {
        add_counter++;
        std::cerr << __func__ << " :: "
                  << "key: " << key << " | "
                  << "value: " << value << " | "
                  << std::endl;
    }

    void delete_table(const std::string& name, const std::string& path, int type) {
        delete_table_counter++;
        std::cerr << __func__ << " :: "
                  << "table name: " << name << " | "
                  << "path: " << path << " | "
                  << "type: " << type << " | "
                  << std::endl;
    }

    void create_table(const std::string& name, const std::string& path, int type, int time_sync) {
        create_table_counter++;
        std::cerr << __func__ << " :: "
                  << "table name: " << name << " | "
                  << "path: " << path << " | "
                  << "type: " << type << " | "
                  << "time_sync: " << time_sync << " | "
                  << std::endl;
    }

    actor_zeta::behavior_t init_;
    actor_zeta::behavior_t search_;
    actor_zeta::behavior_t add_;
    actor_zeta::behavior_t delete_table_;
    actor_zeta::behavior_t create_table_;
};

uint64_t storage_t::constructor_counter = 0;
uint64_t storage_t::destructor_counter = 0;

uint64_t storage_t::init_counter = 0;
uint64_t storage_t::search_counter = 0;
uint64_t storage_t::add_counter = 0;
uint64_t storage_t::delete_table_counter = 0;
uint64_t storage_t::create_table_counter = 0;

enum class test_handlers_names : uint64_t {
    ptr_0 = 0x00,
    ptr_1,
    ptr_2,
    ptr_3,
    ptr_4,
}; // namespace test_handlers_names

class test_handlers final : public actor_zeta::basic_actor<test_handlers> {
public:
    static uint64_t init_counter;

    static uint64_t ptr_0_counter;
    static uint64_t ptr_1_counter;
    static uint64_t ptr_2_counter;
    static uint64_t ptr_3_counter;
    static uint64_t ptr_4_counter;

public:
    test_handlers(dummy_supervisor* ptr)
        : actor_zeta::basic_actor<test_handlers>(ptr)
        , ptr_0_(actor_zeta::make_behavior(
              resource(),
              test_handlers_names::ptr_0,
              []() {
                  TRACE("+++");
                  ptr_0_counter++;
              }))
        , ptr_1_(actor_zeta::make_behavior(
              resource(),
              test_handlers_names::ptr_1,
              []() {
                  TRACE("+++");
                  ptr_1_counter++;
              }))
        , ptr_2_(actor_zeta::make_behavior(
              resource(),
              test_handlers_names::ptr_2,
              [](int&) {
                  TRACE("+++");
                  ptr_2_counter++;
              }))
        , ptr_3_(actor_zeta::make_behavior(
              resource(),
              test_handlers_names::ptr_3,
              [](int data_1, int& data_2) {
                  TRACE("+++");
                  std::cerr << "ptr_3 : " << data_1 << " : " << data_2 << std::endl;
                  ptr_3_counter++;
              }))
        , ptr_4_(actor_zeta::make_behavior(
              resource(),
              test_handlers_names::ptr_4,
              [](int data_1, int& data_2, const std::string& data_3) {
                  TRACE("+++");
                  std::cerr << "ptr_4 : " << data_1 << " : " << data_2 << " : " << data_3 << std::endl;
                  ptr_4_counter++;
              })) {
        init();
    }

    auto make_type() const noexcept -> const char* const {
        return "test_handlers";
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command().integer_value()) {
                    case actor_zeta::make_message_id(test_handlers_names::ptr_0): {
                        ptr_0_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(test_handlers_names::ptr_1): {
                        ptr_1_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(test_handlers_names::ptr_2): {
                        ptr_2_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(test_handlers_names::ptr_3): {
                        ptr_3_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(test_handlers_names::ptr_4): {
                        ptr_4_(msg);
                        break;
                    }
                    default: {
                        TRACE("+++");
                        break;
                    }
                }
            });
    }

    ~test_handlers() override = default;

private:
    void init() {
        TRACE("private init");
        init_counter++;
    }

    actor_zeta::behavior_t ptr_0_;
    actor_zeta::behavior_t ptr_1_;
    actor_zeta::behavior_t ptr_2_;
    actor_zeta::behavior_t ptr_3_;
    actor_zeta::behavior_t ptr_4_;
};

uint64_t test_handlers::init_counter = 0;

uint64_t test_handlers::ptr_0_counter = 0;
uint64_t test_handlers::ptr_1_counter = 0;
uint64_t test_handlers::ptr_2_counter = 0;
uint64_t test_handlers::ptr_3_counter = 0;
uint64_t test_handlers::ptr_4_counter = 0;

void dummy_supervisor::create_storage() {
    spawn_actor([this](storage_t* ptr) {
        TRACE("+++");
        actors_.emplace_back(ptr);
        add_actor_impl_counter++;
    });
}

void dummy_supervisor::create_test_handlers() {
    spawn_actor([this](test_handlers* ptr) {
        TRACE("+++");
        actors_.emplace_back(ptr);
        add_actor_impl_counter++;
    });
}