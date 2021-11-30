#pragma once

#include <iostream>
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
            void SetUp(const ::benchmark::State& state) {
                for (int i = 0; i < state.range(0); ++i) {
                    name_ += std::to_string(i % 10);
                }
            }

            void TearDown(const ::benchmark::State& state) {
                name_.clear();
            }

            std::string name_;
        };

    } // namespace by_name

    namespace by_args {

        namespace trivial_args {

            template<typename... CustomArgs>
            struct construct {};

            template<typename T>
            struct construct<T> {
                static T get(int value) {
                    return T(value);
                }
            };

            template<class P, typename... CustomArgs>
            class fixture_t : public benchmark::Fixture {
            public:
                void SetUp(const ::benchmark::State& state) {
                    arguments_ = std::make_tuple(std::forward<CustomArgs>(construct<CustomArgs>::get(state.range(0)))...);
                    name_ = "name_";
                }

                void TearDown(const ::benchmark::State& state) {
                    name_.clear();
                }

                std::string name_;
                std::tuple<CustomArgs...> arguments_;
                static constexpr size_t counter_ = sizeof...(CustomArgs);
            };

        } // namespace trivial_args

#define DEFINE_TYPE_SEC(append_to_type_seq, revert_type_seq, type_name) \
    template<typename, typename>                                        \
    struct append_to_type_seq {};                                       \
    template<typename T, typename... Ts>                                \
    struct append_to_type_seq<T, std::tuple<Ts...>> {                   \
        using type = std::tuple<Ts..., type_name<T>>;                   \
    };                                                                  \
    template<typename... Ts>                                            \
    struct revert_type_seq {                                            \
        using type = std::tuple<>;                                      \
    };                                                                  \
    template<typename T, typename... Ts>                                \
    struct revert_type_seq<T, Ts...> {                                  \
        using type = typename append_to_type_seq<                       \
            T,                                                          \
            typename revert_type_seq<Ts...>::type>::type;               \
    }

        namespace smart_pointer_args {

            template<typename... CustomArgs>
            struct construct {};

            template<typename T>
            struct construct<T> {
                static std::shared_ptr<T> get(int value) {
                    return std::shared_ptr<T>(new T(value));
                }
            };

            DEFINE_TYPE_SEC(append_to_type_seq, revert_type_seq, std::shared_ptr);

            template<class P, typename... CustomArgs>
            class fixture_t : public benchmark::Fixture {
            public:
                void SetUp(const ::benchmark::State& state) {
                    arguments_ = std::make_tuple((construct<CustomArgs>::get(state.range(0)))...);
                    name_ = "name_";
                }

                void TearDown(const ::benchmark::State& state) {
                    name_.clear();
                }

                std::string name_;
                typename revert_type_seq<CustomArgs...>::type arguments_;
                static constexpr size_t counter_ = sizeof...(CustomArgs);
            };

        } // namespace smart_pointer_args

        namespace container_args {

            template<typename... CustomArgs>
            struct construct_vec {};

            template<typename... CustomArgs>
            struct construct_map {};

            template<typename... CustomArgs>
            struct construct_set {};

            template<typename T>
            struct construct_vec<T> {
                static std::vector<T> get(int value) {
                    std::vector<T> vec;
                    for (auto i = 0; i < value; ++i) {
                        vec.push_back(static_cast<T>(value));
                    }
                    return std::move(vec);
                }
            };

            template<typename T>
            struct construct_map<T> {
                static std::map<T, T> get(int value) {
                    std::map<T, T> map;
                    for (auto i = 0; i < value; ++i) {
                        map[static_cast<T>(value)] = static_cast<T>(value);
                    }
                    return std::move(map);
                }
            };

            template<typename T>
            struct construct_set<T> {
                static std::set<T> get(int value) {
                    std::set<T> set;
                    for (auto i = 0; i < value; ++i) {
                        set.emplace(static_cast<T>(value));
                    }
                    return set;
                }
            };

#define DEFINE_FIXTURE_CLASS(class_name, construct_name, revert_type_seq)                       \
    template<class P, typename... CustomArgs>                                                   \
    class class_name : public benchmark::Fixture {                                              \
    public:                                                                                     \
        void SetUp(const ::benchmark::State& state) {                                           \
            arguments_ = std::make_tuple((construct_name<CustomArgs>::get(state.range(0)))...); \
            name_ = "name_";                                                                    \
        }                                                                                       \
        void TearDown(const ::benchmark::State& state) {                                        \
            name_.clear();                                                                      \
        }                                                                                       \
        std::string name_;                                                                      \
        typename revert_type_seq<CustomArgs...>::type arguments_;                               \
        static constexpr size_t counter_ = sizeof...(CustomArgs);                               \
    }

            DEFINE_TYPE_SEC(append_to_type_seq_vec, revert_type_seq_vec, std::vector);
            //DEFINE_TYPE_SEC(append_to_type_seq_map, revert_type_seq_map, std::map);
            DEFINE_TYPE_SEC(append_to_type_seq_set, revert_type_seq_set, std::set);

            DEFINE_FIXTURE_CLASS(fixture_vec_t, construct_vec, revert_type_seq_vec);
            //DEFINE_FIXTURE_CLASS(fixture_map_t, construct_map, revert_type_seq_map);
            DEFINE_FIXTURE_CLASS(fixture_set_t, construct_set, revert_type_seq_set);

        } // namespace container_args

    } // namespace by_args

} // namespace benchmark_messages
