#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <type_traits>

#include <actor-zeta/forwards.hpp>
#include <actor-zeta/config.hpp>
#include <actor-zeta/detail/string_view.hpp>

namespace actor_zeta {

    class address_t final {
    public:
        address_t() = default;
        address_t(address_t&&) = default;
        address_t(const address_t&) = default;
        address_t& operator=(address_t&&) = default;
        address_t& operator=(const address_t&) = default;
        ~address_t() =default;

        explicit address_t(abstract_actor*);
        explicit address_t(abstract_supervisor*);

        void swap(address_t&) noexcept;
        explicit operator bool() const;
        auto name() const ->detail::string_view;
        auto enqueue(message msg) -> void;

    private:
        enum class abstract : char {
            non = 0x00,
            actor,
            supervisor
        };
        abstract type_;
        union storage {
            storage() {
                actor = nullptr;
                supervisor = nullptr;
            }
            explicit storage(abstract_actor*ptr):actor(ptr){}
            explicit storage(abstract_supervisor*ptr):supervisor(ptr){}
            ~storage() {
                actor = nullptr;
                supervisor = nullptr;
            }
            abstract_actor* actor;
            abstract_supervisor* supervisor;
        }  ptr_;
    };

}

