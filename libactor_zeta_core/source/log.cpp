#include "actor-zeta/log.hpp"

namespace actor_zeta {
    class logger_handler final : public behavior::interface_action {
    private:
        std::ofstream &log;
        std::string t;
    public:
        logger_handler(std::ofstream &log) : log(log), t("log") {}

        const std::string &name() const override final {
            return t;
        }

        void operator()(messaging::message &&msg) override final {
            std::string str_log = msg.get<std::string>();
            log << str_log;
            log.flush();
            std::cout << str_log;
            std::cout.flush();
        }
    };

    log::~log() {
        log_path.close();
    }

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

    log::log(environment::environment &env, const std::string path) : local_actor(env,"log") {
        attach(new logger_handler(log_path));
        log_path.open(path, std::ios_base::app);
    }
}
