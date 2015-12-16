#ifndef MAILBOX_HPP
#define MAILBOX_HPP

#include <vector>

namespace actor_model {
    namespace messaging {

        template<class T>
        struct mail_box {
            mail_box() { }

            mail_box(const mail_box &) = delete;

            mail_box &operator=(const mail_box &) = delete;

            virtual bool put(T &&) = 0;

            virtual T get() = 0;

            virtual std::vector<T> getAll() = 0;

            virtual size_t size() = 0;

            virtual bool empty() = 0;

            virtual ~mail_box() { };
        };
    }
}
#endif