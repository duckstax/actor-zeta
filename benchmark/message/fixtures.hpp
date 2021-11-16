#pragma once

#include <iostream>
#include <map>
#include <memory>
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

        namespace smart_pointer_args {

            template<typename... CustomArgs>
            struct construct {};

            template<typename T>
            struct construct<T> {
                static std::shared_ptr<T> get(int value) {
                    return std::shared_ptr<T>(new T(value));
                }
            };

            template<typename, typename>
            struct append_to_type_seq {};

            template<typename T, typename... Ts>
            struct append_to_type_seq<T, std::tuple<Ts...>> {
                using type = std::tuple<Ts..., std::shared_ptr<T>>;
            };

            template<typename... Ts>
            struct revert_type_seq {
                using type = std::tuple<>;
            };

            template<typename T, typename... Ts>
            struct revert_type_seq<T, Ts...> {
                using type = typename append_to_type_seq<
                    T,
                    typename revert_type_seq<Ts...>::type>::type;
            };

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

    } // namespace by_args

} // namespace benchmark_messages
