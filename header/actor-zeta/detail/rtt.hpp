#pragma once

#include <actor-zeta/detail/aligned_allocate.hpp>
#include <actor-zeta/detail/pmr/default_resource.hpp>
#include <actor-zeta/detail/pmr/memory_resource.hpp>
#include <actor-zeta/detail/type_list.hpp>
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

        actor_zeta::detail::pmr::memory_resource* memory_resource_ = nullptr;

        std::size_t capacity_ = 0;
        std::size_t volume_ = 0;

        void* allocation = nullptr;
        char* data_ = nullptr;

        objects_t* objects_ = nullptr;
        std::size_t objects_idx_ = 0;

        auto clear() -> void {
            auto tmp = data_;
            for (std::size_t i = 0; i < objects_idx_; ++i) {
                objects_[i].destroyer(tmp + objects_[i].offset);
            }
            volume_ = 0;
            objects_idx_ = 0;
            if (allocation)
                memory_resource_->deallocate(allocation, capacity_ + capacity_ * sizeof(objects_t));
            allocation = nullptr;
            data_ = nullptr;
            objects_ = nullptr;
            capacity_ = 0;
        }

    public:
        template<typename... Args>
        explicit rtt(actor_zeta::detail::pmr::memory_resource* memory_resource, Args&&... args)
            : memory_resource_(nullptr)
            , capacity_(0)
            , volume_(0)
            , allocation(nullptr)
            , data_(nullptr)
            , objects_(nullptr)
            , objects_idx_(0) {
            constexpr std::size_t sz = getSize<0, Args...>();
            memory_resource_ = memory_resource ? memory_resource : actor_zeta::detail::pmr::get_default_resource();
            assert(memory_resource_);
            capacity_ = sz;
            allocation = memory_resource_->allocate(capacity_ + capacity_ * sizeof(objects_t));
            assert(allocation);
            data_ = static_cast<char*>(allocation);
            assert(data_);
            objects_ = static_cast<objects_t*>(static_cast<void*>(data_ + capacity_));
            assert(objects_);

            EXPAND_VARIADIC(push_back_no_realloc(std::forward<Args>(args)));

#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::templated_ctor_++;
#endif
        }
        rtt()
            : memory_resource_(actor_zeta::detail::pmr::get_default_resource())
            , capacity_(0)
            , volume_(0)
            , allocation(nullptr)
            , data_(nullptr)
            , objects_(nullptr)
            , objects_idx_(0) {
#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::default_ctor_++;
#endif
        }
        rtt(rtt&& other)
            : memory_resource_(other.memory_resource_)
            , capacity_(other.capacity_)
            , volume_(other.volume_)
            , allocation(other.allocation)
            , data_(other.data_)
            , objects_(other.objects_)
            , objects_idx_(other.objects_idx_) {
            other.memory_resource_ = nullptr;
            other.capacity_ = 0;
            other.volume_ = 0;
            other.allocation = nullptr;
            other.data_ = nullptr;
            other.objects_ = nullptr;
            other.objects_idx_ = 0;
#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::move_ctor_++;
#endif
        }
        rtt(const rtt& other)
            : memory_resource_(other.memory_resource_)
            , capacity_(other.capacity_)
            , volume_(other.volume_)
            , allocation(nullptr)
            , data_(nullptr)
            , objects_(nullptr)
            , objects_idx_(0) {
            if (capacity_ > 0) {
                allocation = memory_resource_->allocate(capacity_ + capacity_ * sizeof(objects_t));
                assert(allocation);
                data_ = static_cast<char*>(allocation);
                assert(data_);
                for (std::size_t i = 0; i < other.objects_idx_; ++i) {
                    assert(other.objects_[i].offset < capacity_);
                    other.objects_[i].creator(
                        static_cast<void*>(data_ + other.objects_[i].offset),
                        static_cast<void*>(other.data_ + other.objects_[i].offset));
                }
                objects_ = static_cast<objects_t*>(static_cast<void*>(data_ + capacity_));
                assert(objects_);
                std::copy(other.objects_, other.objects_ + other.objects_idx_, objects_);
                objects_idx_ = other.objects_idx_;
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

            memory_resource_ = other.memory_resource_;
            capacity_ = other.capacity_;
            volume_ = other.volume_;
            allocation = other.allocation;
            data_ = other.data_;
            objects_ = other.objects_;
            objects_idx_ = other.objects_idx_;

            other.memory_resource_ = nullptr;
            other.capacity_ = 0;
            other.volume_ = 0;
            other.allocation = nullptr;
            other.data_ = nullptr;
            other.objects_ = nullptr;
            other.objects_idx_ = 0;

#ifdef __ENABLE_TESTS_MEASUREMENTS__
            rtt_test::move_operator_++;
#endif

            return *this;
        }
        rtt& operator=(const rtt& other) noexcept {
            clear();

            memory_resource_ = other.memory_resource_;
            capacity_ = other.capacity_;
            volume_ = other.volume_;
            if (capacity_ > 0) {
                allocation = memory_resource_->allocate(capacity_ + capacity_ * sizeof(objects_t));
                assert(allocation);
                data_ = static_cast<char*>(allocation);
                assert(data_);
                for (std::size_t i = 0; i < other.objects_idx_; ++i) {
                    other.objects_[i].creator(
                        static_cast<void*>(data_ + other.objects_[i].offset),
                        static_cast<void*>(other.data_ + other.objects_[i].offset));
                }
                objects_ = static_cast<objects_t*>(static_cast<void*>(data_ + capacity_));
                assert(objects_);
                std::copy(other.objects_, other.objects_ + other.objects_idx_, objects_);
                objects_idx_ = other.objects_idx_;
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
            auto space_left = capacity_ - volume_;
            void* creation_place = data_ + volume_;
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
            const auto new_offset = static_cast<std::size_t>(creation_place - data_);
            objects_[objects_idx_++] = objects_t{new_offset, &destroy<raw_type>, &create<raw_type>};
            volume_ = new_offset + sizeof(raw_type);
        }

        void swap(rtt& that) {
            using std::swap;

            swap(this->memory_resource_, that.memory_resource_);
            swap(this->capacity_, that.capacity_);
            swap(this->volume_, that.volume_);
            swap(this->allocation, that.allocation);
            swap(this->data_, that.data_);
            swap(this->objects_, that.objects_);
            swap(this->objects_idx_, that.objects_idx_);
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
            return objects_[index].offset;
        }

        template<typename T>
        const T& get_by_offset(std::size_t offset) const {
            return *static_cast<const T*>(static_cast<const void*>(data_ + offset));
        }

        template<typename T>
        T& get_by_offset(std::size_t offset) {
            return *static_cast<T*>(static_cast<void*>(data_ + offset)); // this is necessary to use double static_cast here, compile error
        }

        std::size_t size() const {
            return objects_idx_;
        }

        std::size_t volume() const {
            return volume_;
        }

        std::size_t capacity() const {
            return capacity_;
        }

        bool empty() const {
            return objects_idx_ == 0;
        }
    };

    inline void swap(rtt& left, rtt& right) {
        left.swap(right);
    }

    template<std::size_t I, class List>
    typename type_traits::type_list_at_t<List, I> get(rtt& r) {
        return static_cast<typename type_traits::type_list_at_t<List, I>>(
            r.get<typename type_traits::decay_t<type_traits::type_list_at_t<List, I>>>(I));
    }

}} // namespace actor_zeta::detail
