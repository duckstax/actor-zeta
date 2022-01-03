#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <unordered_set>
#include <vector>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/memory_resource.hpp>

auto thread_pool_deleter = [](actor_zeta::scheduler_abstract_t* ptr) {
    ptr->stop();
    delete ptr;
};

static std::atomic<uint64_t> counter_download_data{0};
static std::atomic<uint64_t> counter_work_data{0};
static std::atomic<uint64_t> create_counter_worker{0};

class supervisor_lite;

class worker_t final : public actor_zeta::actor_schedule<worker_t> {
public:
    worker_t(supervisor_lite* ptr, int64_t actor_id)
        : actor_zeta::actor_schedule<worker_t>(ptr, "bot", actor_id) {

        behavior([this](actor_zeta::behavior_t&behavior) {
            add_handler(behavior,"download", &worker_t::download);
            add_handler(behavior,"work_data", &worker_t::work_data);
        });
    }

    void download(const std::string& url, const std::string& user, const std::string& passwod) {
        tmp_ = url;
        counter_download_data++;
    }

    void work_data(const std::string& data, const std::string& operatorName) {
        tmp_ = data;
        counter_work_data++;
    }

    ~worker_t() override = default;

private:
    std::string tmp_;
};

using actor_zeta::detail::pmr::memory_resource;
/// non thread safe
class supervisor_lite final : public actor_zeta::cooperative_supervisor<supervisor_lite> {
public:
    explicit supervisor_lite(memory_resource* ptr)
        : cooperative_supervisor(ptr, "network", 0)
        , e_(new actor_zeta::scheduler_t<actor_zeta::work_sharing>(
                 1,
                 100),
             thread_pool_deleter)
        , cursor(0)
        , system_{
              "sync_contacts",
              "add_link",
              "remove_link",
              "broadcast", "create"} {
        behavior([this](actor_zeta::behavior_t&behavior) {
            add_handler(behavior,"create", &supervisor_lite::create);
            add_handler(behavior,"broadcast", &supervisor_lite::broadcast_impl);
        });
        e_->start();
    }

    void create() {
        spawn_actor<worker_t>([this](worker_t* ptr) {
            actors_.emplace_back(ptr);
        },create_counter_worker.fetch_add(1));
    }

    ~supervisor_lite() override = default;

    template<class... Args>
    void broadcast_on_worker(std::string command, Args&&... args) {
        auto msg = actor_zeta::make_message(
            this->address(),
            "broadcast",
            actor_zeta::make_message_ptr(
                actor_zeta::address_t::empty_address(),
                command,
                std::forward<Args>(args)...));
        enqueue(std::move(msg));
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* final { return e_.get(); }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        auto msg_ = std::move(msg);
        auto it = system_.find(msg_->command());
        if (it != system_.end()) {
            local(std::move(msg_));
        } else {
            redirect_robin(std::move(msg_));
        }
    }

private:
    void broadcast_impl(actor_zeta::message* msg) {
        actor_zeta::message_ptr tmp(msg);
        auto address_tmp = address();
        tmp->sender() = address_tmp;
        for (auto& i : actors_) {
            i->enqueue(actor_zeta::message_ptr(tmp->clone()));
        }
    }
    auto local(actor_zeta::message_ptr msg) -> void {
        set_current_message(std::move(msg));
        behavior_.execute(this,current_message_);
    }

    auto redirect_robin(actor_zeta::message_ptr msg) -> void {
        if (!actors_.empty()) {
            actors_[cursor]->enqueue(std::move(msg));
            ++cursor;
            if (cursor >= actors_.size()) {
                cursor = 0;
            }
        }
    }

    std::unique_ptr<actor_zeta::scheduler_abstract_t, decltype(thread_pool_deleter)> e_;
    std::vector<actor_zeta::actor> actors_;
    std::size_t cursor;
    std::unordered_set<actor_zeta::detail::string_view> system_;
};

int main() {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<supervisor_lite>(mr_ptr);

    int const actors = 10;

    for (auto i = actors - 1; i > 0; --i) {
        actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), "create");
    }

    int const task = 10000;

    for (auto i = task - 1; i > 0; --i) {
        actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), "download", std::string("fb"), std::string("jack"), std::string("1"));
    }

    for (auto i = task - 1; i > 0; --i) {
        supervisor->broadcast_on_worker("work_data", std::string("fb"), std::string("jack"));
    }

    std::this_thread::sleep_for(std::chrono::seconds(180));

    std::cerr << " Finish " << std::endl;
    std::cerr << "counter_download_data :" << counter_download_data.load() << std::endl;
    std::cerr << "counter_work_data :" << counter_work_data.load() << std::endl;
    assert(counter_download_data.load() == 9999);
    assert(counter_work_data.load() == 9999);
    return 0;
}
