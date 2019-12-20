#pragma once

#include <new>
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include <actor-zeta/detail/type_traits.hpp>
#include <cassert>

namespace actor_zeta { namespace detail {
///
/// @brief
///

/// Drop-in replacement for C++17 std::any.

#if EASTL_RTTI_ENABLED
#include <typeinfo>
#endif
#if EASTL_EXCEPTIONS_ENABLED
#include <exception>
#endif


#if EASTL_EXCEPTIONS_ENABLED
            struct bad_cast : std::exception
    {
        const char* what() const EA_NOEXCEPT EA_OVERRIDE
            { return "bad cast"; }
    };

    struct bad_any_cast : public bad_cast
    {
        const char* what() const EA_NOEXCEPT EA_OVERRIDE
            { return "bad_any_cast"; }
    };
#endif

            namespace Internal {
                // utility to switch between exceptions and asserts
                inline void DoBadAnyCast() {
#if EASTL_EXCEPTIONS_ENABLED
                    throw bad_any_cast();
#else
                    assert(false);///, "bad_any_cast\n");

                    // NOTE(rparolin): CRASH!
                    // You crashed here because you requested a type that was not contained in the object.
                    // We choose to intentionally crash here instead of returning invalid data to the calling
                    // code which could cause hard to track down bugs.
                    *((volatile int *) 0) = 0xDEADC0DE;
#endif
                }

                template<typename T, typename... Args>
                void *DefaultConstruct(Args &&... args) {
                    return ::new T(std::forward<Args>(args)...);
                }

                template<typename T>
                void DefaultDestroy(T *p) {
                    p->~T();
                    delete p;
                }
            }

            class any final {
                enum class storage_operation {
                    GET,
                    DESTROY,
                    COPY,
                    MOVE,
                    TYPE_INFO
                };


                union storage {
                    using internal_storage_t = type_traits::aligned_storage_t<4 * sizeof(void *), std::alignment_of<void *>::value>;

                    void *external_storage = nullptr;
                    internal_storage_t internal_storage;
                };



                template<typename T>
                using use_internal_storage = type_traits::bool_constant
                        <
                                std::is_nothrow_move_constructible<T>::value
                                && (sizeof(T) <= sizeof(storage)) &&
                                (std::alignment_of<storage>::value % std::alignment_of<T>::value == 0)
                        >;


                template<class ValueType>
                friend const ValueType *any_cast(const any *pAny) noexcept;

                template<class ValueType>
                friend ValueType *any_cast(any *pAny) noexcept;

                template<class ValueType>
                friend ValueType any_cast(const any &operand);

                template<class ValueType>
                friend ValueType any_cast(any &operand);

                template<class ValueType>
                friend ValueType any_cast(any &&operand);

                template<class ValueType>
                friend const ValueType *unsafe_any_cast(const any *pAny) noexcept;

                template<class ValueType>
                friend ValueType *unsafe_any_cast(any *pAny) noexcept;


                template<typename T>
                struct storage_handler_internal {
                    template<typename V>
                    static void construct(storage &s, V &&v) {
                        ::new(&s.internal_storage) T(std::forward<V>(v));
                    }

                    template<typename... Args>
                    static void construct_inplace(storage &s, Args... args) {
                        ::new(&s.internal_storage) T(std::forward<Args>(args)...);
                    }

                    template<class NT, class U, class... Args>
                    static void construct_inplace(storage &s, std::initializer_list<U> il, Args &&... args) {
                        ::new(&s.internal_storage) NT(il, std::forward<Args>(args)...);
                    }

                    static inline void destroy(any &refAny) {
                        T &t = *static_cast<T *>(static_cast<void *>(&refAny.m_storage.internal_storage));
                        t.~T();

                        refAny.m_handler = nullptr;
                    }

                    static void *handler_func(storage_operation op, const any *pThis, any *pOther) {
                        switch (op) {
                            case storage_operation::GET: {
                                assert(pThis);
                                return (void *) (&pThis->m_storage.internal_storage);
                            }
                                break;

                            case storage_operation::DESTROY: {
                                assert(pThis);
                                destroy(const_cast<any &>(*pThis));
                            }
                                break;

                            case storage_operation::COPY: {
                                assert(pThis);
                                assert(pOther);
                                construct(pOther->m_storage, *(T *) (&pThis->m_storage.internal_storage));
                            }
                                break;

                            case storage_operation::MOVE: {
                                assert(pThis);
                                assert(pOther);
                                construct(pOther->m_storage, std::move(*(T *) (&pThis->m_storage.internal_storage)));
                                destroy(const_cast<any &>(*pThis));
                            }
                                break;

                            case storage_operation::TYPE_INFO: {
#if EASTL_RTTI_ENABLED
                                return (void*)&typeid(T);
#endif
                            }
                                break;

                            default: {
                                assert(false);//, "unknown storage operation\n");
                            }
                                break;
                        };

                        return nullptr;
                    }
                };

                template<typename T>
                struct storage_handler_external {
                    template<typename V>
                    static inline void construct(storage &s, V &&v) {
                        s.external_storage = Internal::DefaultConstruct<T>(std::forward<V>(v));
                    }

                    template<typename... Args>
                    static inline void construct_inplace(storage &s, Args... args) {
                        s.external_storage = Internal::DefaultConstruct<T>(std::forward<Args>(args)...);
                    }

                    template<class NT, class U, class... Args>
                    static inline void construct_inplace(storage &s, std::initializer_list<U> il, Args &&... args) {
                        s.external_storage = Internal::DefaultConstruct<NT>(il, std::forward<Args>(args)...);
                    }

                    static inline void destroy(any &refAny) {
                        Internal::DefaultDestroy(static_cast<T *>(refAny.m_storage.external_storage));
                        refAny.m_handler = nullptr;
                    }

                    static void *handler_func(storage_operation op, const any *pThis, any *pOther) {
                        switch (op) {
                            case storage_operation::GET: {
                                assert(pThis);
                                assert(pThis->m_storage.external_storage);
                                return static_cast<void *>(pThis->m_storage.external_storage);
                            }
                                break;

                            case storage_operation::DESTROY: {
                                assert(pThis);
                                destroy(*const_cast<any *>(pThis));
                            }
                                break;

                            case storage_operation::COPY: {
                                assert(pThis);
                                assert(pOther);
                                construct(pOther->m_storage, *static_cast<T *>(pThis->m_storage.external_storage));
                            }
                                break;

                            case storage_operation::MOVE: {
                                assert(pThis);
                                assert(pOther);
                                construct(pOther->m_storage, std::move(*(T *) (pThis->m_storage.external_storage)));
                                destroy(const_cast<any &>(*pThis));
                            }
                                break;

                            case storage_operation::TYPE_INFO: {
#if EASTL_RTTI_ENABLED
                                return (void*)&typeid(T);
#endif
                            }
                                break;

                            default: {
                                assert(false);///, "unknown storage operation\n");
                            }
                                break;
                        };

                        return nullptr;
                    }
                };


                using storage_handler_ptr = void *(*)(storage_operation, const any *, any *);

                template<typename T>
                using storage_handler = typename std::conditional<use_internal_storage<T>::value,
                        storage_handler_internal<T>,
                        storage_handler_external<T>>::type;


                storage m_storage;
                storage_handler_ptr m_handler;

            public:

                any() noexcept : m_storage(), m_handler(nullptr) {}

                any(const any &other) : m_handler(nullptr) {
                    if (other.m_handler) {
                        other.m_handler(storage_operation::COPY, &other, this);
                        m_handler = other.m_handler;
                    }
                }

                any(any &&other) noexcept : m_handler(nullptr) {
                    if (other.m_handler) {
                        m_handler = std::move(other.m_handler);
                        other.m_handler(storage_operation::MOVE, &other, this);
                    }
                }

                ~any() { reset(); }

                template<class ValueType>
                any(ValueType &&value,
                    typename std::enable_if<!std::is_same<typename std::decay<ValueType>::type, any>::value>::type * = 0) {
                    using DecayedValueType = type_traits::decay_t <ValueType> ;
                    static_assert(std::is_copy_constructible<DecayedValueType>::value,"ValueType must be copy-constructible");
                    storage_handler<DecayedValueType>::construct(m_storage, std::forward<ValueType>(value));
                    m_handler = &storage_handler<DecayedValueType>::handler_func;
                }

                template<class T, class... Args>
                explicit any(type_traits::in_place_type_t <T>, Args &&... args) {
                    typedef storage_handler <type_traits::decay_t<T>> StorageHandlerT;
                    static_assert(std::is_constructible<T, Args...>::value, "T must be constructible with Args...");
                    StorageHandlerT::construct_inplace(m_storage, std::forward<Args>(args)...);
                    m_handler = &StorageHandlerT::handler_func;
                }

                template<class T, class U, class... Args>
                explicit any(type_traits::in_place_type_t <T>,
                             std::initializer_list<U> il,
                             Args &&... args,
                             typename std::enable_if<std::is_constructible<T, std::initializer_list<U> &, Args...>::value, void>::type * = 0) {
                    typedef storage_handler <type_traits::decay_t<T>> StorageHandlerT;

                    StorageHandlerT::construct_inplace(m_storage, il, std::forward<Args>(args)...);
                    m_handler = &StorageHandlerT::handler_func;
                }

                // 20.7.3.2, assignments
                template<class ValueType>
                any &operator=(ValueType &&value) {
                    static_assert(std::is_copy_constructible <type_traits::decay_t < ValueType >> ::value,"ValueType must be copy-constructible");
                    any(std::forward<ValueType>(value)).swap(*this);
                    return *this;
                }

                any &operator=(const any &other) {
                    any(other).swap(*this);
                    return *this;
                }

                any &operator=(any &&other) noexcept {
                    any(std::move(other)).swap(*this);
                    return *this;
                }

                template<class T, class... Args>
                void emplace(Args &&... args) {
                    typedef storage_handler <type_traits::decay_t<T>> StorageHandlerT;
                    static_assert(std::is_constructible<T, Args...>::value, "T must be constructible with Args...");
                    reset();
                    StorageHandlerT::construct_inplace(m_storage, std::forward<Args>(args)...);
                    m_handler = &StorageHandlerT::handler_func;
                }

                template<class NT, class U, class... Args>
                typename std::enable_if<std::is_constructible<NT, std::initializer_list<U> &, Args...>::value, void>::type
                emplace(std::initializer_list<U> il, Args &&... args) {
                    using StorageHandlerT = storage_handler <type_traits::decay_t<NT>>;

                    reset();
                    StorageHandlerT::construct_inplace(m_storage, il, std::forward<Args>(args)...);
                    m_handler = &StorageHandlerT::handler_func;
                }


                void reset() noexcept {
                    if (m_handler)
                        m_handler(storage_operation::DESTROY, this, nullptr);
                }

                void swap(any &other) noexcept {
                    if (this == &other)
                        return;

                    if (m_handler && other.m_handler) {
                        any tmp;
                        tmp.m_handler = other.m_handler;
                        other.m_handler(storage_operation::MOVE, &other, &tmp);

                        other.m_handler = m_handler;
                        m_handler(storage_operation::MOVE, this, &other);

                        m_handler = tmp.m_handler;
                        tmp.m_handler(storage_operation::MOVE, &tmp, this);
                    } else if (m_handler == nullptr && other.m_handler) {
                        std::swap(m_handler, other.m_handler);
                        m_handler(storage_operation::MOVE, &other, this);
                    } else if (m_handler && other.m_handler == nullptr) {
                        std::swap(m_handler, other.m_handler);
                        other.m_handler(storage_operation::MOVE, this, &other);
                    }
                    //else if (m_handler == nullptr && other.m_handler == nullptr)
                    //{
                    //     // nothing to swap
                    //}
                }

                bool has_value() const noexcept {
                    return m_handler != nullptr;
                }

#if EASTL_RTTI_ENABLED
                inline const std::type_info& type() const noexcept {
                if(m_handler){
                    auto* pTypeInfo = m_handler(storage_operation::TYPE_INFO, this, nullptr);
                    return *static_cast<const std::type_info*>(pTypeInfo);
                } else {
                    return typeid(void);
                }
            }
#endif
            };


            inline void swap(any &rhs, any &lhs) noexcept {
                rhs.swap(lhs);
            }


            template<class ValueType>
            inline ValueType any_cast(const any &operand) {
                static_assert(std::is_reference<ValueType>::value || std::is_copy_constructible<ValueType>::value,"ValueType must be a reference or copy constructible");
                auto *p = any_cast<typename std::add_const<typename std::remove_reference<ValueType>::type>::type>(&operand);

                if (p == nullptr)
                    Internal::DoBadAnyCast();

                return *p;
            }

            template<class ValueType>
            inline ValueType any_cast(any &operand) {
                static_assert(std::is_reference<ValueType>::value || std::is_copy_constructible<ValueType>::value,"ValueType must be a reference or copy constructible");
                auto *p = any_cast<typename std::remove_reference<ValueType>::type>(&operand);

                if (p == nullptr)
                    Internal::DoBadAnyCast();

                return *p;
            }

            template<class ValueType>
            inline ValueType any_cast(any &&operand) {
                static_assert(std::is_reference<ValueType>::value || std::is_copy_constructible<ValueType>::value,"ValueType must be a reference or copy constructible");
                auto *p = any_cast<typename std::remove_reference<ValueType>::type>(&operand);

                if (p == nullptr)
                    Internal::DoBadAnyCast();

                return *p;
            }

            template<class ValueType>
            inline const ValueType *any_cast(const any *pAny) noexcept {
                return (pAny && pAny->m_handler
#if EASTL_RTTI_ENABLED
                && pAny->type() == typeid(typename remove_reference<ValueType>::type)
#endif
                ) ?
                static_cast<const ValueType *>(pAny->m_handler(any::storage_operation::GET, pAny,nullptr)) :nullptr;
            }

            template<class ValueType>
            inline ValueType *any_cast(any *pAny) noexcept {
                return (pAny && pAny->m_handler

#if EASTL_RTTI_ENABLED
                && pAny->type() == typeid(typename remove_reference<ValueType>::type)
#endif
                ) ?
                static_cast<ValueType *>(pAny->m_handler(any::storage_operation::GET, pAny,nullptr)) : nullptr;
            }

//Unsafe operations - use with caution
            template<class ValueType>
            inline const ValueType *unsafe_any_cast(const any *pAny) noexcept {
                return unsafe_any_cast<ValueType>(const_cast<any *>(pAny));
            }

            template<class ValueType>
            inline ValueType *unsafe_any_cast(any *pAny) noexcept {
                return static_cast<ValueType *>(pAny->m_handler(any::storage_operation::GET, pAny, nullptr));
            }

            template<class T, class... Args>
            inline any make_any(Args &&... args) {
                return any(type_traits::in_place<T>, std::forward<Args>(args)...);
            }

            template<class T, class U, class... Args>
            inline any make_any(std::initializer_list<U> il, Args &&... args) {
                return any(type_traits::in_place<T>, il, std::forward<Args>(args)...);
            }

}}