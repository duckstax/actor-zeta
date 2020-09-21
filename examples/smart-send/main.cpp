#include <cassert>

#include <unordered_set>
#include <queue>
#include <vector>
#include <iostream>
#include <memory>

#include <actor-zeta.hpp>

using actor_zeta::basic_async_actor;
using actor_zeta::abstract_executor;
using actor_zeta::supervisor;
using actor_zeta::join;

using actor_zeta::abstract_executor;
using actor_zeta::executor_t;
using actor_zeta::work_sharing;

using actor_zeta::message;
using actor_zeta::make_message;


template<typename Task, typename ...Args>
inline auto make_task(supervisor&executor_,const std::string &command, Args... args ) -> void {
    executor_->enqueue(std::move(make_message(executor_.address(), command, std::move(Task(std::forward<Args>(args)...)))));
}

template<typename Task, typename ...Args>
inline auto make_task_broadcast(supervisor&executor_,const std::string &command, Args... args ) -> void {
    executor_->broadcast(std::move(make_message(executor_.address(), command, std::move(Task(std::forward<Args>(args)...)))));
}

auto thread_pool_deleter = [](abstract_executor* ptr){
    ptr->stop();
    delete ptr;
};

/// non thread safe
class supervisor_lite final : public actor_zeta::abstract_supervisor {
public:
    explicit supervisor_lite()
            : abstract_supervisor("network")
            , e_(new executor_t<work_sharing>(
                    1,
                    std::numeric_limits<std::size_t>::max()
                 ),
                 thread_pool_deleter
            )
            , cursor(0)
            , system_{"sync_contacts", "add_link", "remove_link"}
            {
                e_->start();
    }

    auto join(actor_zeta::supervisor) -> actor_zeta::actor_address override {
        return actor_zeta::actor_address();
    }

    ~supervisor_lite() override {
        e_->stop();
    }

    auto executor() noexcept -> actor_zeta::abstract_executor & final { return *e_; }

    auto join(actor_zeta::actor t) -> actor_zeta::actor_address final {
        auto tmp = std::move(t);
        auto address = tmp->address();
        actors_.push_back(std::move(tmp));
        return address;
    }

    auto enqueue(message msg, actor_zeta::execution_device *) -> void final {
        auto msg_ = std::move(msg);
        auto it = system_.find(msg_.command());
        if (it != system_.end()) {
            local(std::move(msg_));
        } else {
            redirect_robin(std::move(msg_));
        }
    }

private:
    auto local(message msg) -> void {
        set_current_message(std::move(msg));
        dispatch().execute(*this);
    }

    auto redirect_robin(message msg) -> void {
        if (!actors_.empty()) {
            actors_[cursor]->enqueue(std::move(msg));
            ++cursor;
            if (cursor >= actors_.size()) {
                cursor = 0;
            }
        }
        //assert(false);
    }

    std::unique_ptr<abstract_executor,decltype(thread_pool_deleter)> e_;
    std::vector<actor_zeta::actor> actors_;
    std::size_t cursor;
    std::unordered_set<actor_zeta::detail::string_view> system_;
};


struct download_data final {

    download_data(const std::string &url, const std::string &user, const std::string &passwod)
        : url_(url)
        , user_(user)
        , passwod_(passwod) {}

    ~download_data() = default;
    std::string url_;
    std::string user_;
    std::string passwod_;
};

struct work_data final {

    ~work_data() = default;

    work_data(const std::string &data, const std::string &operatorName) : data_(data), operator_name_(operatorName) {}

    std::string data_;
    std::string operator_name_;
};

class worker_t final : public basic_async_actor {
public:
    explicit worker_t(supervisor &ref) : basic_async_actor(ref, "bot") {

        add_handler(
                "download",
                &worker_t::download
        );

        add_handler(
                "work_data",
                &worker_t::work_data
        );
    }

    void download(download_data &url){
        std::cerr << "url : " << url.url_ << std::endl;
        std::cerr << "user : " << url.user_ << std::endl;
        std::cerr << "password : " << url.passwod_ << std::endl;
    }

    void work_data(work_data & work_data) {
        std::cerr << "data_ : " << work_data.data_ << std::endl;
        std::cerr << "operator_name : " << work_data.operator_name_ << std::endl;
    }

    ~worker_t() override = default;

private:

};

int main() {

     actor_zeta::supervisor s(new supervisor_lite());

    int const actors = 10;

    for (auto i = actors - 1; i > 0; --i) {
        auto bot = join<worker_t>(s);
        actor_zeta::link(s, bot);
    }

    int const task = 10000;

    for (auto i = task - 1; i > 0; --i) {
        make_task<download_data>(s,"download", "fb", "jack","");
    }

    for (auto i = task - 1; i > 0; --i) {
        make_task_broadcast<download_data>(s,"work_data", "fb", "jack","");
    }

    return 0;
}