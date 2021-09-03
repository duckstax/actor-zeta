#pragma once

#include <cassert>
#include <cstdio>
#include <functional>
#include <string>

struct type_id_t {
    friend bool operator==(type_id_t const& LHS, type_id_t const& RHS) { return LHS.m_id == RHS.m_id; }
    friend bool operator!=(type_id_t const& LHS, type_id_t const& RHS) { return LHS.m_id != RHS.m_id; }

    std::string name() const {
        return m_id;
    }

private:
    explicit constexpr type_id_t(const char* xid)
        : m_id(xid) {}

    type_id_t(const type_id_t&) = delete;
    type_id_t& operator=(type_id_t const&) = delete;

    const char* const m_id;
    template<class T>
    friend type_id_t const& make_type_id_impl();
};

template<class T>
inline type_id_t const& make_type_id_impl() {
    static const type_id_t id(__PRETTY_FUNCTION__);
    return id;
}

template<class T>
struct type_wrapper_t {};

template<class T>
inline type_id_t const& make_type_id() {
    return make_type_id_impl<type_wrapper_t<T>>();
}

template<class... Args>
struct argument_list_id_t {};

template<class... Args>
inline type_id_t const& make_argument_id() {
    return make_type_id_impl<argument_list_id_t<Args...>>();
}

#define COMPARE_TYPEID(LHS, RHS) compare_type_id_verbose(#LHS, LHS, #RHS, RHS)

inline bool compare_type_id_verbose(const char* LHSString, type_id_t const* LHS,
                                 const char* RHSString, type_id_t const* RHS) {
    if (*LHS == *RHS)
        return true;
    std::printf("type_id_t's not equal:\n");
    std::printf("%s: %s\n----------\n%s: %s\n",
                LHSString, LHS->name().c_str(),
                RHSString, RHS->name().c_str());
    return false;
}
