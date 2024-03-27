#pragma once

#include <cassert>

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include <actor-zeta/base/behavior.hpp>

namespace actor_zeta { namespace detail {

    class hfsm {
    public:
        hfsm(const hfsm&) = delete;
        hfsm& operator=(const hfsm&) = delete;
        hfsm() = delete;

        hfsm(actor_zeta::pmr::memory_resource* ) {}

        void pop_back() {
            assert(!elements_.empty());
            erased_elements_.push_back(std::move(elements_.back()));
            elements_.pop_back();
        }

        void clear() {
            if (!elements_.empty()) {
                if (erased_elements_.empty()) {
                    elements_.swap(erased_elements_);
                } else {
                    std::move(elements_.begin(), elements_.end(),
                              std::back_inserter(erased_elements_));
                    elements_.clear();
                }
            }
        }

        bool empty() const {
            return elements_.empty();
        }

        base::behavior_t& back() {
            assert(!empty());
            return elements_.back();
        }

        void push_back(base::behavior_t&& what) {
            elements_.emplace_back(std::move(what));
        }

        template<class... Ts>
        void emplace_back(Ts&&... xs) {
            elements_.emplace_back(std::forward<Ts>(xs)...);
        }

        void cleanup() {
            erased_elements_.clear();
        }

    private:
        std::vector<base::behavior_t> elements_;
        std::vector<base::behavior_t> erased_elements_;
    };

}} // namespace actor_zeta::detail
