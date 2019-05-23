#pragma once

#ifdef 0

#include <cstddef>

namespace actor_zeta {

#if defined(DEBUG)
    #  include <cassert>
    #  define debug_only(expr) expr
    #  define debug_assert(expr) assert(expr)
#else
#  define debug_only(expr)
#  define debug_assert(expr)
#endif

    template<class Parent, class Member>
    std::ptrdiff_t offset_from_pointer_to_member(const Member Parent::* ptr_to_member){
        const Parent * const parent = 0;
        const char *const member = static_cast<const char*>(static_cast<const void*>(&(parent->*ptr_to_member)));
        return std::ptrdiff_t(member - static_cast<const char*>(static_cast<const void*>(parent)));

    }

    template<class Parent, class Member>
    Parent *parent_from_member(Member *member, const Member Parent::* ptr_to_member){
        return static_cast<Parent*>(
                static_cast<void*>(
                        static_cast<char*>(static_cast<void*>(member)) - offset_from_pointer_to_member(ptr_to_member)
                )
        );
    }

    template<class Parent, class Member>
    const Parent *parent_from_member(const Member *member, const Member Parent::* ptr_to_member){
        return static_cast<const Parent*>(
                static_cast<const void*>(
                        static_cast<const char*>(static_cast<const void*>(member)) - offset_from_pointer_to_member(ptr_to_member)
                )
        );
    }

    struct intrusive_list_node {
        intrusive_list_node * prev, * next;
    };


    template <class T, intrusive_list_node T::*LinkPonter>
    class intrusive_list final {
        using node_type = intrusive_list_node;
    public:
        using value_type = T ;
        using pointer = T * ;

        constexpr intrusive_list() noexcept : dummy_link({&dummy_link, &dummy_link}) {}

        pointer front() noexcept {
            debug_assert(not empty());
            return pointer_from_link(dummy_link.next);
        }

        pointer back() noexcept {
            debug_assert(not empty());
            return pointer_from_link(dummy_link.prev);
        }

        void push_front(pointer item) noexcept {
            auto link = &(item->*LinkPonter);
            link->next = dummy_link.next;
            link->next->prev = link;
            link->prev = &dummy_link;
            dummy_link.next = link;
        }

        void push_back(pointer item) noexcept {
            node_type * link = &(item->*LinkPonter);
            link->prev = dummy_link.prev;
            link->prev->next = link;
            link->next = &dummy_link;
            dummy_link.prev = link;
        }

        pointer pop_front() noexcept {
            debug_assert(not empty());
            node_type * link = dummy_link.next;
            unlink(link);
            return pointer_from_link(link);
        }

        pointer pop_back() noexcept {
            debug_assert(not empty());
            node_type * link = dummy_link.prev;
            debug_assert(link->next == &dummy_link);
            unlink(link);
            return pointer_from_link(link);
        }

        void remove(pointer item) noexcept {
            debug_assert(has(item));
            unlink(item);
        }

        bool is_head(pointer item) const noexcept {
            debug_assert(is_linked(item));
            debug_assert(has(item));
            return &(item->*LinkPonter) == dummy_link.next;
        }

        bool is_tail(pointer item) const noexcept {
            debug_assert(is_linked(item));
            debug_assert(has(item));
            return &item->link == dummy_link.prev;
        }

        void move_front(pointer item) noexcept {
            debug_assert(has(item));
            if (is_head(item)) {
                return;
            }
            node_type * link = &(item->*LinkPonter);
            auto prev = link->prev;
            // relink this with prev->prev
            prev->prev->next = link;
            link->prev = prev->prev;
            auto next = link->next;
            // relink prev with next
            next->prev = prev;
            prev->next = next;
            // relink this with prev
            prev->prev = link;
            link->next = prev;
        }

        static void unlink(pointer item) noexcept {
            debug_assert(is_linked(item));
            unlink(&(item->*LinkPonter));
        }

        static bool is_linked(pointer item) noexcept {
            auto link = &(item->*LinkPonter);
            return link->next != link && link->prev != link;
        }


        bool has(pointer item) const noexcept {
            debug_assert(item != nullptr);
            if (not is_linked(item)) {
                return false;
            }
            const node_type * node = &dummy_link;
            while (node->next != &dummy_link) {
                node = node->next;
                if (node == &(item->*LinkPonter)) {
                    return true;
                }
                // DBG_loopbreak(1000)
            }
            return false;
        }

        bool empty() const noexcept {
            return dummy_link.next == &dummy_link;
        }

    private:
        static void unlink(node_type * link) noexcept {
            debug_assert(link != nullptr);
            // Integrity check, unlink
            debug_assert(link->prev->next == link);
            link->prev->next = link->next;
            debug_assert(link->next->prev == link);
            link->next->prev = link->prev;
            debug_only(link->next = link->prev = link);
        }

        static pointer pointer_from_link(node_type * link) noexcept {
            // we don't want to mess with ABI by ourselves
            return parent_from_member<T, intrusive_list_node>(link, LinkPonter);
        }

    private:
        node_type dummy_link;
    };

}

#end