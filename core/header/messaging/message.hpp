#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "actor/actor_address.hpp"
#include "message_priorities.hpp"
#include "intrusive_ptr.hpp"

namespace actor_model {
    namespace messaging {

        class message {
        public:

            message() = delete;

            message(const message &) = delete;

            message &operator=(const message &) = delete;

            message(message &&other) {
                std::swap(content, other.content);
                other.content = nullptr;
                std::swap(typeMessage, other.typeMessage);
                std::swap(address, other.address);
                std::swap(callback, other.callback);
                std::swap(prioritie, other.prioritie);
            }

            message &operator=(message &&other) {
                if (this != &other) {
                    std::swap(content, other.content);
                    other.content = nullptr;
                    std::swap(typeMessage, other.typeMessage);
                    std::swap(address, other.address);
                    std::swap(callback, other.callback);
                    std::swap(prioritie, other.prioritie);
                }
                return *this;
            };

            //template<typename ValueType> any(ValueType &&); TODO:не понятно пока как подержать
            template<typename T>
            message(const std::string &type, const T &t)
                    : typeMessage(type), content(new contaner<T>(t)), prioritie(message_priorities::normal),
                      callback(false) { }


            template<typename T>
            message(actor_address aa, const std::string &type, const T &t)
                    : address(aa), typeMessage(type), content(new contaner<T>(t)),
                      prioritie(message_priorities::normal),
                      callback(true) { }

            template<typename T>
            message(message_priorities p, const std::string &type, const T &t)
                    : prioritie(p), typeMessage(type), content(new contaner<T>(t)),
                      callback(false) { }

            template<typename T>
            message(actor_address aa, message_priorities p, const std::string &type, const T &t)
                    : address(aa), prioritie(p), typeMessage(type), content(new contaner<T>(t)),
                      callback(true) { }

            /*
            template<typename ValueType> const ValueType * any_cast(const any *);
            template<typename ValueType> ValueType * any_cast(any *);
            */

            template<typename T>
            T get() const {
                if (static_cast<bool>(content.get())) {
                    return static_cast<contaner <T> *>(content.get())->data;
                }
                else {
                    return T();//TODO:  Жесть
                }
            }

            operator bool() const {
                return static_cast<bool>(content.get());
            }

            std::string type() const {
                return typeMessage;
            }

            actor_address from_whom() const {
                return address;
            }

            bool is_callback() const {
                return callback;
            }

            const message_priorities getPrioritie() const {
                return prioritie;
            }

            ~message() { }

        private:
            struct base_contaner : public ref_counted {
                virtual ~base_contaner() { }
            };

            template<typename T>
            struct contaner : base_contaner {
                T data;

                contaner(const T &data) : data(data) { }

                contaner &operator=(const contaner &) = delete;
            };

            intrusive_ptr<base_contaner> content;
            bool callback;
            std::string typeMessage;
            actor_address address;
            message_priorities prioritie;
        };

        template<typename V>
        inline actor_model::messaging::message make_message(const std::string &command, const V &v) {
            return actor_model::messaging::message(command, v);
        }
    }
}
#endif