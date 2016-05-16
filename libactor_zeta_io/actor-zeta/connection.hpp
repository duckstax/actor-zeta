#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <utility>

namespace actor_zeta {
    namespace network {

        struct abstract_read_handler {
            ~ abstract_read_handler() = default;

            virtual void run(const char *buff, ssize_t len) = 0;
        };

        struct abstract_write_handler {
            ~abstract_write_handler() = default;

            virtual void run(const std::string &) = 0;
        };

        class write_handler {
        public:
            write_handler() = default;

            write_handler(const write_handler &) = default;

            write_handler &operator=(const write_handler &) = delete;

            write_handler(write_handler &&) = default;

            write_handler &operator=(write_handler &&) = default;

            ~write_handler()= default;

            write_handler(abstract_write_handler *ptr) : abstract_write_handler_ptr(ptr) { }

            void operator()(const std::string &buff) {
                abstract_write_handler_ptr->run(buff);
            }

        private:
            std::shared_ptr<abstract_write_handler> abstract_write_handler_ptr;
        };

        class proxy_handler {
        public:
            proxy_handler() = default;

            proxy_handler(const proxy_handler &) = default;

            proxy_handler &operator=(const proxy_handler &) = delete;

            proxy_handler(proxy_handler &&) = default;

            proxy_handler &operator=(proxy_handler &&) = default;

            ~proxy_handler()= default;

            proxy_handler(abstract_read_handler *ptr) : abstract_read_handler_ptr(ptr) { }

            void operator()(const char *buff, ssize_t len) {
                abstract_read_handler_ptr->run(buff, len);
            }

        private:
            std::shared_ptr<abstract_read_handler> abstract_read_handler_ptr;
        };
    }
}

#endif //CONNECTION_HPP
