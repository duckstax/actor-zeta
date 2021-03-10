#include <map>
#include <vector>
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
    dummy_executor():abstract_executor(1,10000){}

    void execute(actor_zeta::executable *ptr) override {
        ptr->run(nullptr, max_throughput());
    }
    void start() override{}
    void stop() override{}
};


class dummy_supervisor final : public supervisor_t {
public:

    dummy_supervisor(actor_zeta::abstract_executor*ptr)
        : supervisor_t("dummy_supervisor")
        , ptr_(ptr)
        {
    }

    auto executor() noexcept -> actor_zeta::abstract_executor* override  {
        return ptr_;
    }

     auto join(actor_zeta::actor) -> actor_zeta::actor_address override {
        return actor_zeta::actor_address();
    }

    void enqueue_base(actor_zeta::message_ptr, execution_device *) override {

    }

private:
    actor_zeta::abstract_executor*ptr_;
};

class storage_t final : public basic_async_actor {
public:
    storage_t(dummy_supervisor*ptr) : basic_async_actor(ptr, "storage") {
        add_handler(
                "update",
                 &storage_t::update
       );

        add_handler(
                "find",
                &storage_t::find
        );

        add_handler(
                "remove",
                &storage_t::remote
        );

        add_handler(
                "status",
                [](storage_t& ctx ){
                    ctx.status();
                }
        );

    }

    void status() {
        std::cerr << "status" << std::endl;
    }

    ~storage_t() override = default;

private:

    void update(std::string&data){
        std::cerr << "update:" << data << std::endl;
    }

    void find() {
        std::cerr << "find" << std::endl;
    }

    void remote(){
        std::cerr << "remote" << std::endl;
    }

};


int main() {
    std::unique_ptr<dummy_supervisor> supervisor(new dummy_supervisor(new dummy_executor));
    std::unique_ptr<storage_t> storage(new storage_t(supervisor.get()));
    send(storage, actor_zeta::actor_address(), "update", std::string("payload"));
    send(storage, actor_zeta::actor_address(), "find");
    send(storage, actor_zeta::actor_address(), "remove");
    send(storage, actor_zeta::actor_address(), "status");
    return 0;
}