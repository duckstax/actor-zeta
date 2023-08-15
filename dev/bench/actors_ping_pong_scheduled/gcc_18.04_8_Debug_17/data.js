window.BENCHMARK_DATA = {
  "lastUpdate": 1692110866093,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-8 18.04 Debug c++-17": [
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
        "date": 1692110864957,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 38717.94083999987,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 10744.187 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 30890.6662461475,
            "unit": "ns/iter",
            "extra": "iterations: 62621\ncpu: 8879.094872327178 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 36903.78045964979,
            "unit": "ns/iter",
            "extra": "iterations: 104819\ncpu: 11040.150163615377 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 38063.06603948461,
            "unit": "ns/iter",
            "extra": "iterations: 64734\ncpu: 11119.23564123954 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 36849.077111863604,
            "unit": "ns/iter",
            "extra": "iterations: 61119\ncpu: 10909.841456830125 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 39733.364694987016,
            "unit": "ns/iter",
            "extra": "iterations: 65866\ncpu: 11266.56241459933 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 36118.79708130608,
            "unit": "ns/iter",
            "extra": "iterations: 60438\ncpu: 10953.726132565607 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 37516.0949337776,
            "unit": "ns/iter",
            "extra": "iterations: 64782\ncpu: 11079.168596214995 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 35841.045270981616,
            "unit": "ns/iter",
            "extra": "iterations: 63639\ncpu: 10812.640047769451 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 38332.34122040438,
            "unit": "ns/iter",
            "extra": "iterations: 65339\ncpu: 11594.646382711691 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}