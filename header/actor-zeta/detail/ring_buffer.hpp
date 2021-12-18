#pragma once

#include <array>
#include <atomic>
#include <cassert>
#include <condition_variable>
#include <mutex>

namespace actor_zeta { namespace detail {

    // A ring_buffer designed for a single consumer and any number of producers that
    // can hold a maximum of `Size - 1` elements.
    template<class T, size_t Size>
    class ring_buffer {
    public:
        using guard_type = std::unique_lock<std::mutex>;

        ring_buffer()
            : wr_pos_(0)
            , rd_pos_(0) {
            // nop
        }

        void wait_nonempty() {
            // Double-checked locking to reduce contention on mtx_.
            if (!empty())
                return;
            guard_type guard{mtx_};
            while (empty())
                cv_empty_.wait(guard);
        }

        template<class TimePoint>
        bool wait_nonempty(TimePoint timeout) {
            if (!empty())
                return true;
            auto pred = [&] { return !empty(); };
            guard_type guard{mtx_};
            return cv_empty_.wait_until(guard, timeout, pred);
        }

        T& front() {
            // Safe to access without lock, because we assume a single consumer.
            return buf_[rd_pos_];
        }

        void pop_front() {
            guard_type guard{mtx_};
            auto rp = rd_pos_.load();
            rd_pos_ = next(rp);
            // Wakeup a waiting producers if the queue became non-full.
            if (rp == next(wr_pos_))
                cv_full_.notify_all();
        }

        template<class OutputIterator>
        OutputIterator get_all(OutputIterator i) {
            // No lock needed, again because of single-consumer assumption.
            auto first = rd_pos_.load();
            auto last = wr_pos_.load();
            size_t n;
            assert(first != last);
            // Move buffer content to the output iterator.
            if (first < last) {
                n = last - first;
                for (auto j = first; j != last; ++j)
                    *i++ = std::move(buf_[j]);
            } else {
                n = (Size - first) + last;
                for (size_t j = first; j != Size; ++j)
                    *i++ = std::move(buf_[j]);
                for (size_t j = 0; j != last; ++j)
                    *i++ = std::move(buf_[j]);
            }
            guard_type guard{mtx_};
            rd_pos_ = (first + n) % Size;
            // Wakeup a waiting producers if the queue became non-full.
            if (first == next(wr_pos_))
                cv_full_.notify_all();
            return i;
        }

        void push_back(T&& x) {
            guard_type guard{mtx_};
            while (full())
                cv_full_.wait(guard);
            auto wp = wr_pos_.load();
            buf_[wp] = std::move(x);
            wr_pos_ = next(wp);
            if (rd_pos_ == wp)
                cv_empty_.notify_all();
        }

        template<class... Us>
        void emplace_back(Us&&... xs) {
            push_back(T{std::forward<Us>(xs)...});
        }

        bool empty() const noexcept {
            return rd_pos_ == wr_pos_;
        }

        bool full() const noexcept {
            return rd_pos_ == next(wr_pos_);
        }

        size_t size() const noexcept {
            auto rp = rd_pos_.load();
            auto wp = wr_pos_.load();
            if (rp == wp)
                return 0;
            if (rp < wp)
                return wp - rp;
            return Size - rp + wp;
        }

    private:
        static size_t next(size_t pos) {
            return (pos + 1) % Size;
        }

        // Guards queue_.
        mutable std::mutex mtx_;

        // Signals the empty condition.
        std::condition_variable cv_empty_;

        // Signals the full condition.
        std::condition_variable cv_full_;

        // Stores the current write position in the ring_buffer.
        std::atomic<size_t> wr_pos_;

        // Stores the current read position in the ring_buffer.
        std::atomic<size_t> rd_pos_;

        // Stores events in a circular ring_buffer.
        std::array<T, Size> buf_;
    };

}} // namespace actor_zeta::detail