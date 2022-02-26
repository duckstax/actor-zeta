#pragma once

#include <actor-zeta/detail/aligned_allocate.hpp>
#include <actor-zeta/detail/pmr/default_resource.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/detail/type_traits.hpp>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace actor_zeta { namespace detail {

#ifdef __ENABLE_TESTS_MEASUREMENTS__

    namespace rtt_test {

        static size_t default_ctor_ = 0;
        static size_t copy_ctor_ = 0;
        static size_t const_copy_ctor_ = 0;
        static size_t move_ctor_ = 0;
        static size_t templated_ctor_ = 0;
        static size_t dtor_ = 0;

        static size_t move_operator_ = 0;
        static size_t const_copy_operator_ = 0;
        static size_t copy_operator_ = 0;

        inline void clear() {
            default_ctor_ = 0;
            copy_ctor_ = 0;
            const_copy_ctor_ = 0;
            move_ctor_ = 0;
            templated_ctor_ = 0;
            dtor_ = 0;
            move_operator_ = 0;
            const_copy_operator_ = 0;
            copy_operator_ = 0;
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

    template<typename T>
    void destroy(void* object) noexcept {
        static_cast<T*>(object)->~T();
    }

    template<typename T>
    void create(void* creation_place, void* object) noexcept {
        new (creation_place) T(std::forward<const T&>(*static_cast<T*>(object)));
    }

    class rtt final {
        using destroyer_t = void (*)(void*);
        using creator_t = void (*)(void*, void*);

        struct objects_t {
            std::size_t offset;
            destroyer_t destroyer;
            creator_t creator;
        };

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

#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::templated_ctor_++;
#endif
        }
        rtt()
            : m_memory_resource(actor_zeta::detail::pmr::get_default_resource())
            , m_capacity(0)
            , m_volume(0)
            , allocation(nullptr)
            , m_data(nullptr)
            , m_objects(nullptr)
            , m_objects_idx(0) {
#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::default_ctor_++;
#endif
        }
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
#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::move_ctor_++;
#endif
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
#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::const_copy_ctor_++;
#endif
        }
        rtt(rtt& other)
            : rtt(static_cast<const rtt&>(other)) {
#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::const_copy_ctor_--;
            rtt_test::copy_ctor_++;
#endif
        }

        ~rtt() {
            clear();
#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::dtor_++;
#endif
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

#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::move_operator_++;
#endif

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

#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::const_copy_operator_++;
#endif

            return *this;
        }
        rtt& operator=(rtt& other) noexcept {
#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt& ret = operator=(static_cast<const rtt&>(other));
            rtt_test::const_copy_operator_--;
            rtt_test::copy_operator_++;
            return ret;
#else
            return operator=(static_cast<const rtt&>(other));
#endif
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

    inline void swap(rtt& left, rtt& right) {
        left.swap(right);
    }

}} // namespace actor_zeta::detail
