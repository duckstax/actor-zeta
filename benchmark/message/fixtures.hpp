#pragma once

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include <benchmark/benchmark.h>

namespace benchmark_messages {

    namespace by_name {

        template<typename P>
        class fixture_t : public benchmark::Fixture {
        public:
            virtual void SetUp(const ::benchmark::State& state) final {
                for (int i = 0; i < state.range(0); ++i) {
                    name_ += std::to_string(i % 10);
                }
            }

            virtual void SetUp(::benchmark::State& state) final {
                SetUp(state);
            }

            virtual void TearDown(__attribute__((unused)) const ::benchmark::State& state) final {
                name_.clear();
            }

            virtual void TearDown(::benchmark::State& state) final {
                TearDown(state);
            }

            std::string name_;
        };

    } // namespace by_name

#define DEFINE_FIXTURE_CLASS_1(class_name, construct_name)                                                                                    \
    template<class P, typename... CustomArgs>                                                                                                 \
    class class_name : public ::benchmark::Fixture {                                                                                          \
    public:                                                                                                                                   \
        virtual void SetUp(const ::benchmark::State& state) final {                                                                           \
            arguments_ = std::make_tuple(std::forward<CustomArgs>(construct_name<CustomArgs>::get(static_cast<int64_t>(state.range(0))))...); \
            name_ = "name_";                                                                                                                  \
        }                                                                                                                                     \
        virtual void SetUp(::benchmark::State& state) final {                                                                                 \
            SetUp(state);                                                                                                                     \
        }                                                                                                                                     \
        virtual void TearDown(__attribute__((unused)) const ::benchmark::State& state) final {                                                \
            name_.clear();                                                                                                                    \
        }                                                                                                                                     \
        virtual void TearDown(::benchmark::State& state) final {                                                                              \
            TearDown(state);                                                                                                                  \
        }                                                                                                                                     \
        std::string name_;                                                                                                                    \
        std::tuple<CustomArgs...> arguments_;                                                                                                 \
        static constexpr size_t counter_ = sizeof...(CustomArgs);                                                                             \
    }

    namespace by_args {

        namespace trivial_args {

            template<typename... CustomArgs>
            struct construct {};

            template<typename T>
            struct construct<T> {
                static T get(int64_t value) {
                    return T(value);
                }
            };

            DEFINE_FIXTURE_CLASS_1(fixture_t, construct);

        } // namespace trivial_args

#define DEFINE_APPEND_TO_TYPE_SEC_1(append_to_type_seq, type_name) \
    template<typename, typename>                                   \
    struct append_to_type_seq {};                                  \
    template<typename T, typename... Ts>                           \
    struct append_to_type_seq<T, std::tuple<Ts...>> {              \
        using type = std::tuple<Ts..., type_name<T>>;              \
    }

#define DEFINE_APPEND_TO_TYPE_SEC_2(append_to_type_seq, type_name) \
    template<typename, typename>                                   \
    struct append_to_type_seq {};                                  \
    template<typename T, typename... Ts>                           \
    struct append_to_type_seq<T, std::tuple<Ts...>> {              \
        using type = std::tuple<Ts..., type_name<T, T>>;           \
    }

#define DEFINE_REVERT_TYPE_SEC(append_to_type_seq, revert_type_seq) \
    template<typename... Ts>                                        \
    struct revert_type_seq {                                        \
        using type = std::tuple<>;                                  \
    };                                                              \
    template<typename T, typename... Ts>                            \
    struct revert_type_seq<T, Ts...> {                              \
        using type = typename append_to_type_seq<                   \
            T,                                                      \
            typename revert_type_seq<Ts...>::type>::type;           \
    }

#define DEFINE_FIXTURE_CLASS_2(class_name, construct_name, revert_type_seq)                                           \
    template<class P, typename... CustomArgs>                                                                         \
    class class_name : public ::benchmark::Fixture {                                                                  \
    public:                                                                                                           \
        virtual void SetUp(const ::benchmark::State& state) final {                                                   \
            arguments_ = std::make_tuple((construct_name<CustomArgs>::get(static_cast<int64_t>(state.range(0))))...); \
            name_ = "name_";                                                                                          \
        }                                                                                                             \
        virtual void SetUp(::benchmark::State& state) final {                                                         \
            SetUp(state);                                                                                             \
        }                                                                                                             \
        virtual void TearDown(__attribute__((unused)) const ::benchmark::State& state) final {                        \
            name_.clear();                                                                                            \
        }                                                                                                             \
        virtual void TearDown(::benchmark::State& state) final {                                                      \
            TearDown(state);                                                                                          \
        }                                                                                                             \
        std::string name_;                                                                                            \
        typename revert_type_seq<CustomArgs...>::type arguments_;                                                     \
        static constexpr size_t counter_ = sizeof...(CustomArgs);                                                     \
    }

        namespace smart_pointer_args {

            template<typename... CustomArgs>
            struct construct {};

            template<typename T>
            struct construct<T> {
                static std::shared_ptr<T> get(int64_t value) {
                    return std::shared_ptr<T>(new T(static_cast<T>(value)));
                }
            };

            DEFINE_APPEND_TO_TYPE_SEC_1(append_to_type_seq, std::shared_ptr);
            DEFINE_REVERT_TYPE_SEC(append_to_type_seq, revert_type_seq);

            DEFINE_FIXTURE_CLASS_2(fixture_t, construct, revert_type_seq);

        } // namespace smart_pointer_args

        namespace container_args {

            template<typename... CustomArgs>
            struct construct_vec {};

            template<typename... CustomArgs>
            struct construct_list {};

            template<typename... CustomArgs>
            struct construct_map {};

            template<typename... CustomArgs>
            struct construct_set {};

            template<typename T>
            struct construct_vec<T> {
                static std::vector<T> get(int64_t value) {
                    std::vector<T> vec;
                    for (auto i = 0; i < value; ++i) {
                        vec.push_back(static_cast<T>(value));
                    }
                    return vec;
                }
            };

            template<typename T>
            struct construct_list<T> {
                static std::list<T> get(int64_t value) {
                    std::list<T> list;
                    for (auto i = 0; i < value; ++i) {
                        list.emplace_back(static_cast<T>(value));
                    }
                    return list;
                }
            };

            template<typename T>
            struct construct_map<T> {
                static std::map<T, T> get(int64_t value) {
                    std::map<T, T> map;
                    for (auto i = 0; i < value; ++i) {
                        map[static_cast<T>(value)] = static_cast<T>(value);
                    }
                    return map;
                }
            };

            template<typename T>
            struct construct_set<T> {
                static std::set<T> get(int64_t value) {
                    std::set<T> set;
                    for (auto i = 0; i < value; ++i) {
                        set.emplace(static_cast<T>(value));
                    }
                    return set;
                }
            };

            DEFINE_APPEND_TO_TYPE_SEC_1(append_to_type_seq_vec, std::vector);
            DEFINE_REVERT_TYPE_SEC(append_to_type_seq_vec, revert_type_seq_vec);

            DEFINE_APPEND_TO_TYPE_SEC_1(append_to_type_seq_list, std::list);
            DEFINE_REVERT_TYPE_SEC(append_to_type_seq_list, revert_type_seq_list);

            DEFINE_APPEND_TO_TYPE_SEC_2(append_to_type_seq_map, std::map);
            DEFINE_REVERT_TYPE_SEC(append_to_type_seq_map, revert_type_seq_map);

            DEFINE_APPEND_TO_TYPE_SEC_1(append_to_type_seq_set, std::set);
            DEFINE_REVERT_TYPE_SEC(append_to_type_seq_set, revert_type_seq_set);

            DEFINE_FIXTURE_CLASS_2(fixture_vec_t, construct_vec, revert_type_seq_vec);
            DEFINE_FIXTURE_CLASS_2(fixture_list_t, construct_list, revert_type_seq_list);
            DEFINE_FIXTURE_CLASS_2(fixture_map_t, construct_map, revert_type_seq_map);
            DEFINE_FIXTURE_CLASS_2(fixture_set_t, construct_set, revert_type_seq_set);

        } // namespace container_args

        namespace custom_args {

            struct custom_1_t {
                custom_1_t(int64_t value) {
                    std::string tmp;
                    for (int64_t i = 0; i < value; ++i) {
                        tmp += std::to_string(i % 10);
                        map_[i] = tmp;
                        vec_.push_back(tmp);
                    }
                }
                custom_1_t() = default;
                custom_1_t(custom_1_t&) = default;
                custom_1_t(const custom_1_t&) = default;
                custom_1_t(custom_1_t&&) = default;
                ~custom_1_t() = default;

                custom_1_t& operator=(custom_1_t&) = default;
                custom_1_t& operator=(const custom_1_t&) = default;
                custom_1_t& operator=(custom_1_t&&) = default;

                std::map<int64_t, std::string> map_;
                std::vector<std::string> vec_;
            };

            template<typename... CustomArgs>
            struct construct {};

            template<typename T>
            struct construct<T> {
                static T get(int64_t value) {
                    return T(value);
                }
            };

            DEFINE_APPEND_TO_TYPE_SEC_1(append_to_type_seq, std::shared_ptr);
            DEFINE_REVERT_TYPE_SEC(append_to_type_seq, revert_type_seq);

            DEFINE_FIXTURE_CLASS_1(fixture_t, construct);

        } // namespace custom_args

    } // namespace by_args

} // namespace benchmark_messages
