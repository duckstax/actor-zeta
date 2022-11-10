#pragma once

#include <memory>

#include <actor-zeta/detail/memory_resource.hpp>
#include <actor-zeta/detail/queue/enqueue_result.hpp>

namespace test {

    template<typename Policy_t, typename Queue_t, typename Inode_t>
    struct fixture {
        actor_zeta::detail::pmr::memory_resource* mr_;
        Policy_t policy;
        Queue_t queue_;

        auto queue() -> Queue_t& {
            return queue_;
        }

        template<class... Args>
        auto duplicate(Args&&... args) -> Queue_t {
            return Queue_t(mr_, std::forward<Args&&>(args)...);
        }

        using mapped_type = typename Policy_t::mapped_type;
        using deleter_type = typename Policy_t::deleter_type;
        using unique_pointer = typename Policy_t::unique_pointer;

        template<class T>
        mapped_type* allocate(T&& x) {
            auto ptr = actor_zeta::detail::pmr::allocate_ptr<mapped_type>(mr_, std::forward<T&&>(x));
            assert(ptr);
            return ptr;
        }

        template<class... Args>
        fixture(actor_zeta::detail::pmr::memory_resource* mr, Args&&... args)
            : mr_(mr ? mr : actor_zeta::detail::pmr::get_default_resource())
            , queue_(mr_, std::forward<Args&&>(args)...) {}

        void fill() {}

        template<class T, class... Args>
        void fill(T&& x, Args&&... xs) {
            queue_.push_back(
                allocate(std::forward<T&&>(x))
            );
            fill(std::forward<Args&&>(xs)...);
        }

//        template<class T>
//        void push_back_single(T&& x) {
//            queue_.push_back(
//                allocate(std::forward<T&&>(x));
//            );
//        }

        void fill_front() {}

        template<class T, class... Args>
        void fill_front(T&& x, Args&&... xs) {
            queue_.push_front(
                allocate(std::forward<T&&>(x))
            );
            fill_front(std::forward<Args&&>(xs)...);
        }

        void lifo_append() {}

        template<class T, class... Args>
        void lifo_append(T&& x, Args&&... xs) {
            queue_.lifo_append(
                allocate(std::forward<T&&>(x))
            );
            lifo_append(std::forward<Args&&>(xs)...);
        }

        void fill_unique() {}

        template<class T, class... Args>
        void fill_unique(T&& x, Args&&... xs) {
            auto ptr = allocate(std::forward<T&&>(x));
            assert(ptr);
            queue_.push_back(
                unique_pointer{ptr, deleter_type(mr_)}
            );
            fill_unique(std::forward<Args&&>(xs)...);
        }

        void fill_queue(Queue_t&) {}

        template<class T, class... Ts>
        void fill_queue(Queue_t& q, T&& x, Ts&&... xs) {
            q.push_back(
                allocate(std::forward<T&&>(x))
            );
            fill_queue(q, std::forward<Ts&&>(xs)...);
        }
    };

#if 0
    template<typename Policy_t, typename Queue_t, typename Inode_t, typename _Alloc = std::allocator<Inode_t> >
    struct fixture_front : public _Alloc {
        Policy_t policy;
        Queue_t queue_;

        auto queue() -> Queue_t& {
            return queue_;
        }

        template<class... Args>
        auto duplicate(Args&&... args) -> Queue_t {
            return Queue_t(this, std::forward<Args&&>(args)...);
        }

        using deleter_type = typename Policy_t::deleter_type;
        using unique_pointer = typename Policy_t::unique_pointer;

        template<class... Args>
        fixture_front(Args&&... args)
            : queue_(this, std::forward<Args&&>(args)...) {}

        void fill_front() {}

        template<class T, class... Args>
        void fill_front(T&& x, Args&&... xs) {
            auto ptr = std::allocator_traits<_Alloc>::allocate(*this, sizeof(T));
            assert(ptr);
            std::allocator_traits<_Alloc>::construct(*this, ptr, std::forward<T&&>(x));
            queue_.push_front(
                ptr
            );
            fill_front(std::forward<Args&&>(xs)...);
        }

        template<class T>
        actor_zeta::detail::enqueue_result fill_single(T&& x) {
            auto ptr = std::allocator_traits<_Alloc>::allocate(*this, sizeof(T));
            assert(ptr);
            std::allocator_traits<_Alloc>::construct(*this, ptr, std::forward<T&&>(x));
            return queue_.push_front(
                ptr
            );
        }

        void lifo_append() {}

        template<class T, class... Args>
        void lifo_append(T&& x, Args&&... xs) {
            auto ptr = std::allocator_traits<_Alloc>::allocate(*this, sizeof(T));
            assert(ptr);
            std::allocator_traits<_Alloc>::construct(*this, ptr, std::forward<T&&>(x));
            queue_.lifo_append(
                ptr
            );
            lifo_append(std::forward<Args&&>(xs)...);
        }

        void fill_unique() {}

        template<class T, class... Args>
        void fill_unique(T&& x, Args&&... xs) {
            auto ptr = std::allocator_traits<_Alloc>::allocate(*this, sizeof(T));
            assert(ptr);
            std::allocator_traits<_Alloc>::construct(*this, ptr, std::forward<T&&>(x));
            queue_.push_back(
                unique_pointer{ptr, deleter_type(this)}
            );
            fill_unique(std::forward<Args&&>(xs)...);
        }

        void fill_queue(Queue_t&) {}

        template<class T, class... Ts>
        void fill_queue(Queue_t& q, T&& x, Ts&&... xs) {
            auto ptr = std::allocator_traits<_Alloc>::allocate(*this, sizeof(T));
            assert(ptr);
            std::allocator_traits<_Alloc>::construct(*this, ptr, std::forward<T&&>(x));
            q.push_back(
                ptr
            );
//            auto* value = actor_zeta::detail::pmr::allocate_ptr<queue_type::value_type>(memory_resource_, std::forward<T&&>(x));
//            assert(value);
//            q.push_back(value);
            fill_queue(q, std::forward<Ts&&>(xs)...);
        }

        auto to_string(const typename Queue_t::value_type& x) -> std::string {
            return std::to_string(x.value);
        }

        auto close_and_fetch() -> std::string {
            std::string result;
            auto f = [&](typename Queue_t::pointer x) {
                result += to_string(*x);
                delete x;
            };
            queue_.close(f);
            return result;
        }
    };

    // non-alloc
    template<typename Policy_t, typename Queue_t, typename Inode_t>
    struct fixture_non_alloc {
        Policy_t policy;
        Queue_t queue_;

        auto queue() -> Queue_t& {
            return queue_;
        }

        template<class... Args>
        auto duplicate(Args&&... args) -> Queue_t {
            return Queue_t(std::forward<Args&&>(args)...);
        }

        using deleter_type = typename Policy_t::deleter_type;
        using unique_pointer = typename Policy_t::unique_pointer;

        template<class... Args>
        fixture_non_alloc(Args&&... args)
            : queue_(std::forward<Args&&>(args)...) {}

        void fill() {}

        template<class T, class... Args>
        void fill(T&& x, Args&&... xs) {
            queue_.push_back(
                new Inode_t(std::forward<T&&>(x))
            );
            fill(std::forward<Args&&>(xs)...);
        }

        void lifo_append() {}

        template<class T, class... Args>
        void lifo_append(T&& x, Args&&... xs) {
            queue_.lifo_append(
                new Inode_t(std::forward<T&&>(x))
            );
            lifo_append(std::forward<Args&&>(xs)...);
        }

        void fill_queue(Queue_t&) {}

        template<class T, class... Ts>
        void fill_queue(Queue_t& q, T&& x, Ts&&... xs) {
            q.push_back(
                new Inode_t(std::forward<T&&>(x))
            );
            fill_queue(q, std::forward<Ts&&>(xs)...);
        }
    };
#endif

}
