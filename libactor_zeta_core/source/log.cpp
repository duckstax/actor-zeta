#include "actor-zeta/log.hpp"

namespace actor_zeta {
    log::log(const std::string path, abstract_coordinator *e) : log_j(log_path), local_actor("log", e) {
        life.insert(
                "log",
                [this](actor_zeta::book_contacts &bc, messaging::message &&msg) {
                    log_j.write(bc, std::move(msg));
                }
        );
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

    log::log(const std::string path) : log_j(log_path), local_actor("log", nullptr) {
        life.insert(
                "log",
                [this](book_contacts &bc, messaging::message &&msg) {
                    log_j.write(bc, std::move(msg));
                }
        );
        log_path.open(path, std::ios_base::app);
    }
}
