#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <unordered_map>
#include <vector>

#include <actor-zeta/base/metadata.hpp>
#include <actor-zeta/forwards.hpp>

namespace actor_zeta { namespace executor {
    using std::setw;

    /// @brief
    /// @tparam Policy
    ///

    template<class Policy = profiled<work_sharing>>
    class profiled_executor final : public executor_t<Policy> {
    public:
        using super = executor_t<Policy>;
        using clock_type = std::chrono::high_resolution_clock;

        using usec = std::chrono::microseconds;
        using msec = std::chrono::milliseconds;

        class measurement final {
        public:
            static usec to_usec(const ::timeval& tv) {
                return std::chrono::seconds(tv.tv_sec) + usec(tv.tv_usec);
            }

            static measurement take() {
                auto now = clock_type::now().time_since_epoch();
                measurement m;
                m.runtime = std::chrono::duration_cast<usec>(now);
                return m;
            }

            measurement& operator+=(const measurement& other) {
                runtime += other.runtime;
                usr += other.usr;
                sys += other.sys;
                mem += other.mem;
                return *this;
            }

            measurement& operator-=(const measurement& other) {
                runtime -= other.runtime;
                usr -= other.usr;
                sys -= other.sys;
                mem -= other.mem;
                return *this;
            }

            friend measurement operator+(const measurement& x, const measurement& y) {
                measurement tmp(x);
                tmp += y;
                return tmp;
            }

            friend measurement operator-(const measurement& x, const measurement& y) {
                measurement tmp(x);
                tmp -= y;
                return tmp;
            }

            friend std::ostream& operator<<(std::ostream& out, const measurement& m) {
                using std::setw;
                out << setw(15) << m.runtime.count()
                    << setw(15) << m.usr.count()
                    << setw(15) << m.sys.count()
                    << m.mem;
                return out;
            }

            usec runtime = usec::zero();
            usec usr = usec::zero();
            usec sys = usec::zero();
            long mem = 0;
        };

        struct worker_state final {
            actor_id current;
            measurement job;
            measurement worker;
            clock_type::duration last_flush = clock_type::duration::zero();
        };

        profiled_executor(std::size_t num_worker_threads, std::size_t max_throughput)
            : super(num_worker_threads, max_throughput) {
            auto fname = "profiling-output-file.txt";
            file_.open(fname);
            if (!file_)
                std::cerr << R"([WARNING] could not open file ")"
                          << fname
                          << R"(" (no profiler output will be generated))"
                          << std::endl;
            resolution_ = std::chrono::duration_cast<msec>(std::chrono::duration_cast<std::chrono::duration<int64_t, std::nano>>(std::chrono::milliseconds{100}));
        }

        void start() override {
            clock_start_ = clock_type::now().time_since_epoch();
            super::start();
            worker_states_.resize(this->num_workers());
            file_.flags(std::ios::left);
            file_ << setw(21) << "clock" /// UNIX timestamp in microseconds
                  << setw(10) << "type"  /// "actor" or "worker"
                  << setw(10) << "id"    /// ID of the above
                  << setw(15) << "time"  /// duration of this sample (cumulative)
                  << setw(15) << "usr"   /// time spent in user mode (cumulative)
                  << setw(15) << "sys"   /// time spent in kernel model (cumulative)
                  << "mem"               /// used memory (cumulative)
                  << '\n';
            file_.flush();
        }

        void stop() override {
            super::stop();
            auto now = clock_type::now().time_since_epoch();
            auto wall_clock = system_start_ + (now - clock_start_);
            for (size_t i = 0; i < worker_states_.size(); ++i) {
                record(wall_clock, "worker", i, worker_states_[i].worker);
            }
        }

        void start_measuring(size_t worker, actor_id job) {
            auto& w = worker_states_[worker];
            w.current = job;
            w.job = measurement::take();
        }

        void stop_measuring(size_t worker, actor_id job) {
            auto m = measurement::take();
            auto& w = worker_states_[worker];
            assert(job == w.current);
            auto delta = m - w.job;
            if (delta.runtime < delta.usr + delta.sys) {
                delta.runtime = delta.usr + delta.sys;
            }
            w.worker += delta;
            report(job, delta);
            if (m.runtime - w.last_flush >= resolution_) {
                w.last_flush = m.runtime;
                auto wallclock = system_start_ + (m.runtime - clock_start_);
                std::lock_guard<std::mutex> file_guard{file_mtx_};
                record(wallclock, "worker", worker, w.worker);
                w.worker = {};
            }
        }

        void remove_job(actor_id job) {
            std::lock_guard<std::mutex> job_guard{job_mtx_};
            auto j = jobs_.find(job);
            if (j != jobs_.end()) {
                if (job != 0) {
                    auto now = clock_type::now().time_since_epoch();
                    auto wallclock = system_start_ + (now - clock_start_);
                    std::lock_guard<std::mutex> file_guard{file_mtx_};
                    record(wallclock, "actor", job, j->second);
                }
                jobs_.erase(j);
            }
        }

        template<class Time, class Label>
        void record(Time t, Label label, size_t rec_id, const measurement& m) {
            file_ << setw(21) << t.time_since_epoch().count()
                  << setw(10) << label
                  << setw(10) << rec_id
                  << m
                  << '\n';
            file_.flush();
        }

        void report(const actor_id& job, const measurement& m) {
            std::lock_guard<std::mutex> job_guard{job_mtx_};
            jobs_[job] += m;
            if (m.runtime - last_flush_ >= resolution_) {
                last_flush_ = m.runtime;
                auto now = clock_type::now().time_since_epoch();
                auto wallclock = system_start_ + (now - clock_start_);
                std::lock_guard<std::mutex> file_guard{file_mtx_};
                for (auto& j : jobs_) {
                    record(wallclock, "actor", j.first, j.second);
                    j.second = {};
                }
            }
        }

        std::mutex job_mtx_;
        std::mutex file_mtx_;
        std::ofstream file_;
        msec resolution_;
        std::chrono::system_clock::time_point system_start_;
        clock_type::duration clock_start_;
        std::vector<worker_state> worker_states_;
        std::unordered_map<actor_id, measurement> jobs_;
        clock_type::duration last_flush_ = clock_type::duration::zero();
    };

}} // namespace actor_zeta::executor