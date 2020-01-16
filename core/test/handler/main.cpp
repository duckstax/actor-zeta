#include <iostream>

#include <actor-zeta/core.hpp>

using actor_zeta::basic_async_actor;
using actor_zeta::context;
using actor_zeta::send;
using actor_zeta::abstract_executor;
using actor_zeta::supervisor;
using actor_zeta::message;
using actor_zeta::execution_device;
using actor_zeta::actor::context;
using actor_zeta::actor::handler;
using actor_zeta::actor::make_handler;

class dummy_context final : public context {
public:
    dummy_context(actor_zeta::messaging::message msg) : message_(std::move(msg)) {}

    ~dummy_context() override = default;

    auto addresses(actor_zeta::detail::string_view) -> actor_zeta::actor::actor_address & override {
        return address_;
    }

    auto self() -> actor_zeta::actor::actor_address override {
        return address_;
    };

    auto current_message() -> actor_zeta::messaging::message & override {
        return message_;
    };
private:
    actor_zeta::actor::actor_address address_;
    actor_zeta::messaging::message message_;
};

class dummy_executor final : public abstract_executor {
public:
    dummy_executor() : abstract_executor(1, 10000) {}

    void execute(actor_zeta::executable *ptr) override {
        ptr->run(nullptr, max_throughput());
    }

    void start() override {}

    void stop() override {}
};


class dummy_supervisor final : public supervisor {
public:

    dummy_supervisor(actor_zeta::abstract_executor *ptr)
            : supervisor("dummy_supervisor"), ptr_(ptr) {
    }

    auto executor() noexcept -> actor_zeta::abstract_executor & override {
        return *ptr_;
    }

    auto join(actor_zeta::abstract_actor *) -> actor_zeta::actor::actor_address override {
        return actor_zeta::actor_address();
    }

    void enqueue(message, execution_device *) override {

    }

private:
    actor_zeta::abstract_executor *ptr_;
};


class storage_t final : public basic_async_actor {
public:
    storage_t(dummy_supervisor &ref) : basic_async_actor(ref, "storage") {

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


int main() {
    actor_zeta::actor::actor_address address_tmp;

    auto *ptr_0 = make_handler(
            []() {
                std::cerr << "ptr_0" << std::endl;
            }

    );

    dummy_context tmp_0(actor_zeta::make_message(address_tmp, ""));

    ptr_0->invoke(tmp_0);

    auto *ptr_1 = make_handler(
            [](context &) {
                std::cerr << "ptr_1" << std::endl;
            }

    );

    dummy_context tmp_1(actor_zeta::make_message(address_tmp, "", 6));

    ptr_1->invoke(tmp_1);

    auto *ptr_2 = make_handler(
            [](context &, int &data) {
                std::cerr << "ptr_2 :" << data << std::endl;
            }

    );

    dummy_context tmp_2(actor_zeta::make_message(address_tmp, "", 6));

    ptr_2->invoke(tmp_2);

    auto *ptr_3 = make_handler(
            [](context &, int data_1, int &data_2) {
                std::cerr << "ptr_3 : " << data_1 << " : " << data_2 << std::endl;
            }

    );

    dummy_context tmp_3(actor_zeta::make_message(address_tmp, "", 6, 7));

    ptr_3->invoke(tmp_3);

    auto *ptr_4 = make_handler(
            [](context &, int data_1, int &data_2, const std::string &data_3) {
                std::cerr << "ptr_4 : " << data_1 << " : " << data_2 << " : " << data_3 << std::endl;
            }

    );

    dummy_context tmp_4(actor_zeta::make_message(address_tmp, "", 6, 7, std::string("1qaz")));

    ptr_4->invoke(tmp_4);


    std::unique_ptr<dummy_supervisor> supervisor(new dummy_supervisor(new dummy_executor));
    std::unique_ptr<storage_t> storage(new storage_t(*supervisor));
    send(storage, actor_zeta::actor::actor_address(), "init");
    send(storage, actor_zeta::actor::actor_address(), "search", std::string("key_1"));
    send(storage, actor_zeta::actor::actor_address(), "add", std::string("key_1"), std::string("value_1"));
    send(storage, actor_zeta::actor::actor_address(), "delete_table", std::string("test"), std::string("/"), 12);
    send(storage, actor_zeta::actor::actor_address(), "creature_table", std::string("test"), std::string("/"), 1, 12);
    return 0;
}