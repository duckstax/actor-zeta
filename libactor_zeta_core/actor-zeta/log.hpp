#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "actor-zeta/actor/local_actor.hpp"
#include "actor-zeta/messaging/message.hpp"
#include "forwards.hpp"

namespace actor_zeta {
    std::string getdata();

    namespace level_debug {
        const std::string info = "info";
        const std::string debug = "debug";
        const std::string warning = "warning";
        const std::string error = "error";
        const std::string critical = "critical";
    };

    const std::string new_string = "\n";

    struct log_data {
        std::string level;
        std::string msg;
        std::string date;

        log_data(std::string level, std::string msg, std::string date) : level(level), msg(msg), date(date) {}

        log_data() {}

        std::string get() {
            return level + date + msg + new_string;
        }

        log_data &Info() {
            log_data::level = level_debug::info;
            return *this;
        }

        log_data &Debug() {
            log_data::level = level_debug::debug;
            return *this;
        }

        log_data &Warning() {
            log_data::level = level_debug::warning;
            return *this;
        }

        log_data &Error() {
            log_data::level = level_debug::error;
            return *this;
        }

        log_data &Critical() {
            log_data::level = level_debug::critical;
            return *this;
        }

        log_data &Msg(const std::string msg) {
            log_data::msg = msg;
            return *this;
        }

        log_data &Date() {
            log_data::date = getdata();
            return *this;
        }
    };


    class log : public local_actor {
    private:

        std::ofstream log_path;

        class logger_handler final : public abstract_action {
        private:
            std::ofstream &log;
        public:
            logger_handler(std::ofstream &log);

            void operator()(messaging::message &&msg) {
                std::string str_log = msg.get<log_data>().get();
                log << str_log;
                log.flush();
                std::cout << str_log;
                std::cout.flush();
            }
        };
    public:

        log(const std::string path, abstract_coordinator *e);

        log(const std::string path);

        ~log();
    };

    inline actor make_log(const std::string &path, actor_zeta::abstract_coordinator *e) {
        return actor(new log(path, e));
    }

    inline actor make_log(const std::string &path) {
        return actor(new log(path));
    }
}

#endif