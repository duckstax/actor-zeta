#include <cstdio>
#include <cassert>

#include <map>
#include <vector>
#include <iostream>

#include <actor-zeta/core.hpp>
#include <actor-zeta/network/fake_multiplexer.hpp>

using actor_zeta::basic_async_actor;
using actor_zeta::supervisor;
using actor_zeta::context;
using actor_zeta::actor_address;

using actor_zeta::executor_t;
using actor_zeta::work_sharing;
using actor_zeta::abstract_executor;

using actor_zeta::network::multiplexer;
using actor_zeta::network::buffer;
using actor_zeta::network::query_raw_t;
using actor_zeta::network::fake_multiplexer;

using actor_zeta::environment::abstract_environment;

struct query_t final {
    actor_zeta::network::connection_identifying id;
    buffer commands;
    std::vector<buffer> parameter;
};


struct response_t final {
    actor_zeta::network::connection_identifying id;
    buffer r_;
};

class supervisor_network final : public supervisor {
public:
    supervisor_network(fake_multiplexer&multiplexer,abstract_executor* ptr)
            : supervisor(actor_zeta::detail::string_view("network"))
            , multiplexer_(multiplexer)
            , e_(ptr)
    {
        add_handler(
                "write",
                [this](context & /*ctx*/, response_t & response) -> void {
                    std::cerr << "Operation:" << "write" << std::endl;
                    multiplexer_.write(response.id,response.r_);
                }
        );

        add_handler(
                "read",
                [this](context & ctx, query_raw_t &query_raw) -> void {
                    std::cerr << "Operation:" << "read" << std::endl;
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
                    actor_zeta::actor::send(
                            ctx->addresses(actor_zeta::detail::string_view("storage")),
                            actor_zeta::actor::actor_address(address()),
                            std::string(query_.commands),
                            std::move(query_)
                    );
                }
        );

        add_handler(
                "close",
                [this](context & /*ctx*/, response_t &response) -> void {
                    std::cerr << "Operation:" << "close" << std::endl;
                    multiplexer_.close(response.id);
                }
        );

        constexpr const std::size_t port =  5555;

        constexpr const char * host = "localhost";

        multiplexer.new_tcp_listener(host, port, address() );
    }

    auto shutdown() noexcept -> void final {
        e_->stop();
    }

    auto startup() noexcept -> void final {
        e_->start();
    }

    auto executor() noexcept -> actor_zeta::executor::abstract_executor& final { return *e_;}

    auto broadcast(actor_zeta::messaging::message) -> bool final  {return false;}

    auto join(supervisor &) -> void final {}

    using actor_zeta::actor::supervisor::join;

    auto join(actor_zeta::actor::base_actor *t) -> actor_zeta::actor::actor_address final {
        actor_zeta::actor::actor tmp(t);
        auto addres = tmp->address();
        actors_.push_back(std::move(tmp));
        return addres;
    }

    auto enqueue(actor_zeta::messaging::message msg,actor_zeta::executor::execution_device *) -> void final {
        context tmp(this,std::move(msg));
        dispatch().execute(tmp);
    }


private:
    fake_multiplexer& multiplexer_;
    abstract_executor* e_;
    std::vector<actor_zeta::actor::actor> actors_;
};

/// protocol :
/// request  :  action.parameter1.parameter2.parameterN. ....
/// response :  action.parameter1.parameter2.parameterN. ....

class storage_t final : public basic_async_actor {
public:
    explicit storage_t(supervisor_network*ptr): basic_async_actor(ptr,"storage"){
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
                    actor_zeta::actor::send(
                            ctx.message().sender(),
                            actor_address(self),
                            "write",
                            std::move(response)
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
            it->second=blob;
        }
        return true;
    }

    ///check
    auto in(const std::string& key ) -> bool {
        return storage_.count(key);
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

int main() {
    constexpr const std::size_t port =  5555;

    constexpr const char * host = "localhost";

    std::unique_ptr<actor_zeta::network::fake_multiplexer> multiplexer(new actor_zeta::network::fake_multiplexer);

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

    std::unique_ptr<executor_t<work_sharing>> thread_pool( new executor_t<work_sharing>(1,std::numeric_limits<std::size_t>::max()));

    std::unique_ptr<supervisor_network>supervisor( new supervisor_network(*multiplexer,thread_pool.get()));

    auto storage = supervisor->join<storage_t>(supervisor.get());

    actor_zeta::actor::link(supervisor,storage);

    supervisor->startup();

    return  multiplexer->start();
}