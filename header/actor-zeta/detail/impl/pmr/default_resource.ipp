#pragma once

#include <actor-zeta/detail/aligned_allocate.hpp>
#include <actor-zeta/detail/pmr/default_resource.hpp>

namespace actor_zeta { namespace detail { namespace pmr {

#if CPP17_OR_GREATER

#if __has_include(<memory_resource>)

    memory_resource* get_default_resource() noexcept {
        return std::pmr::get_default_resource();
    }

    memory_resource* set_default_resource(memory_resource* new_res) noexcept {
        return std::pmr::set_default_resource(new_res);
    }

    memory_resource* new_delete_resource() noexcept {
        return std::pmr::new_delete_resource();
    }

    memory_resource* null_memory_resource() noexcept {
        return std::pmr::null_memory_resource();
    }

#else

    memory_resource* get_default_resource() noexcept {
        return std::experimental::pmr::get_default_resource();
    }

    memory_resource* set_default_resource(memory_resource* new_res) noexcept {
        return std::experimental::pmr::set_default_resource(new_res);
    }

    memory_resource* new_delete_resource() noexcept {
        return std::experimental::pmr::new_delete_resource();
    }

    memory_resource* null_memory_resource() noexcept {
        return std::experimental::pmr::null_memory_resource();
    }

#endif

#elif CPP14_OR_GREATER or CPP11_OR_GREATER

#ifndef WEAK_CONSTINIT
#ifndef NO_DESTROY
    REQUIRE_CONST_INIT
    null_memory_resource_t::holder
        null_memory_resource_t::instance_;
#else
    REQUIRE_CONST_INIT
    null_memory_resource_t
        null_memory_resource_t::instance_;
#endif
#else
    null_memory_resource_t
        null_memory_resource_t::instance_;
#endif

    null_memory_resource_t::
        ~null_memory_resource_t() = default;

    void*
    null_memory_resource_t::do_allocate(
        std::size_t bytes,
        std::size_t alignment) {
        assert(false);
    }

    void
    null_memory_resource_t::do_deallocate(
        void* p,
        std::size_t bytes,
        std::size_t alignment) {}

    bool
    null_memory_resource_t::do_is_equal(
        memory_resource const& mr) const noexcept {
        return &mr == this;
    }

#ifndef WEAK_CONSTINIT
#ifndef NO_DESTROY
    REQUIRE_CONST_INIT
    default_memory_resource_t::holder
        default_memory_resource_t::instance_;
#else
    REQUIRE_CONST_INIT
    default_memory_resource_t
        default_memory_resource_t::instance_;
#endif
#else
    default_memory_resource_t
        default_memory_resource_t::instance_;
#endif

    default_memory_resource_t::
        ~default_memory_resource_t() = default;

    using detail::aligned_allocate;
    using detail::aligned_deallocate;

    void*
    default_memory_resource_t::
        do_allocate(
            std::size_t bytes,
            std::size_t alignment) {
        return aligned_allocate(bytes, alignment, [](size_t size) { return ::operator new(size); });
    }

    void
    default_memory_resource_t::
        do_deallocate(
            void* p,
            std::size_t bytes,
            std::size_t alignment) {
        aligned_deallocate(p, bytes, alignment, [](void* p) { ::operator delete(p); });
    }

    bool
    default_memory_resource_t::
        do_is_equal(
            memory_resource const& mr) const noexcept {
        return this == &mr;
    }

    memory_resource* get_default_resource() noexcept {
        return default_memory_resource_t::exchange();
    }

    memory_resource* set_default_resource(memory_resource* new_res) noexcept {
        return default_memory_resource_t::exchange(new_res);
    }

    memory_resource* new_delete_resource() noexcept {
        return default_memory_resource_t::exchange();
    }

    memory_resource* null_memory_resource() noexcept {
        return null_memory_resource_t::get();
    }

#endif

}}} // namespace actor_zeta::detail::pmr