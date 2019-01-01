#pragma once

#include <vector>
#include <utility>
#include <cstddef>

namespace actor_zeta { namespace  detail {

    template<
            typename Value,
            typename Key,
            typename GetKey,
            typename Hash,
            typename Equals,
            typename Allocator
    >
    struct hash_table final {
    private:
        constexpr static size_t const NPos = (size_t) -1;
        constexpr static size_t const EmptyHashValue = 0;
        constexpr static size_t const EndHashValue = 1;
        constexpr static size_t const FilledHashBit = (size_t) 1 << (sizeof(size_t) * 8 - 1);

        struct Bucket final {
            Bucket() {
                this->hash = EmptyHashValue;
            }

            ~Bucket() {
                if (auto s = valuePtr())
                    s->~Value();
            }

            Bucket(Bucket const &rhs) {
                this->hash = rhs.hash;
                if (auto o = rhs.valuePtr())
                    new(&this->value) Value(*o);
            }

            Bucket(Bucket &&rhs) {
                this->hash = rhs.hash;
                if (auto o = rhs.valuePtr())
                    new(&this->value) Value(std::move(*o));}

            Bucket &operator=(Bucket const &rhs) {
                if (auto o = rhs.valuePtr()) {
                    if (auto s = valuePtr())
                        *s = *o;
                    else
                        new(&this->value) Value(*o);
                } else {
                    if (auto s = valuePtr())
                        s->~Value();
                }
                this->hash = rhs.hash;
                return *this;
            }

            Bucket &operator=(Bucket &&rhs) {
                if (auto o = rhs.valuePtr()) {
                    if (auto s = valuePtr())
                        *s = std::move(*o);
                    else
                        new(&this->value) Value(std::move(*o));
                } else {
                    if (auto s = valuePtr())
                        s->~Value();
                }
                this->hash = rhs.hash;
                return *this;
            }

            void setFilled(size_t hash, Value value) {
                if (auto s = valuePtr())
                    *s = std::move(value);
                else
                    new(&this->value) Value(std::move(value));
                this->hash = hash | FilledHashBit;
            }

            void setEmpty(){
                if (auto s = valuePtr())
                    s->~Value();
                this->hash = EmptyHashValue;
            }

            void setEnd() {
                if (auto s = valuePtr())
                    s->~Value();
                this->hash = EndHashValue;
            }

            Value const *valuePtr() const {
                if (hash & FilledHashBit) {
                    return &this->value;
                }
                return nullptr;
            }

            Value *valuePtr() {
                if (hash & FilledHashBit) {
                    return &this->value;
                }
                return nullptr;
            }

            bool isEmpty() const {
                return this->hash == EmptyHashValue;
            }

            bool isEnd() const {
                return this->hash == EndHashValue;
            }

            size_t hash;
            union {
                Value value;
            };
        };

        using Buckets = std::vector<Bucket, typename Allocator::template rebind<Bucket>::other>;

    public:
        struct const_iterator final {
            bool operator==(const_iterator const &rhs) const {
                return current == rhs.current;
            }

            bool operator!=(const_iterator const &rhs) const {
                return current != rhs.current;
            }

            const_iterator &operator++() {
                current = hash_table::scanIterator(++current);
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator copy(*this);
                operator++();
                return copy;
            }

            Value const &operator*() const {
                return *operator->();
            }

            Value const *operator->() const {
                return current->valuePtr();
            }

            typename Buckets::const_iterator current;
        };

        struct iterator final {
            bool operator==(iterator const &rhs) const {
                return current == rhs.current;
            }

            bool operator!=(iterator const &rhs) const {
                return current != rhs.current;
            }

            iterator &operator++() {
                current = hash_table::scanIterator(++current);
                return *this;
            }

            iterator operator++(int) {
                iterator copy(*this);
                operator++();
                return copy;
            }

            Value &operator*() const {
                return *operator->();
            }

            Value *operator->() const {
                return current->valuePtr();
            }

            operator const_iterator() const {
                return const_iterator{current};
            }

            typename Buckets::iterator current;
        };

        hash_table(
                size_t bucketCount,
                GetKey const &getKey,
                Hash const &hash,
                Equals const &equal,
                Allocator const &alloc
        ):m_buckets(alloc),
          m_maxFillLevel(DefaultMaxFillLevel),
          m_filledCount(0),
          m_getKey(getKey),
          m_hash(hash),
          m_equals(equal) {
            if (bucketCount != 0) {
                checkCapacity(bucketCount);
            }
        }

        iterator begin() {
            if (m_buckets.empty()) {
                return end();
            }
            return iterator{scanIterator(m_buckets.begin())};
        }

        iterator end() {
            return iterator{--m_buckets.end()};
        }

        const_iterator begin() const {
            return const_cast<hash_table *>(this)->begin();
        }

        const_iterator end() const {
            return const_cast<hash_table *>(this)->end();
        }

        size_t empty() const {
            return m_filledCount == 0;
        }

        size_t size() const {
            return m_filledCount;
        }

        void clear() {

            if (m_buckets.empty()) {
                return;
            }

            for (size_t i = 0; i < m_buckets.size() - 1; ++i) {
                m_buckets[i].setEmpty();
            }

            m_filledCount = 0;
        }

        std::pair<iterator, bool> insert(Value const &value) {
            return doInsert(Value(value));
        }

        std::pair<iterator, bool> insert(Value &&value) {
            return doInsert(std::move(value));
        }

        iterator erase(const_iterator pos) {
            size_t bucketIndex = pos.current - m_buckets.begin();
            size_t currentBucketIndex = bucketIndex;
            auto currentBucket = &m_buckets[currentBucketIndex];

            while (true) {
                size_t nextBucketIndex = hashBucket(currentBucketIndex + 1);
                auto nextBucket = &m_buckets[nextBucketIndex];
                if (auto nextPtr = nextBucket->valuePtr()) {
                    if (bucketError(nextBucketIndex, nextBucket->hash) > 0) {
                        currentBucket->hash = nextBucket->hash;
                        *currentBucket->valuePtr() = std::move(*nextPtr);
                        currentBucketIndex = nextBucketIndex;
                        currentBucket = nextBucket;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }

            m_buckets[currentBucketIndex].setEmpty();
            --m_filledCount;

            return iterator{scanIterator(m_buckets.begin() + bucketIndex)};
        }

        iterator erase(const_iterator first, const_iterator last) {

            while (first != last) {
                first = erase(first);
            }

            return iterator{m_buckets.begin() + (first.current - m_buckets.begin())};
        }

        const_iterator find(Key const &key) const {
            return const_cast<hash_table *>(this)->find(key);
        }

        iterator find(Key const &key) {
            if (m_buckets.empty())
                return end();

            size_t hash = m_hash(key) | FilledHashBit;
            size_t targetBucket = hashBucket(hash);
            size_t currentBucket = targetBucket;
            while (true) {
                auto &bucket = m_buckets[currentBucket];
                if (auto value = bucket.valuePtr()) {

                    if (bucket.hash == hash && m_equals(m_getKey(*value), key)) {
                        return iterator{m_buckets.begin() + currentBucket};
                    }

                    size_t entryError = bucketError(currentBucket, bucket.hash);
                    size_t findError = bucketError(currentBucket, targetBucket);

                    if (findError > entryError) {
                        return end();
                    }

                    currentBucket = hashBucket(currentBucket + 1);

                } else {
                    return end();
                }
            }
        }

        double maxFillLevel() const {
            return m_maxFillLevel;
        }

        void setMaxFillLevel(double maxFillLevel) {
            m_maxFillLevel = maxFillLevel;
        }

        void reserve(size_t capacity) {
            if (capacity > m_filledCount)
                checkCapacity(capacity - m_filledCount);
        }

        Allocator getAllocator() const {
            return m_buckets.get_allocator();
        }

        bool operator==(hash_table const &rhs) const {
            if (size() != rhs.size()) {
                return false;
            }

            auto i = begin();
            auto j = rhs.begin();
            auto e = end();

            while (i != e) {
                if (*i != *j) {
                    return false;
                }
                ++i;
                ++j;
            }

            return true;
        }

        bool operator!=(hash_table const &rhs) const {
            return !operator==(rhs);
        }

    private:
        static constexpr size_t MinCapacity = 8;
        static constexpr double DefaultMaxFillLevel = 0.7;

        // Scans for the next bucket value that is non-empty
        static typename Buckets::iterator scanIterator(typename Buckets::iterator i) {
            while (i->isEmpty())
                ++i;
            return i;
        }

        static typename Buckets::const_iterator scanIterator(typename Buckets::const_iterator i) {
            while (i->isEmpty())
                ++i;
            return i;
        }

        size_t hashBucket(size_t hash) const {
            return hash & (m_buckets.size() - 2);
        }

        size_t bucketError(size_t current, size_t target) const {
            return hashBucket(current - target);
        }

        void checkCapacity(size_t additionalCapacity) {
            size_t newSize;
            if (!m_buckets.empty())
                newSize = m_buckets.size() - 1;
            else
                newSize = MinCapacity;

            while ((double) (m_filledCount + additionalCapacity) / (double) newSize > m_maxFillLevel)
                newSize *= 2;

            if (newSize == m_buckets.size() - 1)
                return;

            Buckets oldBuckets;
            swap(m_buckets, oldBuckets);

            // Leave an extra end entry when allocating buckets, so that iterators are
            // simpler and can simply iterate until they find something that is not an
            // empty entry.
            m_buckets.resize(newSize + 1);
            m_buckets[newSize].setEnd();

            m_filledCount = 0;

            for (auto &entry : oldBuckets) {
                if (auto ptr = entry.valuePtr()) {
                    insert(std::move(*ptr));
                }
            }
        }

        std::pair<iterator, bool> doInsert(Value value) {
            checkCapacity(1);

            size_t hash = m_hash(m_getKey(value)) | FilledHashBit;
            size_t targetBucket = hashBucket(hash);
            size_t currentBucket = targetBucket;
            size_t insertedBucket = NPos;

            while (true) {
                auto &target = m_buckets[currentBucket];
                if (auto entryValue = target.valuePtr()) {
                    if (target.hash == hash && m_equals(m_getKey(*entryValue), m_getKey(value))) {
                        return std::make_pair(iterator{m_buckets.begin() + currentBucket}, false);
                    }

                    size_t entryTargetBucket = hashBucket(target.hash);
                    size_t entryError = bucketError(currentBucket, entryTargetBucket);
                    size_t addError = bucketError(currentBucket, targetBucket);
                    if (addError > entryError) {
                        if (insertedBucket == NPos) {
                            insertedBucket = currentBucket;
                        }

                        std::swap(value, *entryValue);
                        std::swap(hash, target.hash);
                        targetBucket = entryTargetBucket;
                    }
                    currentBucket = hashBucket(currentBucket + 1);

                } else {
                    target.setFilled(hash, std::move(value));
                    ++m_filledCount;
                    if (insertedBucket == NPos)
                        insertedBucket = currentBucket;

                    return std::make_pair(iterator{m_buckets.begin() + insertedBucket}, true);
                }
            }
        }

        Buckets m_buckets;
        double m_maxFillLevel;
        size_t m_filledCount;

        GetKey m_getKey;
        Hash m_hash;
        Equals m_equals;
    };

    template<typename Value, typename Key, typename GetKey, typename Hash, typename Equals, typename Allocator>
    constexpr size_t hash_table<Value, Key, GetKey, Hash, Equals, Allocator>::MinCapacity;

    template<typename Value, typename Key, typename GetKey, typename Hash, typename Equals, typename Allocator>
    constexpr double hash_table<Value, Key, GetKey, Hash, Equals, Allocator>::DefaultMaxFillLevel;

}}