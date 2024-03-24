#pragma once

#include <actor-zeta/mailbox/message.hpp>
#include <actor-zeta/detail/queue/enqueue_result.hpp>

namespace actor_zeta {

    template<class T>
    class mailbox_t final : protected T {
    public:
        template<class ...Args>
        mailbox_t(Args&&... args)
            : T(std::forward<Args>(args)...) {
        }
        ~mailbox_t() = default;
        detail::enqueue_result push_back(mailbox::message_ptr ptr) {
            return self()->push_back_impl(std::move(ptr));
        }
        void push_front(mailbox::message* ptr) {
            return self()->push_front_impl(ptr);
        }
        mailbox::message_ptr pop_front() {
            return self()->pop_front_impl();
        }
        bool closed() const noexcept {
            return self()->closed_impl();
        }
        bool blocked() const noexcept {
            return self()->blocked_impl();
        }
        bool try_block() {
            return self()->try_block_impl();
        }
        bool try_unblock() {
            return self()->try_unblock_impl();
        }
        size_t close() {
            return self()->close_impl();
        }
        size_t size() {
            return self()->size_impl();
        }
        bool empty() {
            return size() == 0;
        }

    private:
        auto self() noexcept -> T* {
            return static_cast<T*>(this);
        }

        auto self() const noexcept -> T* {
            return static_cast<T*>(this);
        }
    };

} // namespace actor_zeta