#pragma once

#include <actor-zeta/detail/aligned_allocate.hpp>
#include <actor-zeta/detail/rtt_management.hpp>

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

    inline void swap(rtt& left, rtt& right) {
        left.swap(right);
    }

}} // namespace actor_zeta::detail
