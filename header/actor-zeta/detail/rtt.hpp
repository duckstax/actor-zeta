#pragma once

#include <actor-zeta/detail/aligned_allocate.hpp>
#include <actor-zeta/detail/pmr/default_resource.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/detail/rtt_management.hpp>
#include <actor-zeta/detail/type_traits.hpp>

#include <iostream>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace actor_zeta { namespace detail {

#ifdef __TESTS_ENABLED__

    namespace rtt_test {

        static size_t copy_ctor_ = 0;
        static size_t const_copy_ctor_ = 0;
        static size_t move_ctor_ = 0;
        static size_t templated_ctor_ = 0;
        static size_t dtor_ = 0;

        inline void clear() {
            copy_ctor_ = 0;
            const_copy_ctor_ = 0;
            move_ctor_ = 0;
            templated_ctor_ = 0;
            dtor_ = 0;
        }

    } // namespace rtt_test

#endif

    inline void dummy(std::initializer_list<int>) {}

#define EXPAND_VARIADIC(expression) \
    dummy({(expression, 0)...})

    template<size_t N>
    constexpr size_t getSize() {
        return N;
    }

    template<size_t N, class Head, class... Args>
    constexpr size_t getSize() {
        return getSize<((N + alignof(Head) - 1) & -(alignof(Head))) + sizeof(Head), Args...>();
    }

    namespace impl_new {

        template<typename T>
        void destroy(void* object) noexcept {
            static_cast<T*>(object)->~T();
        }

        template<typename T>
        void create(void* creation_place, void* object) noexcept {
            new (creation_place) T(std::forward<const T&>(*static_cast<T*>(object)));
        }

        using destroyer_t = void (*)(void*);
        using creator_t = void (*)(void*, void*);

        struct objects_t {
            std::size_t offset;
            destroyer_t destroyer;
            creator_t creator;
        };

        class rtt final {
            actor_zeta::detail::pmr::memory_resource* m_memory_resource = nullptr;
            std::size_t m_capacity = 0;
            std::size_t m_volume = 0;
            void* allocation = nullptr;
            char* m_data = nullptr;

            objects_t* m_objects = nullptr;
            std::size_t m_objects_idx = 0;

            auto clear() -> void {
                auto tmp = m_data;
                for (std::size_t i = 0; i < m_objects_idx; ++i) {
                    m_objects[i].destroyer(tmp + m_objects[i].offset);
                }
                m_volume = 0;
                m_objects_idx = 0;
                if (allocation)
                    m_memory_resource->deallocate(allocation, m_capacity + m_capacity * sizeof(objects_t));
                allocation = nullptr;
                m_data = nullptr;
                m_objects = nullptr;
                m_capacity = 0;
            }

        public:
            template<typename... Args>
            explicit rtt(actor_zeta::detail::pmr::memory_resource* memory_resource, Args&&... args)
                : m_memory_resource(nullptr)
                , m_capacity(0)
                , m_volume(0)
                , allocation(nullptr)
                , m_data(nullptr)
                , m_objects(nullptr)
                , m_objects_idx(0) {
                constexpr std::size_t sz = getSize<0, Args...>();
                m_memory_resource = memory_resource ? memory_resource : actor_zeta::detail::pmr::get_default_resource();
                assert(m_memory_resource);
                m_capacity = sz;
                allocation = m_memory_resource->allocate(m_capacity + m_capacity * sizeof(objects_t));
                assert(allocation);
                m_data = static_cast<char*>(allocation);
                assert(m_data);
                m_objects = static_cast<objects_t*>(static_cast<void*>(m_data + m_capacity));
                assert(m_objects);

                EXPAND_VARIADIC(push_back_no_realloc(std::forward<Args>(args)));
            }
            rtt()
                : m_memory_resource(actor_zeta::detail::pmr::get_default_resource())
                , m_capacity(0)
                , m_volume(0)
                , allocation(nullptr)
                , m_data(nullptr)
                , m_objects(nullptr)
                , m_objects_idx(0) {}
            rtt(rtt&& other)
                : m_memory_resource(other.m_memory_resource)
                , m_capacity(other.m_capacity)
                , m_volume(other.m_volume)
                , allocation(other.allocation)
                , m_data(other.m_data)
                , m_objects(other.m_objects)
                , m_objects_idx(other.m_objects_idx) {
                other.m_memory_resource = nullptr;
                other.m_capacity = 0;
                other.m_volume = 0;
                other.allocation = nullptr;
                other.m_data = nullptr;
                other.m_objects = nullptr;
                other.m_objects_idx = 0;
            }
            rtt(const rtt& other)
                : m_memory_resource(other.m_memory_resource)
                , m_capacity(other.m_capacity)
                , m_volume(other.m_volume)
                , allocation(nullptr)
                , m_data(nullptr)
                , m_objects(nullptr)
                , m_objects_idx(0) {
                if (m_capacity > 0) {
                    allocation = m_memory_resource->allocate(m_capacity + m_capacity * sizeof(objects_t));
                    assert(allocation);
                    m_data = static_cast<char*>(allocation);
                    assert(m_data);
                    for (std::size_t i = 0; i < other.m_objects_idx; ++i) {
                        assert(other.m_objects[i].offset < m_capacity);
                        other.m_objects[i].creator(
                            static_cast<void*>(m_data + other.m_objects[i].offset),
                            static_cast<void*>(other.m_data + other.m_objects[i].offset));
                    }
                    m_objects = static_cast<objects_t*>(static_cast<void*>(m_data + m_capacity));
                    assert(m_objects);
                    std::copy(other.m_objects, other.m_objects + other.m_objects_idx, m_objects);
                    m_objects_idx = other.m_objects_idx;
                }
            }
            rtt(rtt& other)
                : rtt(static_cast<const rtt&>(other)) {}

            ~rtt() {
                clear();
            }

            rtt& operator=(rtt&& other) noexcept {
                clear();

                m_memory_resource = other.m_memory_resource;
                m_capacity = other.m_capacity;
                m_volume = other.m_volume;
                allocation = other.allocation;
                m_data = other.m_data;
                m_objects = other.m_objects;
                m_objects_idx = other.m_objects_idx;

                other.m_memory_resource = nullptr;
                other.m_capacity = 0;
                other.m_volume = 0;
                other.allocation = nullptr;
                other.m_data = nullptr;
                other.m_objects = nullptr;
                other.m_objects_idx = 0;

                return *this;
            }
            rtt& operator=(const rtt& other) noexcept {
                clear();

                m_memory_resource = other.m_memory_resource;
                m_capacity = other.m_capacity;
                m_volume = other.m_volume;
                if (m_capacity > 0) {
                    allocation = m_memory_resource->allocate(m_capacity + m_capacity * sizeof(objects_t));
                    assert(allocation);
                    m_data = static_cast<char*>(allocation);
                    assert(m_data);
                    for (std::size_t i = 0; i < other.m_objects_idx; ++i) {
                        other.m_objects[i].creator(
                            static_cast<void*>(m_data + other.m_objects[i].offset),
                            static_cast<void*>(other.m_data + other.m_objects[i].offset));
                    }
                    m_objects = static_cast<objects_t*>(static_cast<void*>(m_data + m_capacity));
                    assert(m_objects);
                    std::copy(other.m_objects, other.m_objects + other.m_objects_idx, m_objects);
                    m_objects_idx = other.m_objects_idx;
                }
                return *this;
            }
            rtt& operator=(rtt& other) noexcept {
                return operator=(static_cast<const rtt&>(other));
            }

            template<typename T>
            char* try_to_align(const T&) {
                auto space_left = m_capacity - m_volume;
                void* creation_place = m_data + m_volume;
                auto aligned_place = actor_zeta::detail::align(alignof(T), sizeof(T), creation_place, space_left);
                return static_cast<char*>(aligned_place);
            }

            template<typename T>
            char* force_align(const T& object) {
                auto creation_place = try_to_align(object);
                assert(creation_place != nullptr);

                return creation_place;
            }

            template<typename T>
            void push_back_no_realloc(T&& object) {
                auto creation_place = force_align(object);

                using raw_type = actor_zeta::type_traits::decay_t<T>;
                new (creation_place) raw_type(std::forward<T>(object));
                const auto new_offset = static_cast<std::size_t>(creation_place - m_data);
                m_objects[m_objects_idx++] = objects_t{new_offset, &destroy<raw_type>, &create<raw_type>};
                m_volume = new_offset + sizeof(raw_type);
            }

            void swap(rtt& that) {
                using std::swap;

                swap(this->m_memory_resource, that.m_memory_resource);
                swap(this->m_capacity, that.m_capacity);
                swap(this->m_volume, that.m_volume);
                swap(this->allocation, that.allocation);
                swap(this->m_data, that.m_data);
                swap(this->m_objects, that.m_objects);
                swap(this->m_objects_idx, that.m_objects_idx);
            }

            template<typename T>
            const T& get(std::size_t index) const {
                return get_by_offset<T>(offset(index));
            }

            template<typename T>
            T& get(std::size_t index) {
                return get_by_offset<T>(offset(index));
            }

            std::size_t offset(std::size_t index) const {
                return m_objects[index].offset;
            }

            template<typename T>
            const T& get_by_offset(std::size_t offset) const {
                return *static_cast<const T*>(static_cast<const void*>(m_data + offset));
            }

            template<typename T>
            T& get_by_offset(std::size_t offset) {
                return *static_cast<T*>(static_cast<void*>(m_data + offset)); // this is necessary to use double static_cast here, compile error
            }

            std::size_t size() const {
                return m_objects_idx;
            }

            std::size_t volume() const {
                return m_volume;
            }

            std::size_t capacity() const {
                return m_capacity;
            }

            bool empty() const {
                return m_objects_idx == 0;
            }
        };

    } // namespace impl_new

    namespace impl_old {

        // run-time tuple
        class rtt final {
        private:
            using object_info_container_type = std::vector<management::object_info_t>;

        public:
            using size_type = typename object_info_container_type::size_type;

        public:
            template<typename... Args>
            explicit rtt(Args&&... args)
                : m_capacity(getSize<0, Args...>())
                , m_data(std::move(std::unique_ptr<char[]>(new char[m_capacity]))) {
                m_objects.reserve(m_capacity);
#ifndef __EXCEPTIONS_DISABLE__
                try {
#endif
                    EXPAND_VARIADIC(push_back_no_realloc(std::forward<Args>(args)));
#ifndef __EXCEPTIONS_DISABLE__
                } catch (...) {
                    clear();
                    throw;
                }
#endif
#ifdef __TESTS_ENABLED__
                rtt_test::templated_ctor_++;
#endif
            }

            rtt() = default;

            /* move ctor and assignment op for rvalue */

            rtt(rtt&& that) noexcept
                : rtt() {
                this->swap(that);
#ifdef __TESTS_ENABLED__
                rtt_test::move_ctor_++;
#endif
            }

            rtt& operator=(rtt&& that) noexcept {
                clear();

                this->swap(that);
                return *this;
            }

            /* copy ctor and assignment op for const lvalue */

            rtt(const rtt& that)
                : m_capacity(that.m_volume)
                , m_data(std::move(std::unique_ptr<char[]>(new char[m_capacity])))
                , m_objects(that.m_objects)
                , m_volume(that.m_volume) {
#ifndef __EXCEPTIONS_DISABLE__
                try {
#endif
                    management::copy(m_objects.begin(), m_objects.end(), that.data(), this->data());
#ifndef __EXCEPTIONS_DISABLE__
                } catch (...) {
                    clear();
                    throw;
                }
#endif
#ifdef __TESTS_ENABLED__
                rtt_test::const_copy_ctor_++;
#endif
            }

            rtt& operator=(const rtt& that) {
                clear();

#ifndef __EXCEPTIONS_DISABLE__
                try {
#endif
                    reserve(that.m_volume);
                    management::copy(that.m_objects.begin(), that.m_objects.end(), that.data(), this->data());
                    static_assert(std::is_nothrow_move_assignable<object_info_container_type>::value, "");
                    m_objects = that.m_objects;
                    m_volume = that.m_volume;
#ifndef __EXCEPTIONS_DISABLE__
                } catch (...) {
                    clear();
                    throw;
                }
#endif

                return *this;
            }

            /* copy ctor and assignment op for non-const lvalue */

            rtt(rtt& that)
                : rtt(static_cast<const rtt&>(that)) {
#ifdef __TESTS_ENABLED__
                rtt_test::const_copy_ctor_--;
                rtt_test::copy_ctor_++;
#endif
            }

            rtt& operator=(rtt& that) {
                return operator=(static_cast<const rtt&>(that));
            }

            ~rtt() {
                destroy_all();
#ifdef __TESTS_ENABLED__
                rtt_test::dtor_++;
#endif
            }

            void swap(rtt& that) {
                using std::swap;

                swap(this->m_capacity, that.m_capacity);
                swap(this->m_data, that.m_data);
                swap(this->m_objects, that.m_objects);
                swap(this->m_volume, that.m_volume);
            }

            template<typename T>
            const T& get(size_type index) const {
                assert(management::conforms<T>(m_objects[index]));
                return get_by_offset<T>(offset(index));
            }

            template<typename T>
            T& get(size_type index) {
                assert(management::conforms<T>(m_objects[index]));
                return get_by_offset<T>(offset(index));
            }

            size_type offset(size_type index) const {
                return m_objects[index].offset;
            }

            template<typename T>
            const T& get_by_offset(size_type offset) const {
                return *static_cast<const T*>(static_cast<const void*>(data() + offset));
            }

            template<typename T>
            T& get_by_offset(size_type offset) {
                return *static_cast<T*>(static_cast<void*>(data() + offset)); // this is necessary to use double static_cast here, compile error
            }

            size_type size() const {
                return m_objects.size();
            }

            std::size_t volume() const {
                return m_volume;
            }

            std::size_t capacity() const {
                return m_capacity;
            }

            bool empty() const {
                return m_objects.empty();
            }

        private:
            void reserve(std::size_t new_capacity) {
                if (new_capacity > m_capacity) {
                    reallocate(std::max(new_capacity, m_capacity * CAPACITY_INCREASING_FACTOR));
                }
            }

            void shrink_to_fit() {
                if (m_capacity > m_volume) {
                    reallocate(m_volume);
                }
            }

            void clear() {
                destroy_all();
                m_volume = 0;
            }

            void reallocate(std::size_t new_capacity) {
                assert(new_capacity >= m_volume);
#ifndef __EXCEPTIONS_DISABLE__
                try {
#endif
                    auto new_data = std::unique_ptr<char[]>(new char[new_capacity]);
                    management::move(m_objects.begin(), m_objects.end(), data(), new_data.get());
                    std::swap(m_data, new_data);
                    m_capacity = new_capacity;
#ifndef __EXCEPTIONS_DISABLE__
                } catch (...) {
                    clear();
                    throw;
                }
#endif
            }

            char* data() {
                return m_data.get();
            }

            const char* data() const {
                return m_data.get();
            }

            template<typename T>
            char* set_up_creation_place(const T& object) {
                if (auto proposed_creation_place = try_to_align(object)) {
                    return proposed_creation_place;
                } else {
                    reserve(volume() + sizeof(T) + alignof(T));
                    return force_align(object);
                }
            }

            template<typename T>
            void push_back_no_realloc(T&& object) {
                auto creation_place = force_align(object);
                accommodate(std::forward<T>(object), creation_place);
            }

            template<typename T>
            char* try_to_align(const T&) {
                auto space_left = capacity() - volume();
                void* creation_place = data() + volume();
                auto aligned_place = align(alignof(T), sizeof(T), creation_place, space_left);
                return static_cast<char*>(aligned_place);
            }

            template<typename T>
            char* force_align(const T& object) {
                auto creation_place = try_to_align(object);
                assert(creation_place != nullptr);

                return creation_place;
            }

            template<typename T>
            void accommodate(T&& object, char* creation_place) {
                assert(creation_place && "rtt accommodate creation_place");
#ifndef __EXCEPTIONS_DISABLE__
                try {
#endif
                    using raw_type = type_traits::decay_t<T>;
                    new (creation_place) raw_type(std::forward<T>(object));

                    const auto new_offset = static_cast<std::size_t>(creation_place - data());
                    m_objects.push_back(management::make_object_info<raw_type>(new_offset));
                    m_volume = new_offset + sizeof(raw_type);
#ifndef __EXCEPTIONS_DISABLE__
                } catch (...) {
                    clear();
                    throw;
                }
#endif
            }

            void destroy_all() {
                management::destroy(m_objects.begin(), m_objects.end(), data());
                m_objects.clear();
            }

            static constexpr auto CAPACITY_INCREASING_FACTOR = std::size_t{2};

            std::size_t m_capacity = 0;
            std::unique_ptr<char[]> m_data;

            object_info_container_type m_objects; // uptr
            std::size_t m_volume = 0;
        };

    } // namespace impl_old

    using rtt = impl_new::rtt;

    inline void swap(rtt& left, rtt& right) {
        left.swap(right);
    }

}} // namespace actor_zeta::detail
