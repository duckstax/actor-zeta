#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <utility>

namespace actor_zeta {
    namespace network {

        struct abstract_read_handler {
            virtual  ~ abstract_read_handler() = default;

            virtual void run(const char *buff, ssize_t len) = 0;
        };

        struct abstract_write_handler {
            virtual ~abstract_write_handler() = default;

            virtual void run(const std::string &) = 0;

            virtual std::string id() = 0;
        };

        class write_handler {
        public:
            write_handler() = default;

            write_handler(const write_handler &) = default;

            write_handler &operator=(const write_handler &) = delete;

            write_handler(write_handler &&) = default;

            write_handler &operator=(write_handler &&) = default;

            ~write_handler() = default;

            explicit write_handler(abstract_write_handler *ptr) : abstract_write_handler_ptr(ptr) { }

            void operator()(const std::string &buff) {
                abstract_write_handler_ptr->run(buff);
            }

            std::string id() {
                return abstract_write_handler_ptr->id();
            }

        private:
            std::shared_ptr<abstract_write_handler> abstract_write_handler_ptr;
        };

        class read_handler {
        public:
            read_handler() = default;

            read_handler(const read_handler &) = default;

            read_handler &operator=(const read_handler &) = delete;

            read_handler(read_handler &&) = default;

            read_handler &operator=(read_handler &&) = default;

            ~read_handler() = default;

            explicit read_handler(abstract_read_handler *ptr) : abstract_read_handler_ptr(ptr) { }

            void operator()(const char *buff, ssize_t len) {
                abstract_read_handler_ptr->run(buff, len);
            }

        private:
            std::shared_ptr<abstract_read_handler> abstract_read_handler_ptr;
        };
    }
}

#endif //CONNECTION_HPP
