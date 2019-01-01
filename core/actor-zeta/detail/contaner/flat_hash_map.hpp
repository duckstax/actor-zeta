#pragma once

#include <functional>
#include <type_traits>

#include <actor-zeta/detail/contaner/flat_hash_table.hpp>

namespace actor_zeta { namespace  detail {

    template<
            typename Key,
            typename Mapped,
            typename Hash = std::hash<Key>,
            typename Equals = std::equal_to<Key>,
            typename Allocator = std::allocator<Key>
    >
    class hash_map final {
    public:
        using key_type = Key;
        using mapped_type = Mapped;
        using value_type = std::pair<key_type const, mapped_type>;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using hasher = Hash;
        using key_equal = Equals;
        using allocator_type = Allocator;
        using reference = value_type &;
        using const_reference = value_type const &;
        using pointer = value_type *;
        using const_pointer = value_type const *;

    private:
        using TableValue = std::pair<key_type, mapped_type>;

        struct GetKey final {
            key_type const &operator()(TableValue const &value) const {
                return value.first;
            }
        };

        using Table = hash_table<
                TableValue,
                key_type,
                GetKey,
                Hash,
                Equals,
                typename Allocator::template rebind<TableValue>::other
        >;

    public:
        struct const_iterator final {
            using iterator_category = std::forward_iterator_tag;
            using value_type = typename hash_map::value_type const;
            using difference_type = ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

            bool operator==(const_iterator const &rhs) const {
                return inner == rhs.inner;
            }

            bool operator!=(const_iterator const &rhs) const {
                return inner != rhs.inner;
            }

            const_iterator &operator++() {
                ++inner;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator copy(*this);
                ++*this;
                return copy;
            }

            value_type &operator*() const {
                return *operator->();
            }

            value_type *operator->() const {
                return (value_type *) (&*inner);
            }

            typename Table::const_iterator inner;
        };

        struct iterator final {
            using iterator_category = std::forward_iterator_tag;
            using value_type = typename hash_map::value_type;
            using difference_type = ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

            bool operator==(iterator const &rhs) const {
                return inner == rhs.inner;
            }

            bool operator!=(iterator const &rhs) const {
                return inner != rhs.inner;
            }

            iterator &operator++() {
                ++inner;
                return *this;
            }

            iterator operator++(int) {
                iterator copy(*this);
                operator++();
                return copy;
            }

            value_type &operator*() const {
                return *operator->();
            }

            value_type *operator->() const {
                return (value_type *) (&*inner);
            }

            operator const_iterator() const {
                return const_iterator{inner};
            }

            typename Table::iterator inner;
        };

        hash_map() : hash_map(0) {}

        explicit hash_map(
                size_t bucketCount,
                hasher const &hash = hasher(),
                key_equal const &equal = key_equal(),
                allocator_type const &alloc = allocator_type()
        ) : m_table(bucketCount, GetKey(), hash, equal, alloc) {}

        hash_map(
                size_t bucketCount,
                allocator_type const &alloc
        ) : hash_map(
                bucketCount,
                hasher(),
                key_equal(),
                alloc) {

        }

        hash_map(
                size_t bucketCount,
                hasher const &hash,
                allocator_type const &alloc
        ) : hash_map(
                bucketCount,
                hash,
                key_equal(),
                alloc
        ) {}

        explicit hash_map(allocator_type const &alloc) : hash_map(0, hasher(), key_equal(), alloc) {}

        template<typename InputIt>
        hash_map(
                InputIt first,
                InputIt last,
                size_t bucketCount = 0,
                hasher const &hash = hasher(),
                key_equal const &equal = key_equal(),
                allocator_type const &alloc = allocator_type()
        )  : hash_map(bucketCount, hash, equal, alloc) {
            insert(first, last);
        }

        template<typename InputIt>
        hash_map(
                InputIt first,
                InputIt last,
                size_t bucketCount,
                allocator_type const &alloc
        )   : hash_map(
                first,
                last,
                bucketCount,
                hasher(),
                key_equal(),
                alloc
        ) {

        }

        template<typename InputIt>
        hash_map(
                InputIt first,
                InputIt last,
                size_t bucketCount,
                hasher const &hash,
                allocator_type const &alloc
        )  : hash_map(
                first,
                last,
                bucketCount,
                hash,
                key_equal(),
                alloc
        ) {

        }

        hash_map(hash_map const &other) : hash_map(other, other.m_table.getAllocator()) {}

        hash_map(hash_map const &other, allocator_type const &alloc) : hash_map(alloc) {
            operator=(other);
        }

        hash_map(hash_map &&other) : hash_map(move(other), other.m_table.getAllocator()) {}

        hash_map(hash_map &&other, allocator_type const &alloc) : hash_map(alloc) {
            operator=(move(other));
        }

        hash_map(
                std::initializer_list<value_type> init,
                size_t bucketCount = 0,
                hasher const &hash = hasher(),
                key_equal const &equal = key_equal(),
                allocator_type const &alloc = allocator_type()
        ) : hash_map(bucketCount, hash, equal, alloc) {
            operator=(init);
        }

        hash_map(
                std::initializer_list<value_type> init,
                size_t bucketCount,
                allocator_type const &alloc
        ) : hash_map(
                init,
                bucketCount,
                hasher(),
                key_equal(),
                alloc
        ) {}


        hash_map(
                std::initializer_list<value_type> init,
                size_t bucketCount,
                hasher const &hash,
                allocator_type const &alloc
        ) : hash_map(
                init,
                bucketCount,
                hash,
                key_equal(),
                alloc
        ) {}

        hash_map &operator=(hash_map const &other) {
            m_table.clear();
            m_table.reserve(other.size());
            for (auto const &p : other) {
                m_table.insert(p);
            }
            return *this;
        }

        hash_map &operator=(hash_map &&other) {
            m_table = move(other.m_table);
            return *this;
        }

        hash_map &operator=(std::initializer_list<value_type> init) {
            clear();
            insert(init.begin(), init.end());
            return *this;
        }

        iterator begin() {
            return iterator{m_table.begin()};
        }

        iterator end() {
            return iterator{m_table.end()};
        }

        const_iterator begin() const {
            return const_iterator{m_table.begin()};
        }

        const_iterator end() const {
            return const_iterator{m_table.end()};
        }

        const_iterator cbegin() const {
            return begin();
        }

        const_iterator cend() const {
            return end();
        }

        size_t empty() const {
            return m_table.empty();
        }

        size_t size() const {
            return m_table.size();
        }

        void clear() {
            m_table.clear();
        }

        std::pair<iterator, bool> insert(value_type const &value) {
            auto res = m_table.insert(TableValue(value));
            return {iterator{res.first}, res.second};
        }

        template<typename T, typename = typename std::enable_if<std::is_constructible<TableValue, T &&>::value>::type>
        std::pair<iterator, bool> insert(T &&value) {
            auto res = m_table.insert(TableValue(std::forward<T &&>(value)));
            return {iterator{res.first}, res.second};
        }

        iterator insert(const_iterator hint, value_type const &value) {
            return insert(hint, TableValue(value));
        }

        template<typename T, typename = typename std::enable_if<std::is_constructible<TableValue, T &&>::value>::type>
        iterator insert(const_iterator hint, T &&value) {
            return insert(std::forward<T &&>(value)).first;
        }

        template<typename InputIt>
        void insert(InputIt first, InputIt last) {
            m_table.reserve(m_table.size() + std::distance(first, last));
            for (auto i = first; i != last; ++i) {
                insert(*i);
            }
        }

        void insert(std::initializer_list<value_type> init) {
            insert(init.begin(), init.end());
        }

        template<typename... Args>
        std::pair<iterator, bool> emplace(Args &&... args) {
            return insert(TableValue(std::forward<Args>(args)...));
        }

        template<typename... Args>
        iterator emplace_hint(const_iterator hint, Args &&... args) {
            return insert(hint, TableValue(std::forward<Args>(args)...));
        }

        iterator erase(const_iterator pos) {
            return iterator{m_table.erase(pos.inner)};
        }

        iterator erase(const_iterator first, const_iterator last) {
            return iterator{m_table.erase(first.inner, last.inner)};
        }

        size_t erase(key_type const &key) {
            auto i = find(key);
            if (i != end()) {
                erase(i);
                return 1;
            }
            return 0;
        }

        mapped_type &at(key_type const &key) {
            auto i = find(key);
            if (i == end())
                ///throw std::out_of_range("no such key in hash_map");
            return i->second;
        }

        mapped_type const &at(key_type const &key) const {
            auto i = find(key);
            if (i == end())
                ///throw std::out_of_range("no such key in hash_map");
            return i->second;
        }

        mapped_type &operator[](key_type const &key) {
            auto i = find(key);
            if (i != end())
                return i->second;
            return insert({key, mapped_type()}).first->second;
        }

        mapped_type &operator[](key_type &&key) {
            auto i = find(key);
            if (i != end())
                return i->second;
            return insert({std::move(key), mapped_type()}).first->second;
        }

        size_t count(key_type const &key) const {
            if (find(key) != end())
                return 1;
            else
                return 0;
        }

        const_iterator find(key_type const &key) const {
            return const_iterator{m_table.find(key)};
        }

        iterator find(key_type const &key) {
            return iterator{m_table.find(key)};
        }

        std::pair<iterator, iterator> equal_range(key_type const &key) {
            auto i = find(key);
            if (i != end()) {
                auto j = i;
                ++j;
                return {i, j};
            } else {
                return {i, i};
            }
        }

        std::pair<const_iterator, const_iterator> equal_range(key_type const &key) const {
            auto i = find(key);
            if (i != end()) {
                auto j = i;
                ++j;
                return {i, j};
            } else {
                return {i, i};
            }
        }

        void reserve(size_t capacity) {
            m_table.reserve(capacity);
        }

        bool operator==(hash_map const &rhs) const {
            return m_table == rhs.m_table;
        }

        bool operator!=(hash_map const &rhs) const {
            return m_table != rhs.m_table;
        }

    private:
        Table m_table;
    };

    template<
            typename Key,
            typename Mapped,
            typename Hash,
            typename Equals,
            typename Allocator
    >
    bool operator==(const hash_map<Key,Mapped,Hash,Equals,Allocator>& xs, const hash_map<Key,Mapped,Hash,Equals,Allocator>& ys) {
        return xs.size() == ys.size() &&
               std::equal(xs.begin(), xs.end(), ys.begin());
    }

    template<
            typename Key,
            typename Mapped,
            typename Hash,
            typename Equals,
            typename Allocator
    >
    bool operator!=(const hash_map<Key,Mapped,Hash,Equals,Allocator>& xs, const hash_map<Key,Mapped,Hash,Equals,Allocator>& ys) {
        return !operator==(xs, ys);
    }

    template<
            typename Key,
            typename Mapped,
            typename Hash,
            typename Equals,
            typename Allocator
    >
    bool operator<(const hash_map<Key,Mapped,Hash,Equals,Allocator>& xs, const hash_map<Key,Mapped,Hash,Equals,Allocator>& ys) {
        return std::lexicographical_compare(xs.begin(), xs.end(), ys.begin(), ys.end());
    }

    template<
            typename Key,
            typename Mapped,
            typename Hash,
            typename Equals,
            typename Allocator
    >
    bool operator>=(const hash_map<Key,Mapped,Hash,Equals,Allocator>& xs, const hash_map<Key,Mapped,Hash,Equals,Allocator>& ys) {
        return !operator<(xs, ys);
    }
}}