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
        auto type() const -> abstract;
        auto ptr() -> void*;

    private:
        abstract type_;
        void* ptr_;
    };

    auto name_(address_t& address)->detail::string_view;
    auto enqueue_(address_t& address, message msg) -> void;


}

