#include <iostream>

#include <actor-zeta.hpp>

using actor_zeta::basic_async_actor;
using actor_zeta::send;
using actor_zeta::abstract_executor;
using actor_zeta::supervisor_t;
using actor_zeta::message;
using actor_zeta::execution_device;

class dummy_executor final : public abstract_executor {
public:
    dummy_executor() : abstract_executor(1, 10000) {}

    void execute(actor_zeta::executable *ptr) override {
        ptr->run(nullptr, max_throughput());
    }

    void start() override {}

    void stop() override {}
};


class dummy_supervisor final : public supervisor_t {
public:

    explicit dummy_supervisor(actor_zeta::abstract_executor *ptr)
            : supervisor_t("dummy_supervisor"), ptr_(ptr) {
    }

    auto executor() noexcept -> actor_zeta::abstract_executor * override {
        return ptr_;
    }

    auto join(actor_zeta::actor ) -> actor_zeta::actor_address override {
        return actor_zeta::actor_address();
    }

    void enqueue_base(actor_zeta::message_ptr, execution_device *) override {

    }

private:
    actor_zeta::abstract_executor *ptr_;
};


class storage_t final : public basic_async_actor {
public:
    explicit storage_t(dummy_supervisor *ptr) : basic_async_actor(ptr, "storage") {

        add_handler(
                "init",
                &storage_t::init
        );

        add_handler(
                "search",
                &storage_t::search
        );

        add_handler(
                "add",
                &storage_t::add
        );

        add_handler(
                "delete_table",
                &storage_t::delete_table
        );

        add_handler(
                "creature_table",
                &storage_t::creature_table
        );

    }

    ~storage_t() override = default;

private:
    void init() {
        std::cerr << "init " << std::endl;
    }

    void search(std::string &key) {
        std::cerr << "search: "
                  << "key: " << key
                  << std::endl;
    }

    void add(const std::string &key, const std::string &value) {
        std::cerr << "add: "
                  << "key: " << key << " | "
                  << "value: " << value << " | "
                  << std::endl;
    }

    void delete_table(const std::string &name, const std::string &path, int type) {
        std::cerr << "delete_table: "
                  << "table name: " << name << " | "
                  << "path: " << path << " | "
                  << "type: " << type << " | "
                  << std::endl;
    }

    void creature_table(const std::string &name, const std::string &path, int type, int time_sync) {
        std::cerr << "creature_table: "
                  << "table name: " << name << " | "
                  << "path: " << path << " | "
                  << "type: " << type << " | "
                  << "time_sync: " << time_sync << " | "
                  << std::endl;
    }

};

class test_handlers final : public basic_async_actor {
public:
    test_handlers(dummy_supervisor *ptr) : basic_async_actor(ptr, "test_handlers") {
        add_handler(
                "ptr_0",
                []() {
                    std::cerr << "ptr_0" << std::endl;
                }
        );

        add_handler(
                "ptr_1",
                [this](int &data) {
                    init();
                    std::cerr << "ptr_2 :" << data << std::endl;
                }
        );
        add_handler(
                "ptr_2",
                [this](int& data_1, int &data_2) {
                    init();
                    std::cerr << "ptr_3 : " << data_1 << " : " << data_2 << std::endl;
                }
        );

        add_handler(
                "ptr_3",
                [this](int data_1, int &data_2, const std::string &data_3) {
                    init();
                    std::cerr << "ptr_4 : " << data_1 << " : " << data_2 << " : " << data_3 << std::endl;
                }
        );
    }

    ~test_handlers() override = default;

private:
    void init() {
        std::cerr << "private init" << std::endl;
    }
};


int main() {

    std::unique_ptr<dummy_supervisor> supervisor(new dummy_supervisor(new dummy_executor));

    std::unique_ptr<test_handlers> test_handlers_(new test_handlers(supervisor.get()));
    send(test_handlers_, actor_zeta::actor_address(), "ptr_0");
    send(test_handlers_, actor_zeta::actor_address(), "ptr_1", 1);
    send(test_handlers_, actor_zeta::actor_address(), "ptr_2", 1, 2);
    send(test_handlers_, actor_zeta::actor_address(), "ptr_3", 1, 2, std::string("test"));

    std::unique_ptr<storage_t> storage(new storage_t(supervisor.get()));

    send(storage, actor_zeta::actor_address(), "init");
    send(storage, actor_zeta::actor_address(), "search", std::string("key_1"));
    send(storage, actor_zeta::actor_address(), "add", std::string("key_1"), std::string("value_1"));
    send(storage, actor_zeta::actor_address(), "delete_table", std::string("test"), std::string("/"), 12);
    send(storage, actor_zeta::actor_address(), "creature_table", std::string("test"), std::string("/"), 1, 12);

    return 0;
}