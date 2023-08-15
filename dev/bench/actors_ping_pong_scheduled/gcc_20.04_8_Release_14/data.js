window.BENCHMARK_DATA = {
  "lastUpdate": 1692110730101,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-8 20.04 Release c++-14": [
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
        "date": 1692110728796,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 29219.795660000043,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9675.132000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27993.998569999123,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9555.811000000002 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28770.829435876523,
            "unit": "ns/iter",
            "extra": "iterations: 76118\ncpu: 9459.504979111382 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 21293.556988721102,
            "unit": "ns/iter",
            "extra": "iterations: 73497\ncpu: 7228.567152400778 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28942.65111286433,
            "unit": "ns/iter",
            "extra": "iterations: 77323\ncpu: 9743.4243368726 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27999.94851834976,
            "unit": "ns/iter",
            "extra": "iterations: 72453\ncpu: 9555.366927525427 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27572.053538420485,
            "unit": "ns/iter",
            "extra": "iterations: 75740\ncpu: 9317.067599683118 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28334.529376936716,
            "unit": "ns/iter",
            "extra": "iterations: 72625\ncpu: 9617.81342512909 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 29035.09804810481,
            "unit": "ns/iter",
            "extra": "iterations: 77207\ncpu: 9634.275389537219 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 29340.681575461676,
            "unit": "ns/iter",
            "extra": "iterations: 74721\ncpu: 9573.209673318072 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}