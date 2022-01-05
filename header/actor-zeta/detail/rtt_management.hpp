#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "type_traits.hpp"

namespace actor_zeta {
namespace detail {

namespace management {
    template<typename T>
    auto copy(const void* source, void* destination)
        -> type_traits::enable_if_t<
            std::is_copy_constructible<T>::value> {
        assert(destination && "rtt management copy");
        new (destination) // Construct a `T` object, placing it directly into your
                          // pre-allocated storage at memory address `destination`.
            T(*static_cast<const T*>(source));
    }

    template<typename T>
    void move(const void* source, void* destination) {
        assert(destination && "rtt management move");
        new (destination) // Construct a `T` object, placing it directly into your
                          // pre-allocated storage at memory address `destination`.
            T(std::move(*static_cast<const T*>(source)));
    }

    template<typename T>
    void destroy(void* object) noexcept {
        static_cast<T*>(object)->~T();
    }

    enum struct operation_t {
        copy,
        move,
        destroy,
        size,
    };

    using manager_t = void (*)(operation_t, const void*, void*);

    template<typename T>
    void manage(operation_t todo, const void* source, void* destination) {
        switch (todo) {
            case operation_t::copy: {
                copy<T>(source, destination);
                break;
            }
            case operation_t::move: {
                move<T>(source, destination);
                break;
            }
            case operation_t::destroy: {
                assert(source == nullptr);
                destroy<T>(destination);
                break;
            }
            case operation_t::size: {
                assert(source == nullptr);
                *static_cast<std::size_t*>(destination) = sizeof(T);
                break;
            }
        }
    }

    struct object_info_t final {
        std::size_t offset;
        manager_t manage;
    };

    template<typename T>
    object_info_t make_object_info(std::size_t offset) noexcept {
        return object_info_t{offset, &manage<T>};
    }

    inline void destroy(const object_info_t& object, char* data) {
        object.manage(operation_t::destroy, nullptr, data + object.offset);
    }

    template<typename InputIterator>
    void destroy(InputIterator first, InputIterator last, char* data) {
        for (auto current = first; current != last; ++current) {
            destroy(*current, data);
        }
        /*std::for_each(first, last,
                      [data](const auto& object) {
                          destroy(object, data);
                      });*/
    }

    template<typename ForwardIterator>
    void
    move(
        ForwardIterator first,
        ForwardIterator last,
        char* source,
        char* destination) {
        for (auto current = first; current != last; ++current) {
#ifndef __EXCEPTIONS_DISABLE__
            try {
#endif
                current->manage(operation_t::move, source + current->offset, destination + current->offset);
#ifndef __EXCEPTIONS_DISABLE__
            } catch (...) {
                destroy(first, current, destination);
                throw;
            }
#endif
        }
        destroy(first, last, source);
    }

    template<typename ForwardIterator>
    void
    copy(
        ForwardIterator first,
        ForwardIterator last,
        const char* source,
        char* destination) {
        for (auto current = first; current != last; ++current) {
#ifndef __EXCEPTIONS_DISABLE__
            try {
#endif
                current->manage(operation_t::copy, source + current->offset, destination + current->offset);
#ifndef __EXCEPTIONS_DISABLE__
            } catch (...) {
                destroy(first, current, destination);
                throw;
            }
#endif
        }
    }

    template<typename T>
    bool conforms(const object_info_t& object) {
        return &manage<T> == object.manage;
    }

    inline std::size_t size_of(const object_info_t& object) {
        std::size_t size;
        object.manage(operation_t::size, nullptr, std::addressof(size));
        return size;
    }
}
}} // namespace actor_zeta::detail::management
