#pragma once

#include <vector>
#include <type_traits>
#include <algorithm>
#include <new>
#include <tuple>
#include <memory>

#include <actor-zeta/detail/type_traits/type_traits.hpp>

namespace actor_zeta { namespace contaner {

    namespace impl {

        template<typename Key, typename Value>
        class split_flatmap_storage {
            using key_storage = std::vector<Key>;
            using value_storage = std::vector<Value>;
        public:
            using key_type = Key;
            using mapped_type = Value;
            using value_type = std::pair<Key, Value>;
            using reference = std::pair<const Key &, Value &> &;
            using pointer = std::pair<const Key &, Value &> *;
            using size_type = typename key_storage::size_type;

            split_flatmap_storage() = default;

            template<typename container>
            class iterator_type;

            using iterator = iterator_type<split_flatmap_storage>;
            using const_iterator = iterator_type<const split_flatmap_storage>;

            void clear() noexcept {
                m_keys.clear();
                m_values.clear();
            }

            bool empty() const noexcept { return m_values.empty(); }

            size_type size() const noexcept { return m_values.size(); }

            iterator begin() noexcept { return iterator{*this, 0}; }

            iterator end() noexcept { return iterator{*this, m_keys.size()}; }

            const_iterator begin() const noexcept { return const_iterator{*this, 0}; }

            const_iterator end() const noexcept { return const_iterator{*this, m_keys.size()}; }

            const_iterator cbegin() const noexcept { return begin(); }

            const_iterator cend() const noexcept { return end(); }

        protected:

            key_storage m_keys;
            value_storage m_values;
        };
    }

    template<typename Key, typename Value>
    class unordered_split_flatmap final : private impl::split_flatmap_storage<Key, Value> {
        static_assert(std::is_nothrow_move_constructible<Key>{},"The type Key is not move_constructible!");
        static_assert(std::is_nothrow_move_constructible<Value>{},"The type Value is not move_constructible!");
    public:
        using key_type = Key;
        using mapped_type = Value;
        using value_type =     typename impl::split_flatmap_storage<Key, Value>::value_type;
        using reference =     typename impl::split_flatmap_storage<Key, Value>::reference;
        using pointer =     typename impl::split_flatmap_storage<Key, Value>::pointer;
        using iterator =       typename impl::split_flatmap_storage<Key, Value>::iterator;
        using const_iterator = typename impl::split_flatmap_storage<Key, Value>::const_iterator;
        using size_type =      typename impl::split_flatmap_storage<Key, Value>::size_type;

        unordered_split_flatmap() = default;

        unordered_split_flatmap(std::initializer_list<value_type> list){
            for (auto &&x : list) {
                emplace(std::move(x));
            }
        };

        template<typename Iterator,
                typename EIterator,
                typename = type_traits::enable_if_t<type_traits::is_input_iterator<Iterator>{} &&
                                            type_traits::are_equal_comparable<Iterator, EIterator>{} &&
                                            std::is_constructible<value_type, typename std::iterator_traits<Iterator>::value_type>{}>>
        inline unordered_split_flatmap(Iterator b, EIterator e) {
            while (b != e) {
                emplace(*b);
                ++b;
            }
        }

        using impl::split_flatmap_storage<Key, Value>::clear;
        using impl::split_flatmap_storage<Key, Value>::empty;
        using impl::split_flatmap_storage<Key, Value>::size;
        using impl::split_flatmap_storage<Key, Value>::begin;
        using impl::split_flatmap_storage<Key, Value>::end;
        using impl::split_flatmap_storage<Key, Value>::cbegin;
        using impl::split_flatmap_storage<Key, Value>::cend;

        template<typename K, typename = type_traits::enable_if_t<type_traits::are_equal_comparable<Key, const K &>{}>>
        size_type count(const K &key) const noexcept { return find(key) == end() ? 0 : 1; }

        std::pair<iterator, bool> insert(const value_type &v){
            auto i = find(v.first);
            if ( i != end()) {
                return {i, false};
            }
            this->m_keys.push_back(v.first);
            this->m_values.push_back(v.second);
            return {{std::prev(this->m_keys.end()), std::prev(this->m_values.end())}, true};
        }

        std::pair<iterator, bool> insert(value_type &&v){
            auto i = find(v.first);
            if ( i != end()) {
                return {i, false};
            }

            this->m_keys.push_back(std::move(v.first));
            this->m_values.push_back(std::move(v.second));
            return {std::prev(end()), true};
        }

        template<typename K,
                typename V,
                typename = type_traits::enable_if_t<
                        type_traits::are_equal_comparable<Key, K>{} && std::is_constructible<Value, V>{} &&
                        std::is_assignable<Value, V>{}>>
        inline auto insert_or_assign(K &&k, V &&v) -> std::pair<iterator, bool> {
            auto i = find(k);
            if ( i != end()) {
                i->second = std::forward<V>(v);
                return {i, false};
            }
            return emplace(std::forward<K>(k), std::forward<V>(v));
        }

        template<typename ... T, typename = type_traits::enable_if_t<std::is_constructible<value_type, T...>{}>>
        inline auto emplace(T &&... t) -> std::pair<iterator, bool> {
            return insert(value_type(std::forward<T>(t)...));
        }

        template<typename K,
                typename ... V,
                typename = type_traits::enable_if_t<
                        type_traits::are_equal_comparable<Key, K>{} && std::is_constructible<Value, V...>{}>>
        inline auto try_emplace(K &&key, V &&... v)-> std::pair<iterator, bool> {
            auto i = find(key);
            if ( i != end()) {
                return {i, false};
            }
            return emplace(std::forward<K>(key), std::forward<V>(v)...);
        }

        inline auto erase(iterator i) -> void {
            if (i != std::prev(end())) {
                auto kp = std::addressof(i->first);
                auto vp = std::addressof(i->second);
                kp->~Key();
                vp->~Value();
                new(const_cast<Key *>(kp)) Key(std::move(this->m_keys.back()));
                new(vp) Value(std::move(this->m_values.back()));
            }
            this->m_keys.pop_back();
            this->m_values.pop_back();
        }

        template<typename K, typename = type_traits::enable_if_t<type_traits::are_equal_comparable<Key, const K &>{}>>
        inline auto erase(const K &key) -> size_type {
            auto i = find(key);
            if ( i != end()) {
                erase(i);
                return 1;
            }
            return 0;
        };

        template<typename T, typename = type_traits::enable_if_t<type_traits::are_equal_comparable<Key, T>{}>>
        inline auto operator[](const T &key)-> Value & {
            auto i = find(key);
            if (i != end()) {
                return i->second;
            }
            emplace(key, Value());
            return this->m_values.back();
        }

        template<typename T, typename = type_traits::enable_if_t<type_traits::are_equal_comparable<Key, T>{}>>
        inline auto find(const T &key)  noexcept -> iterator {
            auto ki = std::find_if(
                    std::begin(this->m_keys),
                    std::end(this->m_keys),
                    [&](key_type &x) { return x == key; }
            );
            auto d = static_cast<size_type>(std::distance(std::begin(this->m_keys), ki));
            return iterator{*this, d};
        }

        template<typename T, typename = type_traits::enable_if_t<type_traits::are_equal_comparable<Key, T>{}>>
        inline auto find(const T &key) const noexcept -> const_iterator {
            auto ki = std::find_if(std::begin(this->m_keys), std::end(this->m_keys),
                                   [&](key_type &x) { return x == key; });
            auto d = static_cast<size_type>(std::distance(std::begin(this->m_keys), ki));
            return const_iterator{*this, d};
        }
    };


    template<typename Key, typename Value>
    template<typename container>
    class impl::split_flatmap_storage<Key, Value>::iterator_type {
        template<typename C>
        friend
        class impl::split_flatmap_storage<Key, Value>::iterator_type;

        friend class impl::split_flatmap_storage<Key, Value>;

        using data = std::pair<const typename container::key_type &, typename container::mapped_type &>;
    public:
        class data_ptr {
        public:
            template<typename T, typename U>
            data_ptr(T &t, U &u) : m{t, u} {}

            data *operator->() { return &m; }

        private:
            data m;
        };

        using value_type = typename container::value_type;
        using iterator_category = std::bidirectional_iterator_tag;
        using reference = data;
        using pointer = data_ptr;
        using difference_type = typename key_storage::iterator::difference_type;

        iterator_type() noexcept = default;

        iterator_type(container &c_, typename container::size_type idx_) noexcept : c{&c_}, idx{idx_} {}

        iterator_type &operator++() noexcept {
            ++idx;
            return *this;
        }

        iterator_type operator++(int) noexcept {
            auto rv = *this;
            operator++();
            return rv;
        }

        iterator_type &operator--() noexcept {
            --idx;
            return *this;
        }

        iterator_type operator--(int) noexcept {
            auto rv = *this;
            operator--();
            return rv;
        }

        reference operator*() const noexcept { return {c->m_keys[idx], c->m_values[idx]}; }

        pointer operator->() const noexcept { return {c->m_keys[idx], c->m_values[idx]}; }

        template<typename C>
        bool operator==(const iterator_type<C> &ci) const noexcept {
            return c == ci.c && idx == ci.idx;
        }

        template<typename C>
        bool operator!=(const iterator_type<C> &ci) const noexcept {
            return !(*this == ci);
        }

    private:

        container *c;
        typename container::size_type idx;
    };


}}
