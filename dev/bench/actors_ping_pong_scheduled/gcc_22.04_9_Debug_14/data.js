window.BENCHMARK_DATA = {
  "lastUpdate": 1692110407092,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-9 22.04 Debug c++-14": [
      {
        "commit": {
          "author": {
            "email": "grem_snoort@protonmail.com",
            "name": "GremSnoort",
            "username": "GremSnoort"
          },
          "committer": {
            "email": "grem_snoort@protonmail.com",
            "name": "GremSnoort",
            "username": "GremSnoort"
          },
          "distinct": true,
          "id": "13f5d5708aa4baefe68655e94d167b4efc46662f",
          "message": "BM run GCC and Clang",
          "timestamp": "2023-08-15T17:01:02+03:00",
          "tree_id": "0582bed100837da8b35e1568fdf6634365e7ed04",
          "url": "https://github.com/duckstax/actor-zeta/commit/13f5d5708aa4baefe68655e94d167b4efc46662f"
        },
        "date": 1692110406556,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 23851.025583094415,
            "unit": "ns/iter",
            "extra": "iterations: 73916\ncpu: 7650.181286866173 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 26163.45654999975,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8520.891 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28152.36103739469,
            "unit": "ns/iter",
            "extra": "iterations: 74610\ncpu: 9339.837823348078 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28577.848169195353,
            "unit": "ns/iter",
            "extra": "iterations: 82177\ncpu: 9382.031468659114 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28539.238860732963,
            "unit": "ns/iter",
            "extra": "iterations: 75768\ncpu: 9366.697022489703 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28575.117893560546,
            "unit": "ns/iter",
            "extra": "iterations: 78749\ncpu: 9412.682065804012 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27769.204169319262,
            "unit": "ns/iter",
            "extra": "iterations: 75408\ncpu: 9106.431678336518 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28421.764693894478,
            "unit": "ns/iter",
            "extra": "iterations: 73602\ncpu: 9352.17113665389 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28358.119696969745,
            "unit": "ns/iter",
            "extra": "iterations: 73920\ncpu: 9261.254058441547 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28649.697898435523,
            "unit": "ns/iter",
            "extra": "iterations: 74849\ncpu: 9377.067161885918 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}