#include "actor-zeta/log.hpp"

namespace actor_zeta {
    log::log(const std::string path, abstract_coordinator *e) :local_actor("log", e) {
        life.insert("log", new logger_handler(log_path));
        log_path.open(path, std::ios_base::app);
    }

    log::~log() {
        log_path.close();
    }

    log::logger_handler::logger_handler(std::ofstream &log) : log(log) { }

    std::string getdata() {
        time_t rawtime;
        struct tm *timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, " %d-%m-%Y-%H:%M:%S ", timeinfo);
        std::string d(buffer);
        return d;
    }

    log::log(const std::string path) : local_actor("log", nullptr) {
        life.insert("log", new logger_handler(log_path));
        log_path.open(path, std::ios_base::app);
    }
}
