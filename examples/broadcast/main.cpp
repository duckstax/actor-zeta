#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <atomic>

#include <actor-zeta.hpp>

auto thread_pool_deleter = [](actor_zeta::scheduler_abstract_t* ptr) {
    ptr->stop();
    delete ptr;
};

static std::atomic<uint64_t> counter_download_data{0};
static std::atomic<uint64_t> counter_work_data{0};

class supervisor_lite;
class worker_t;
using actor_zeta::pmr::memory_resource;
/// non thread safe
class supervisor_lite final : public actor_zeta::cooperative_supervisor<supervisor_lite> {
public:
    enum class system_command : std::uint64_t {
        broadcast = 0x00,
        create
    };

    supervisor_lite(memory_resource* ptr)
        : cooperative_supervisor<supervisor_lite>(ptr)
        , create_(actor_zeta::make_behavior(resource(), system_command::create, this, &supervisor_lite::create))
        , broadcast_(actor_zeta::make_behavior(resource(), system_command::broadcast, this, &supervisor_lite::broadcast_impl))
        , e_(new actor_zeta::scheduler_t<actor_zeta::work_sharing>(2, 1000), thread_pool_deleter) {
        e_->start();
    }

    void create() {
        spawn_actor([this](worker_t* ptr) {
            actors_.emplace_back(ptr);
            ++size_actors_;
        });
    }

    const char* make_type() const noexcept {
        return "network";
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case actor_zeta::make_message_id(system_command::create): {
                        create_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(system_command::broadcast): {
                        broadcast_(msg);
                        break;
                    }
                }
            });
    }

    ~supervisor_lite() override = default;

    template<class Id = uint64_t, class... Args>
    void broadcast_on_worker(Id id, Args&&... args) {
        auto size = size_actor();
        std::vector<actor_zeta::message_ptr> tmp;
        tmp.reserve(size);
        for (std::size_t i = 0, e = size; i != e; ++i) {
            auto ptr = actor_zeta::make_message_ptr(
                address(),
                id,
                std::forward<const Args&>(args)...);
            tmp.push_back(std::move(ptr));
        }

        auto msg = actor_zeta::make_message(
            address(),
            system_command::broadcast,
            std::move(tmp));
        enqueue(std::move(msg));
    }

    auto make_scheduler() noexcept -> actor_zeta::scheduler_abstract_t* { return e_.get(); }

protected:
    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        set_current_message(std::move(msg));
        behavior()(current_message());
    }

private:
    int64_t size_actor() noexcept {
        return size_actors_.load();
    }

    void broadcast_impl(std::vector<actor_zeta::message_ptr>& msg) {
        auto msgs = std::move(msg);
        for (std::size_t i = 0, end = size_actor(); i != end; ++i) {
            actors_[i]->enqueue(std::move(msgs[i]));
        }
    }

    actor_zeta::behavior_t create_;
    actor_zeta::behavior_t broadcast_;
    std::unique_ptr<actor_zeta::scheduler_abstract_t, decltype(thread_pool_deleter)> e_;
    std::vector<actor_zeta::actor_t> actors_;
    std::atomic<int64_t> size_actors_{0};
};

class worker_t final : public actor_zeta::basic_actor<worker_t> {
public:
    enum class command_t : uint64_t {
        download = 0x00,
        work_data
    };

    worker_t(supervisor_lite* ptr)
        : actor_zeta::basic_actor<worker_t>(ptr)
        , download_(actor_zeta::make_behavior(resource(), command_t::download, this, &worker_t::download))
        , work_data_(actor_zeta::make_behavior(resource(), command_t::work_data, this, &worker_t::work_data)) {
    }

    actor_zeta::behavior_t behavior() {
        return actor_zeta::make_behavior(
            resource(),
            [this](actor_zeta::message* msg) -> void {
                switch (msg->command()) {
                    case actor_zeta::make_message_id(command_t::download): {
                        download_(msg);
                        break;
                    }
                    case actor_zeta::make_message_id(command_t::work_data): {
                        work_data_(msg);
                        break;
                    }
                }
            });
    }

    const char* make_type() const noexcept {
        return "worker_t";
    }

    void download(const std::string& url, const std::string& /*user*/, const std::string& /*password*/) {
        tmp_ = url;
        counter_download_data++;
    }

    void work_data(const std::string& data, const std::string& /*operatorName*/) {
        tmp_ = data;
        counter_work_data++;
    }

    ~worker_t() override = default;

private:
    actor_zeta::behavior_t download_;
    actor_zeta::behavior_t work_data_;
    std::string tmp_;
};

int main() {
    auto* mr_ptr = actor_zeta::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<supervisor_lite>(mr_ptr);

    int const actors = 10;

    for (auto i = actors - 1; i > 0; --i) {
        actor_zeta::send(supervisor.get(), actor_zeta::address_t::empty_address(), supervisor_lite::system_command::create);
    }

    int const task = 10000;

    for (auto i = task - 1; i > 0; --i) {
        supervisor->broadcast_on_worker(worker_t::command_t::download, std::string("fb"), std::string("jack"), std::string("1"));
    }

    for (auto i = task - 1; i > 0; --i) {
        supervisor->broadcast_on_worker(worker_t::command_t::work_data, std::string("fb"), std::string("jack"));
    }

    std::this_thread::sleep_for(std::chrono::seconds(180));

    std::cerr << " Finish " << std::endl;
    std::cerr << "counter_download_data :" << counter_download_data.load() << std::endl;
    std::cerr << "counter_work_data :" << counter_work_data.load() << std::endl;
    assert(counter_download_data.load() == 9999);
    assert(counter_work_data.load() == 9999);
    return 0;
}
