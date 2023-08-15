window.BENCHMARK_DATA = {
  "lastUpdate": 1692109948559,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-4.8 18.04 Release c++-11": [
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
        "date": 1692109947917,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 23274.919419999947,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8360.337000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 23049.720986161763,
            "unit": "ns/iter",
            "extra": "iterations: 81082\ncpu: 8244.219432179769 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 23010.829554095784,
            "unit": "ns/iter",
            "extra": "iterations: 86790\ncpu: 8219.213042977299 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 16959.30984434658,
            "unit": "ns/iter",
            "extra": "iterations: 87502\ncpu: 6153.950766839614 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 23187.575168833533,
            "unit": "ns/iter",
            "extra": "iterations: 88993\ncpu: 8026.797613295429 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 22306.365438462777,
            "unit": "ns/iter",
            "extra": "iterations: 85355\ncpu: 7715.843242926595 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22954.691128826893,
            "unit": "ns/iter",
            "extra": "iterations: 90439\ncpu: 8238.923473280332 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 18405.80844936313,
            "unit": "ns/iter",
            "extra": "iterations: 81947\ncpu: 6596.846742406673 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 22543.874324460125,
            "unit": "ns/iter",
            "extra": "iterations: 89373\ncpu: 7958.5378134335915 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 22765.349888607274,
            "unit": "ns/iter",
            "extra": "iterations: 85733\ncpu: 8168.365740146742 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}