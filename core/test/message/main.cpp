
#include <cassert>
#include <actor-zeta/detail/intrusive_list.hpp>
#include <actor-zeta/messaging/message.hpp>

using BaseList =  actor_zeta::intrusive_forward_list<actor_zeta::messaging::message> ;

int main() {
    actor_zeta::messaging::message b1, b2, b3;

    BaseList mail_queue;
    BaseList local_queue;
    BaseList cache_;

    mail_queue.push_back(std::move(m));

    if (local_queue.empty()) {
        local_queue.splice(local_queue.begin(), mail_queue);
    }

    if (!local_queue.empty()) {
        tmp = std::move(local_queue.front());
        local_queue.pop_front();
    }

    cache_.push_back(std::move(msg_ptr));

    if (!cache_.empty()) {
        msg_ptr = std::move(cache_.front());
        cache_.pop_front();
    }

    return 0 ;
}