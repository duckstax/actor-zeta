#pragma once

#include <vector>
#include <algorithm>

namespace actor_zeta { namespace  detail {
///
/// @brief
///
        class node final {
        public:
            using vertex_id      = std::size_t;
            using list_vertices  = std::vector<vertex_id>;
            using iterator       = list_vertices::iterator;
            using const_iterator = list_vertices::const_iterator;

            struct cmp {
                bool operator()(const node& p, vertex_id s) const { return p.id() < s; }

                bool operator()(vertex_id s, const node& p) const { return s < p.id(); }
            };

            node() = delete;

            node(class node &) = default;

            node &operator=(class node &) = default;

            node(node &&) = default;

            node &operator=(node &&) = default;

            ~node() = default;

            explicit node(vertex_id id) : id_(id) {}

            bool operator<(const node &other) const {
                return this->id() < other.id();
            }

            bool operator<(const vertex_id &other) const {
                return this->id() < other;
            }

            bool operator>(const vertex_id &other) const {
                return this->id() > other;
            }

            bool operator>(const node &other) const {
                return this->id() > other.id();
            }

            std::size_t size() const {
                return list_vertex.size();
            }

            auto begin() -> iterator {
                return list_vertex.begin();
            }

            auto end() -> iterator {
                return list_vertex.end();
            }

            auto begin() const -> const_iterator {
                return list_vertex.begin();
            }

            auto end() const -> const_iterator {
                return list_vertex.end();
            }

            void add(vertex_id id) {
                if (!(std::binary_search(list_vertex.begin(), list_vertex.end(), id))) {
                    list_vertex.insert(
                            std::upper_bound(
                                    list_vertex.begin(),
                                    list_vertex.end(),
                                    id
                            ),
                            id
                    );
                }
            }

            vertex_id id() const {
                return id_;
            }

        private:
            vertex_id id_;
            list_vertices list_vertex;
        };

///
/// @brief
/// @tparam Node
///
        template<class Node>
        class stored_vertex final {
        public:
            using vertex_id=typename Node::vertex_id;
            using cmp_t=typename Node::cmp;

            stored_vertex() = default;

            stored_vertex(const stored_vertex &) = default;

            stored_vertex &operator=(const stored_vertex &) = default;

            stored_vertex(stored_vertex &&) = default;

            stored_vertex &operator=(stored_vertex &&) = default;

            ~stored_vertex() = default;

            void add_vertex(vertex_id id) {
                if (!std::binary_search(ddd.begin(), ddd.end(), id, cmp_t())) {
                    ddd.insert(
                            std::upper_bound(
                                    ddd.begin(),
                                    ddd.end(),
                                    id,
                                    cmp_t()
                            ),
                            Node(id)
                    );
                }
            }

            Node &lookup(vertex_id id) {
                return ddd.at(id);
            }

            void add_edge(vertex_id id_1, vertex_id id_2) {

                if (!std::binary_search(ddd.begin(), ddd.end(), id_1, cmp_t())) {
                    auto it = ddd.insert(
                            std::upper_bound(
                                    ddd.begin(),
                                    ddd.end(),
                                    id_1,
                                    cmp_t()
                            ),
                            Node(id_1)
                    );
                    it->add(id_2);
                } else {
                    auto it = std::lower_bound(
                            ddd.begin(),
                            ddd.end(),
                            id_1
                    );
                    if (it != ddd.end()) {
                        it->add(id_2);
                    }
                }

                if (!std::binary_search(ddd.begin(), ddd.end(), id_2, cmp_t())) {
                    ddd.insert(
                            std::upper_bound(
                                    ddd.begin(),
                                    ddd.end(),
                                    id_2,
                                    cmp_t()
                            ),
                            Node(id_2)
                    );
                }

            }

        private:

            std::vector<Node> ddd;
        };

///
/// @brief
///
        template<template<class> class Store, class Node=node>
        class adjacency_list final {
        public:
            adjacency_list() = default;

            adjacency_list(const adjacency_list &) = delete;

            adjacency_list &operator=(const adjacency_list &) = delete;

            adjacency_list(adjacency_list &&) = delete;

            adjacency_list &operator=(adjacency_list &&) = delete;

            ~adjacency_list() = default;

            template<typename vertex_id>
            void add_vertex(vertex_id id) {
                graph_.add_vertex(id);
            }

            template<typename vertex_id>
            void add_edge(vertex_id id_1, vertex_id id_2) {
                graph_.add_edge(id_1, id_2);
            }

            template<typename vertex_id>
            auto finding_adjacency(vertex_id id) -> std::vector<vertex_id> {
                auto node_ = graph_.lookup(id);
                std::vector<vertex_id> tmp;
                tmp.reserve(node_.size());
                for (auto &i:node_) {
                    tmp.emplace_back(i);
                }
                return tmp;
            }

        private:
            Store<Node> graph_;
        };

}}
