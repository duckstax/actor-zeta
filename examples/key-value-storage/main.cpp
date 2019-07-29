#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <iostream>

#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/basic_actor.hpp>
#include <actor-zeta/environment.hpp>
#include <actor-zeta/supervisor_heavy.hpp>
#include <actor-zeta/executor/abstract_executor.hpp>
#include <actor-zeta/network/fake_multiplexer.hpp>
#include <actor-zeta/actor/broker.hpp>
#include <actor-zeta/network_environment.hpp>
#include <actor-zeta/executor/executor.hpp>
#include <actor-zeta/executor/policy/work_sharing.hpp>

using actor_zeta::actor::make_handler;
using actor_zeta::actor::context;
using actor_zeta::messaging::make_message;
using actor_zeta::environment::abstract_environment;
using actor_zeta::actor::basic_async_actor;
using actor_zeta::actor::broker;
using actor_zeta::network::multiplexer;
using actor_zeta::environment::network_environment;
using actor_zeta::network::buffer;
using actor_zeta::actor::actor_address;
using actor_zeta::network::query_raw_t;
using actor_zeta::executor::executor;
using actor_zeta::executor::work_sharing;
using actor_zeta::executor::abstract_executor;
using actor_zeta::actor::context;
using actor_zeta::environment::abstract_environment;
using actor_zeta::actor::basic_async_actor;
using actor_zeta::environment::supervisor_heavy;
using actor_zeta::environment::environment;
using actor_zeta::environment::make_environment;

struct query_t final {
    actor_zeta::network::connection_identifying id;
    buffer commands;
    std::vector<buffer> parameter;
};


struct response_t final {
    actor_zeta::network::connection_identifying id;
    buffer r_;
};

/// protocol :
/// request  :  action.parameter1.parameter2.parameterN. ....
/// response :  action.parameter1.parameter2.parameterN. ....

class storage_t final : public basic_async_actor {
public:
    explicit storage_t(supervisor_heavy&ptr): basic_async_actor(ptr,"storage"){
        auto* self = this;
        add_handler(
                "update",
                [this, self](context &ctx, query_t &tmp) -> void {
                    std::cerr << "Operation:" << "update" <<std::endl;
                    auto status = update(tmp.parameter[0], tmp.parameter[1]);
                    assert(in("1qaz"));
                    assert(find("1qaz") == "7");
                    response_t response;
                    response.r_ = std::to_string(status);
                    response.id = tmp.id;
                    ctx.message().sender()->send(
                            make_message(
                                    actor_address(self),
                                    "write",
                                    std::move(response)
                            )
                    );
                }
        );

    }


    ~storage_t() override = default;

    auto find(const std::string& key) -> std::string {
            return storage_.at(key);
    }

    auto update(const std::string& key,const std::string& blob) -> bool {
        auto it = storage_.find(key);
        if(it == storage_.end()){
            storage_.emplace(key,blob);
        } else {
            storage_.at(blob);
        }
        return true;
    }

    ///check
    auto in(const std::string& /*key*/) -> bool {
        return true;
    }

    ///debug
    auto view() -> void {
        for(auto&i:storage_){
            std::cerr << i.first << " == " << i.second << std::endl;
        }
    }

    auto remove(const std::string& key) -> void {
        storage_.erase(key);
    }


private:
    std::unordered_map<std::string,std::string> storage_;

};


class fake_broker final : public basic_async_actor {
public:

    fake_broker(supervisor_heavy&ptr):basic_async_actor(ptr,"network"){
        add_handler(
                "read",
                [this](context &ctx, query_raw_t &query_raw) -> void {
                    std::cerr << "Operation:" << "read" <<std::endl;
                    auto raw = query_raw.raw;
                    std::vector<buffer> parsed_raw_request;
                    std::string delimiter(".");
                    size_t pos = 0;
                    std::string token;
                    while ((pos = raw.find(delimiter)) != std::string::npos) {
                        parsed_raw_request.emplace_back(raw.substr(0, pos));
                        raw.erase(0, pos + delimiter.length());
                    }
                    parsed_raw_request.push_back(raw);

                    query_t query_;

                    query_.commands = *(parsed_raw_request.begin());
                    parsed_raw_request.erase(parsed_raw_request.begin());
                    query_.parameter = std::move(parsed_raw_request);
                    query_.id = query_raw.id;

                    ctx->addresses("storage")->send(
                            make_message(
                                    actor_zeta::actor::actor_address(address()),
                                    std::string(query_.commands),
                                    std::move(query_)
                            )
                    );
                }
        );

        add_handler(
                "write",
                [this](context & /*ctx*/, response_t &response) -> void {
                    std::cerr << "Operation:" << "write" <<std::endl;
                }
        );

        add_handler(
                "close",
                [this](context & /*ctx*/, response_t &response) -> void {
                    std::cerr << "Operation:" << "close" <<std::endl;
                    multiplexer_->close(response.id);
                }
        );

    }

    ~fake_broker() final = default;
};

int main() {
    constexpr const std::size_t port =  5555;

    constexpr const char * host = "localhost";

    auto* multiplexer = new actor_zeta::network::fake_multiplexer;

    multiplexer->add_scenario(host,port)
    .add("update.1qaz.7",actor_zeta::network::client_state::read)

    .add(
            [](const std::string&buffer) -> bool {
                std::cerr << "Operation:" << "check write" <<std::endl;
                return "1" == buffer;
            },
            actor_zeta::network::client_state::write,
            0
    )
    .add(actor_zeta::network::client_state::close);

    auto environment =  make_environment<network_environment>(new executor<work_sharing>(1,std::numeric_limits<std::size_t>::max()),multiplexer);

    auto&supervisor = environment->supervisor<supervisor_heavy>(environment.get());

    auto storage = supervisor.join<storage_t>(supervisor);
    auto broker = supervisor.join<fake_broker>(supervisor);

    actor_zeta::actor::link(broker,storage);

    multiplexer->new_tcp_listener(host, port, broker->entry_point() );

    return environment->start();
}