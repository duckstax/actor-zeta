#pragma once

#include <atomic>
#include <condition_variable> // std::cv_status
#include <deque>
#include <limits>
#include <list>
#include <memory>
#include <mutex>

#include "intrusive_partitioned_list.hpp"

namespace actor_zeta { namespace detail {

    enum class enqueue_result {
        success,
        unblocked_reader,
        queue_closed
    };

    /// An intrusive, thread-safe queue implementation.
    template<class T, class Delete = std::default_delete<T>>
    class single_reader_queue {
    public:
        using value_type = T;
        using pointer = value_type*;
        using deleter_type = Delete;
        using unique_pointer = std::unique_ptr<value_type, deleter_type>;
        using cache_type = intrusive_partitioned_list<value_type, deleter_type>;

        pointer try_pop() {
            return take_head();
        }


        enqueue_result enqueue(pointer new_element) {
            assert(new_element != nullptr);
            pointer e = stack_.load();
            for (;;) {
                if (!e) {
                    // if tail is nullptr, the queue has been closed
                    delete_(new_element);
                    return enqueue_result::queue_closed;
                }
                // a dummy is never part of a non-empty list
                new_element->next = is_dummy(e) ? nullptr : e;
                if (stack_.compare_exchange_strong(e, new_element)) {
                    return (e == reader_blocked_dummy()) ? enqueue_result::unblocked_reader
                                                         : enqueue_result::success;
                }
                // continue with new value of e
            }
        }

        bool can_fetch_more() {
            if (head_ != nullptr)
                return true;
            auto ptr = stack_.load();
            assert(ptr != nullptr);
            return !is_dummy(ptr);
        }

        bool empty() {
            assert(!closed());
            return cache_.empty() && !head_ && is_dummy(stack_.load());
        }

        bool closed() {
            return !stack_.load();
        }

        bool blocked() {
            return stack_.load() == reader_blocked_dummy();
        }

        bool try_block() {
            auto e = stack_empty_dummy();
            return stack_.compare_exchange_strong(e, reader_blocked_dummy());
            //return res || e == reader_blocked_dummy();
        }

        bool try_unblock() {
            auto e = reader_blocked_dummy();
            return stack_.compare_exchange_strong(e, stack_empty_dummy());
        }

        void close() {
            auto nop = [](const T&) {};
            close(nop);
        }

        template<class F>
        void close(const F& f) {
            clear_cached_elements(f);
            if (!blocked() && fetch_new_data(nullptr))
                clear_cached_elements(f);
            cache_.clear(f);
        }

        single_reader_queue()
            : head_(nullptr) {
            stack_ = stack_empty_dummy();
        }

        ~single_reader_queue() {
            if (!closed())
                close();
        }

        size_t count(size_t max_count = std::numeric_limits<size_t>::max()) {
            size_t res = cache_.count(max_count);
            if (res >= max_count)
                return res;
            fetch_new_data();
            auto ptr = head_;
            while (ptr && res < max_count) {
                ptr = ptr->next;
                ++res;
            }
            return res;
        }

        pointer peek() {
            if (head_ != nullptr || fetch_new_data())
                return head_;
            return nullptr;
        }

        template<class F>
        void peek_all(F fun) {
            auto ranges = cache_.ranges();
            for (auto& range : ranges)
                for (auto i = range.first; i != range.second; ++i)
                    fun(*i);
            // Fetch new data if needed
            if (head_ == nullptr) {
                fetch_new_data();
            } else if (!is_dummy(stack_.load())) {
                auto old_head = head_;
                head_ = nullptr;
                auto tail = old_head;
                while (tail->next != nullptr)
                    tail = tail->next;
                fetch_new_data();
                tail->next = head_;
                head_ = old_head;
            }
            auto ptr = head_;
            while (ptr) {
                fun(*ptr);
                ptr = ptr->next;
            }
        }

        cache_type& cache() {
            return cache_;
        }


        template<class Mutex, class CondVar>
        bool synchronized_enqueue(Mutex& mtx, CondVar& cv, pointer new_element) {
            switch (enqueue(new_element)) {
                case enqueue_result::unblocked_reader: {
                    std::unique_lock<Mutex> guard(mtx);
                    cv.notify_one();
                    return true;
                }
                case enqueue_result::success:
                    // enqueued message to a running actor's mailbox
                    return true;
                case enqueue_result::queue_closed:
                    // actor no longer alive
                    return false;
            }
            assert(false);
        }

        template<class Mutex, class CondVar>
        void synchronized_await(Mutex& mtx, CondVar& cv) {
            assert(!closed());
            if (!can_fetch_more() && try_block()) {
                std::unique_lock<Mutex> guard(mtx);
                while (blocked())
                    cv.wait(guard);
            }
        }

        template<class Mutex, class CondVar, class TimePoint>
        bool synchronized_await(Mutex& mtx, CondVar& cv, const TimePoint& timeout) {
            assert(!closed());
            if (!can_fetch_more() && try_block()) {
                std::unique_lock<Mutex> guard(mtx);
                while (blocked()) {
                    if (cv.wait_until(guard, timeout) == std::cv_status::timeout) {
                        return !try_unblock();
                    }
                }
            }
            return true;
        }

    private:
        std::atomic<pointer> stack_;

        pointer head_;
        deleter_type delete_;
        cache_type cache_;

        bool fetch_new_data(pointer end_ptr) {
            assert(!end_ptr || end_ptr == stack_empty_dummy());
            pointer e = stack_.load();
            assert(e != nullptr);
            assert(e != reader_blocked_dummy());
            while (e != end_ptr) {
                if (stack_.compare_exchange_weak(e, end_ptr)) {
                    assert(e != reader_blocked_dummy());
                    if (is_dummy(e)) {
                        assert(!end_ptr);
                        return false;
                    }
                    while (e) {
                        assert(!is_dummy(e));
                        auto next = e->next;
                        e->next = head_;
                        head_ = e;
                        e = next;
                    }
                    return true;
                }
            }
            return false;
        }

        bool fetch_new_data() {
            return fetch_new_data(stack_empty_dummy());
        }

        pointer take_head() {
            if (head_ != nullptr || fetch_new_data()) {
                auto result = head_;
                head_ = head_->next;
                return result;
            }
            return nullptr;
        }

        template<class F>
        void clear_cached_elements(const F& f) {
            while (head_) {
                auto next = head_->next;
                f(*head_);
                delete_(head_);
                head_ = next;
            }
        }

        pointer stack_empty_dummy() {
            return reinterpret_cast<pointer>(this);
        }

        pointer reader_blocked_dummy() {
            return reinterpret_cast<pointer>(reinterpret_cast<intptr_t>(this) + static_cast<intptr_t>(sizeof(void*)));
        }

        bool is_dummy(pointer ptr) {
            return ptr == stack_empty_dummy() || ptr == reader_blocked_dummy();
        }
    };

}} // namespace actor_zeta::detail