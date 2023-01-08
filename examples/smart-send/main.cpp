#include <cassert>

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <actor-zeta.hpp>
#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/base/cooperative_actor.hpp>

auto thread_pool_deleter = [](actor_zeta::scheduler_abstract_t* ptr) {
    ptr->stop();
    delete ptr;
};

static std::atomic<uint64_t> counter_download_data{0};
static std::atomic<uint64_t> counter_work_data{0};

class supervisor_lite;

class worker_t final : public actor_zeta::base::basic_actor<worker_t> {
public:
    enum class command_t : uint64_t {
        download = 0x00,
        work_data
    };

    worker_t(supervisor_lite* ptr)
        : actor_zeta::base::basic_actor<worker_t>(ptr, "bot") {
        add_handler(command_t::download, &worker_t::download);
        add_handler(command_t::work_data, &worker_t::work_data);
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
    std::string tmp_;
};

using actor_zeta::detail::pmr::memory_resource;
/// non thread safe
class supervisor_lite final : public actor_zeta::cooperative_supervisor<supervisor_lite> {
public:
    enum class system_command : std::uint64_t {
        broadcast = 0x00,
        create
    };

    explicit supervisor_lite(memory_resource* ptr)
        : cooperative_supervisor(ptr, "network")
        , e_(new actor_zeta::scheduler_t<actor_zeta::work_sharing>(
                 2,
                 1000),
             thread_pool_deleter) {
        e_->start();
        add_handler(system_command::create, &supervisor_lite::create);
        add_handler(system_command::broadcast, &supervisor_lite::broadcast_impl);
    }

    void create() {
        spawn_actor([this](worker_t* ptr) {
            actors_.emplace_back(ptr);
        });
    }

    ~supervisor_lite() override = default;

    template<class Id = uint64_t , class... Args>
    void broadcast_on_worker(Id id, Args&&... args) {
        auto msg = actor_zeta::make_message(
            address(),
            system_command::broadcast,
            actor_zeta::make_message_ptr(
                actor_zeta::address_t::empty_address(),
                id,
                std::forward<Args>(args)...));
        enqueue(std::move(msg));
    }

protected:
    auto scheduler_impl() noexcept -> actor_zeta::scheduler_abstract_t* final { return e_.get(); }

    auto enqueue_impl(actor_zeta::message_ptr msg, actor_zeta::execution_unit*) -> void final {
        set_current_message(std::move(msg));
        execute(this, current_message());
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

    std::unique_ptr<actor_zeta::scheduler_abstract_t, decltype(thread_pool_deleter)> e_;
    std::vector<actor_zeta::actor> actors_;
};

int main() {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
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
