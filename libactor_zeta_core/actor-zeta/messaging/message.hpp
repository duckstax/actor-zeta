#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "actor-zeta/actor/actor_address.hpp"
#include "message_priorities.hpp"
#include "memory"

namespace actor_zeta {
    namespace messaging {

        class message {
        public:

            message() = delete;

            message(const message &) = delete;

            message &operator=(const message &) = delete;

            message(message &&other) {
                    std::swap(data, other.data);
            }

            message &operator=(message &&other) {
                if (this != &other) {
                    std::swap(data, other.data);
                }
                return *this;
            };

            //TODO:не понятно пока как подержать
            //template<typename ValueType> any(ValueType &&);
            //template<typename ValueType> const ValueType * any_cast(const any *);
            //template<typename ValueType> ValueType * any_cast(any *);

            template<typename T>
            message(const std::string &type, const T &t):
                    data(new message_data(type, new contaner<T>(t), message_priorities::normal, false)) {}

            template<typename T>
            message(const std::string &type, const T &t, const actor_address &aa):
                    data(new message_data(type, new contaner<T>(t), message_priorities::normal, true, aa)) {}

            template<typename T>
            message(const std::string &type, const T &t, message_priorities p):
                    data(new message_data(type, new contaner<T>(t), p, false)) {}

            template<typename T>
            message(const std::string &type, const T &t, message_priorities p, const actor_address &aa)
                    : data(new message_data(type, new contaner<T>(t), p, true, aa)) {}

            template<typename T>
            T get() const {
                if (static_cast<bool>(data.get())) {
                    return static_cast<contaner <T> *>(data.get()->content.get())->data;
                }
                else {
                    return T();//TODO:  Жесть
                }
            }

            operator bool() const {
                return static_cast<bool>(data.get());
            }

            std::string type() const {
                return data->type_message;
            }

            const actor_address &return_address() const {
                return data->address;
            }

            bool is_callback() const {
                return data->callback;
            }

            const message_priorities get_prioritie() const {
                return data->prioritie;
            }

            ~message() {}

        private:
            struct base_contaner {
                virtual ~base_contaner() {}
            };

            template<typename T>
            struct contaner : base_contaner {
                T data;

                contaner(const T &data) : data(data) {}

                contaner &operator=(const contaner &) = delete;
            };

            struct message_data {
                message_data(const message_data &) = delete;

                message_data &operator=(const message_data &) = delete;

                message_data() = delete;

                ~message_data() = default;

                std::unique_ptr<base_contaner> content;
                bool callback;
                std::string type_message;
                actor_address address;
                message_priorities prioritie;

                message_data(
                        const std::string &type_message,
                        base_contaner *ptr,
                        message_priorities prioritie,
                        bool callback,
                        const actor_address &address
                ) : content(ptr),
                    callback(callback),
                    type_message(type_message),
                    address(address),
                    prioritie(prioritie) {}

                message_data(
                        const std::string &type_message,
                        base_contaner *ptr,
                        message_priorities prioritie,
                        bool callback
                ) : content(ptr),
                    callback(callback),
                    type_message(type_message),
                    prioritie(prioritie) {}
            };

            std::unique_ptr<message_data> data;
        };

        template<typename V>
        inline actor_zeta::messaging::message make_message(const std::string &command, const V &v) {
            return actor_zeta::messaging::message(command, v);
        }

        template<typename V>
        inline actor_zeta::messaging::message
        make_message(actor_address address, const std::string &command, const V &v) {
            return actor_zeta::messaging::message(command, v, address);
        }
    }
}
#endif