#pragma once

#include <deque>
#include <queue>
#include <thread>
#include <list>
#include <cassert>
#include <unordered_map>
#include <utility>
#include <atomic>
#include <functional>

#include <actor-zeta/network/multiplexer.hpp>

namespace actor_zeta { namespace network {

        enum class client_state {
            close,
            open,
            accept,
            connect,
            write,
            read,
            disconnect
        };


        struct query_raw_t final {
            query_raw_t()= default;
            query_raw_t(query_raw_t&&)= default;
            query_raw_t&operator=(query_raw_t&&)= default;
            query_raw_t(const query_raw_t&)= default;
            query_raw_t&operator=(const query_raw_t&)= default;
            ~query_raw_t()= default;
            actor_zeta::network::connection_identifying id;
            buffer raw;
        };

        struct fake_state final {
            fake_state(fake_state&&)= default;
            fake_state&operator=(fake_state&&)= default;
            ~fake_state() = default;
            fake_state():
                    waite_time(0){

            }

            fake_state(client_state next_state) :
                    state(next_state) ,
                    waite_time(0) {}


            fake_state(const buffer &input, client_state next_state) :
                    buffer_(input),
                    state(next_state) ,
                    waite_time(0) {}

            template<class F>
            fake_state(F && checker, client_state next_state, size_t waite_time) :
                    checker_(std::forward<F>(checker)),
                    state(next_state),
                    waite_time(waite_time) {}

            std::function<bool(const buffer &)> checker_;
            buffer buffer_;
            client_state state;
            std::size_t waite_time;
        };

        struct fake_socket final {
            fake_socket()                        = default;
            fake_socket(fake_socket&&)           = default;
            fake_socket&operator=(fake_socket&&) = default;


            template <class ...Args>
            fake_socket& add(Args&&... args){
                scenario.emplace_back(std::forward<Args>(args)...);
                return *this;
            }


            buffer read() {
                assert(!scenario.empty());
                current_satet = std::move(scenario.front());
                scenario.pop_front();
                assert(current_satet.state == client_state::read);
                return current_satet.buffer_;
            }


            void close() {
                assert(!scenario.empty());
                current_satet=std::move(scenario.front());
                scenario.pop_front();
                assert(current_satet.state == client_state::close);
            }

            void write(const buffer& b) {

                assert(!scenario.empty());
                current_satet=std::move(scenario.front());
                scenario.pop_front();
                assert(current_satet.state == client_state::write);
                bool is_equality = (current_satet.checker_(b));
                ///TODO: see hack
                if(is_equality){
                    assert(is_equality);
                }
            }

            std::size_t wait_size() {
                return current_satet.waite_time;
            }

        private:
            fake_state current_satet;
            std::deque<fake_state> scenario;
        };


        template<typename Socket>
        class connection final {
        public:
            connection(connection&&) = default;
            connection&operator=(connection&&) = default;
            connection() = default;
            using socket_t = Socket;

            connection(socket_t &&socket, actor::actor_address &&address) :
                    socket_(std::forward<Socket>(socket)),
                    address_(std::move(address)) {

            }

            ~connection() = default;

            socket_t& socket() {
                return socket_;
            }

            socket_t& socket() const {
                return socket_;
            }


            actor::actor_address address() const {
                return address_;
            }

        private:
            socket_t socket_;
            actor::actor_address address_;
        };


        class fake_multiplexer final : public multiplexer {
        public:
            fake_multiplexer();

            ~fake_multiplexer() override;

            fake_socket& add_scenario(const std::string &host, uint16_t port);

            std::size_t start() override;

            void new_tcp_listener(const std::string &host, uint16_t port, actor::actor_address ) override;

            void new_tcp_connection(const std::string &host, uint16_t port, actor::actor_address)  override;

            void close(const connection_identifying &) override;

            void write(const connection_identifying &, const buffer &) override;

        private:
            std::atomic_bool enabled;
            std::deque<std::function<void()>> tasks;
            std::unordered_map<connection_identifying, connection<fake_socket>> sockets;
            std::unordered_map<connection_identifying, fake_socket> scenario;
        };

    }
}
