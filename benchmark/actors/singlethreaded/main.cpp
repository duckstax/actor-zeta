#include <benchmark/benchmark.h>

#include "define_supervisor.hpp"

int main(int argc, char** argv) {
    supervisor_t sup(actor_zeta::pmr::get_default_resource());
    return 0;
}

///#include "fixtures.hpp"
///
///REGISTER_BENCHMARKS(size_t);
///REGISTER_BENCHMARKS(int8_t);
///REGISTER_BENCHMARKS(int16_t);
///REGISTER_BENCHMARKS(int32_t);
///REGISTER_BENCHMARKS(int64_t);
///REGISTER_BENCHMARKS(short);
///
///class memory_manager_t : public benchmark::MemoryManager {
///    void Start() BENCHMARK_OVERRIDE {}
///    void Stop(Result* result) BENCHMARK_OVERRIDE {
///    }
///};
///
///// Run the benchmark
///int main(int argc, char** argv) {
///    benchmark::Initialize(&argc, argv);
///    if (benchmark::ReportUnrecognizedArguments(argc, argv))
///        return 1;
///    std::unique_ptr<benchmark::MemoryManager> mm(new memory_manager_t());
///    benchmark::RegisterMemoryManager(mm.get());
///    benchmark::RunSpecifiedBenchmarks();
///    benchmark::Shutdown();
///    benchmark::RegisterMemoryManager(nullptr);
///    return 0;
///}
///