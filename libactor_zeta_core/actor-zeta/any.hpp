#ifndef ANY_HPP
#define ANY_HPP

#include <new>
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <algorithm>

class any {
public:
    any() noexcept: content(nullptr) {}

    template<typename ValueType>
    any(const ValueType &value): content(new holder<ValueType>(value)) {}

    any(const any &other) : content(other.content ? other.content->clone() : nullptr) {}

    any(any &&other) noexcept : content(other.content) {
        other.content = nullptr;
    }

    template<typename ValueType>
    any(ValueType &&value) : content(new holder<ValueType>(std::move(value))) {}


    ~any() noexcept {
        delete content;
    }

    any &swap(any &rhs) noexcept {
        std::swap(content, rhs.content);
        return *this;
    }


    any &operator=(const any &rhs) {
        any(rhs).swap(*this);
        return *this;
    }

    any &operator=(any &&rhs)noexcept {
        rhs.swap(*this);
        any().swap(rhs);
        return *this;
    }

    template<class ValueType>
    any &operator=(ValueType &&rhs) {
        any(std::move(rhs)).swap(*this);
        return *this;
    }


    bool empty() const noexcept {
        return !content;
    }

    void clear() noexcept {
        any().swap(*this);
    }

    template <typename T>
    T get() {
        return static_cast<holder<T>*>(content)->held;
    }

private:

    struct placeholder {
        virtual ~placeholder() {}

        virtual placeholder *clone() const = 0;
    };

    template<typename ValueType>
    struct holder : public placeholder {


        holder(const ValueType &value) : held(value) {
        }


        holder(ValueType &&value) : held(std::move(value)) {
        }

        virtual placeholder *clone() const {
            return new holder(held);
        }

        ValueType held;

        holder &operator=(const holder &) = delete;
    };

private:
    placeholder *content;
};

inline void swap(any &lhs, any &rhs)noexcept {
    lhs.swap(rhs);
}


template<typename ValueType>
ValueType any_cast(any & operand) {
    return operand.get<ValueType>();
}

#endif