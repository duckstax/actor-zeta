window.BENCHMARK_DATA = {
  "lastUpdate": 1692110602701,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-6 18.04 Release c++-14": [
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
        "date": 1692110601925,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 26688.729809999357,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8997.592 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 18512.040503132073,
            "unit": "ns/iter",
            "extra": "iterations: 78389\ncpu: 6500.510275676433 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 26456.02368968676,
            "unit": "ns/iter",
            "extra": "iterations: 79275\ncpu: 8753.446862188583 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28162.300837805455,
            "unit": "ns/iter",
            "extra": "iterations: 77703\ncpu: 8813.20927119931 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 26438.989464744955,
            "unit": "ns/iter",
            "extra": "iterations: 81251\ncpu: 8971.195431440845 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27422.607429356205,
            "unit": "ns/iter",
            "extra": "iterations: 83022\ncpu: 8933.168316831687 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27297.535253387523,
            "unit": "ns/iter",
            "extra": "iterations: 80588\ncpu: 8981.15724425473 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 25633.846870000525,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8793.195000000002 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 26905.05598985488,
            "unit": "ns/iter",
            "extra": "iterations: 81229\ncpu: 8878.122345467757 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 25293.86325742551,
            "unit": "ns/iter",
            "extra": "iterations: 83127\ncpu: 8679.54695826868 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}