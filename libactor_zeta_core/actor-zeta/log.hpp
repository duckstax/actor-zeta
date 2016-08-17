#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <iostream>
#include <fstream>

#include <actor-zeta/actor/scheduled_actor.hpp>
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

    inline const std::string info(const std::string &msg) {
        std::string result;
        return result.append(level_debug::info).append(getdata()).append(msg).append(new_string);
    }

    inline const std::string debug(const std::string &msg) {
        std::string result;
        return result.append(level_debug::debug).append(getdata()).append(msg).append(new_string);
    }

    inline const std::string warning(const std::string &msg) {
        std::string result;
        return result.append(level_debug::warning).append(getdata()).append(msg).append(new_string);
    }

    inline const std::string error(const std::string &msg) {
        std::string result;
        return result.append(level_debug::error).append(getdata()).append(msg).append(new_string);
    }

    inline const std::string critical(const std::string &msg) {
        std::string result;
        return result.append(level_debug::critical).append(getdata()).append(msg).append(new_string);
    }

    class log final : public actor::scheduled_actor {
    private:
        std::ofstream log_path;
    public:

        log(environment::environment &,const std::string path);

        ~log();
    };
}

#endif