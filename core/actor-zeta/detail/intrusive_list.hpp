#pragma once

#include <cstddef>

namespace actor_zeta {

    struct intrusive_list_node {
        intrusive_list_node *next_;
        intrusive_list_node *prev_;

        intrusive_list_node() = default;

        ~intrusive_list_node() = default;
    };

    class intrusive_list_base {
    protected:
        intrusive_list_node anchor_;

    public:
        inline intrusive_list_base() {
            anchor_.next_ = anchor_.prev_ = &anchor_;
        }

        inline ~intrusive_list_base() {
            clear();
            anchor_.next_ = anchor_.prev_ = nullptr;
        }

        inline bool empty() const noexcept {
            return anchor_.prev_ == &anchor_;
        }

        inline void clear() noexcept {
#if 0
            //O(1) -> O(n)

        intrusive_list_node* pNode = anchor_.next_;

        while(pNode != &anchor_){
            intrusive_list_node* const pNextNode = pNode->next_;
            pNode->next_ = pNode->prev_ = nullptr;
            pNode = pNextNode;
        }
#endif

            anchor_.next_ = anchor_.prev_ = &anchor_;
        }

        inline void pop_front() {

            intrusive_list_node *const pNode = anchor_.next_;

            anchor_.next_->next_->prev_ = &anchor_;
            anchor_.next_ = anchor_.next_->next_;


            if (pNode != &anchor_) {
                pNode->next_ = pNode->prev_ = nullptr;
            } else {
                static_assert(true, "empty list");
            }


        }

        inline void pop_back() {
            intrusive_list_node *const pNode = anchor_.prev_;
            anchor_.prev_->prev_->next_ = &anchor_;
            anchor_.prev_ = anchor_.prev_->prev_;


            if (pNode != &anchor_) {
                pNode->next_ = pNode->prev_ = nullptr;
            } else {
                static_assert(true, "empty list");
            }

        }

    };

/// Differences between std::list and intrusive_list:
/// Issue                            std::list       intrusive_list
/// --------------------------------------------------------------
/// Automatic node ctor/dtor         Yes             No
/// Can memmove() container          Maybe*          No
/// Same item in list twice          Yes(copy/byref) No
/// Can store non-copyable items     No              Yes
/// clear()                          O(n)            O(1)
/// erase(range)                     O(n)            O(1)
/// Convert reference to iterator    No              O(1)
/// Remove without container         No              O(1)
/// Nodes in mixed allocators        No              Yes

    template<typename T = intrusive_list_node>
    class intrusive_list final : public intrusive_list_base {
    public:
        typedef intrusive_list<T> this_type;
        typedef T node_type;
        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;

    public:
        intrusive_list() = default;

        intrusive_list(const this_type &) : intrusive_list_base() {}

        this_type &operator=(const this_type &) {
            return *this;
        }

        void swap(this_type &x) {

            intrusive_list_node temp(anchor_);
            anchor_ = x.anchor_;
            x.anchor_ = temp;

            if (anchor_.next_ == &x.anchor_)
                anchor_.next_ = anchor_.prev_ = &anchor_;
            else
                anchor_.next_->prev_ = anchor_.prev_->next_ = &anchor_;

            if (x.anchor_.next_ == &anchor_) {
                x.anchor_.next_ = x.anchor_.prev_ = &x.anchor_;
            } else {
                x.anchor_.next_->prev_ = x.anchor_.prev_->next_ = &x.anchor_;
            }

            temp.prev_ = temp.next_ = nullptr;

        }

        reference front() {
            assert(anchor_.next_ == &anchor_);//"intrusive_list::front(): empty list.";
            return *static_cast<T *>(anchor_.next_);
        }

        const_reference front() const {

            assert(anchor_.next_ == &anchor_);//"intrusive_list::front(): empty list.";
            return *static_cast<const T *>(anchor_.next_);
        }

        reference back() {
            assert(anchor_.next_ == &anchor_);//"intrusive_list::back(): empty list."
            return *static_cast<T *>(anchor_.prev_);
        }

        const_reference back() const {
            assert(anchor_.next_ == &anchor_);//"intrusive_list::back(): empty list."
            return *static_cast<const T *>(anchor_.prev_);
        }

        void push_front(value_type &x) {
            assert(x.next_ || x.prev_);//"intrusive_list::push_front(): element already on a list."
            x.next_ = anchor_.next_;
            x.prev_ = &anchor_;
            anchor_.next_ = &x;
            x.next_->prev_ = &x;
        }

        void push_back(value_type &x) {
            assert(x.next_ || x.prev_);//"intrusive_list::push_back(): element already on a list."
            x.prev_ = anchor_.prev_;
            x.next_ = &anchor_;
            anchor_.prev_ = &x;
            x.prev_->next_ = &x;
        }

        static void remove(value_type &value) {
            intrusive_list_node &prev = *value.prev_;
            intrusive_list_node &next = *value.next_;
            prev.next_ = &next;
            next.prev_ = &prev;
            value.prev_ = value.next_ = nullptr;
        }

    };

    template<typename T>
    bool operator==(const intrusive_list<T> &a, const intrusive_list<T> &b) {
        typename intrusive_list<T>::const_iterator ia = a.begin();
        typename intrusive_list<T>::const_iterator ib = b.begin();
        typename intrusive_list<T>::const_iterator enda = a.end();
        typename intrusive_list<T>::const_iterator endb = b.end();

        while ((ia != enda) && (ib != endb) && (*ia == *ib)) {
            ++ia;
            ++ib;
        }
        return (ia == enda) && (ib == endb);
    }

    template<typename T>
    bool operator!=(const intrusive_list<T> &a, const intrusive_list<T> &b) {
        return !(a == b);
    }

    template<typename T>
    bool operator<(const intrusive_list<T> &a, const intrusive_list<T> &b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    template<typename T>
    bool operator>(const intrusive_list<T> &a, const intrusive_list<T> &b) {
        return b < a;
    }

    template<typename T>
    bool operator<=(const intrusive_list<T> &a, const intrusive_list<T> &b) {
        return !(b < a);
    }

    template<typename T>
    bool operator>=(const intrusive_list<T> &a, const intrusive_list<T> &b) {
        return !(a < b);
    }

    template<typename T>
    void swap(intrusive_list<T> &a, intrusive_list<T> &b) {
        a.swap(b);
    }

}
