#pragma once

// std
#include <fstream>
#include <iostream>
#include <thread>
#include <execinfo.h>
#include <string>

namespace sdk {

    namespace memory {

        struct memory_t {
            double rss_memory;
            double shared_memory;
            double private_memory;
        };

        inline auto memusage() -> memory_t {
            memory_t mem{0.0, 0.0, 0.0};

            int tSize = 0, resident = 0, share = 0;
            std::ifstream buffer("/proc/self/statm");
            buffer >> tSize >> resident >> share;
            buffer.close();

            long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
            double rss = resident * page_size_kb;
            mem.rss_memory = (rss / 1024);

            double shared_mem = share * page_size_kb;
            mem.shared_memory = (shared_mem / 1024);

            mem.private_memory = ((rss - shared_mem) / 1024);

            return mem;
        }

        class checker_t final {
            double memory_limit_mb_;
            bool need_abort_;
            memory_t mem_prev_;

            auto logger(std::string&& name, double oldval, double newval) const -> void {
                auto end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                std::cout << std::ctime(&end_time) << " :: "
                    << std::this_thread::get_id() << " :: "
                    << name << " Memory - "
                    << newval << " MB; increased for "
                    << newval - oldval << " MB" << std::endl;
            }

        public:
            checker_t(double memory_limit_mb, bool need_abort = true)
                : memory_limit_mb_(memory_limit_mb)
                , need_abort_(need_abort)
                , mem_prev_{0.0, 0.0, 0.0} {}
            ~checker_t() {}

            auto check() {
                auto mem = sdk::memory::memusage();
                if (mem.rss_memory > memory_limit_mb_) {
                    fprintf(stderr, "!!! MEMORY LIMIT EXCEEDED : %f Mb of %f Mb !!!\n", mem.rss_memory, memory_limit_mb_);
                    if (need_abort_) {
                        abort();
                    }
                } else if (mem.rss_memory > mem_prev_.rss_memory) {
                    logger("RSS", mem_prev_.rss_memory, mem.rss_memory);
                    logger("Shared", mem_prev_.shared_memory, mem.shared_memory);
                    logger("Private", mem_prev_.private_memory, mem.private_memory);
                }
                mem_prev_ = mem;
            }
        };

    }

}
