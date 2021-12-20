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

static std::atomic<uint64_t> alarm_counter{0};


class supervisor_lite;


using actor_zeta::detail::pmr::memory_resource;
/// non thread safe
class supervisor_lite final : public actor_zeta::cooperative_supervisor<supervisor_lite> {
public:
    explicit supervisor_lite(memory_resource* ptr)
        : cooperative_supervisor(ptr, "network", 0)
        , e_(new actor_zeta::scheduler_t<actor_zeta::work_sharing>(
                 1,
                 100),
             thread_pool_deleter){
        e_->start();
        add_handler("broadcast", &supervisor_lite::broadcast_impl);
        add_handler("alarm", &supervisor_lite::alarm);
    }

    ~supervisor_lite() override = default;

    void alarm() {
        alarm_counter += 1;
    }

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
        {
            local(std::move(msg));
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
        execute();
    }

    std::unique_ptr<actor_zeta::scheduler_abstract_t, decltype(thread_pool_deleter)> e_;
    std::vector<actor_zeta::actor> actors_;
};

int main() {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor = actor_zeta::spawn_supervisor<supervisor_lite>(mr_ptr);

    int const actors = 10;

    supervisor->clock().schedule_message(actor_zeta::clock::clock_t::time_point(std::chrono::seconds(6)),supervisor->address(),actor_zeta::make_message(actor_zeta::address_t::empty_address(),"alarm"));

    std::this_thread::sleep_for(std::chrono::seconds(60));

    std::cerr << " Finish " << std::endl;
    std::cerr << " Finish Alarm Counter :" << alarm_counter << std::endl;
    assert(alarm_counter.load() == 1);
    return 0;
}
