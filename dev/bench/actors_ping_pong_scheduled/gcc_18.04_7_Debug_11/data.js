window.BENCHMARK_DATA = {
  "lastUpdate": 1692109735892,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-7 18.04 Debug c++-11": [
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
        "date": 1692109734599,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 33831.89494271627,
            "unit": "ns/iter",
            "extra": "iterations: 57521\ncpu: 11091.681299003842 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 33778.94341050998,
            "unit": "ns/iter",
            "extra": "iterations: 63404\ncpu: 10751.471515992682 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 32109.97301518947,
            "unit": "ns/iter",
            "extra": "iterations: 137003\ncpu: 10500.344518003256 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25200.361833379655,
            "unit": "ns/iter",
            "extra": "iterations: 64842\ncpu: 7814.0125227476055 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 32807.55821000014,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 10710.999999999995 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 32475.086108866617,
            "unit": "ns/iter",
            "extra": "iterations: 65603\ncpu: 10766.530494032279 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 32363.711894780878,
            "unit": "ns/iter",
            "extra": "iterations: 64171\ncpu: 10804.52540867369 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 32656.502909925162,
            "unit": "ns/iter",
            "extra": "iterations: 64091\ncpu: 10780.880310808061 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 32631.3327884442,
            "unit": "ns/iter",
            "extra": "iterations: 86256\ncpu: 10729.916759413834 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 32960.27966425057,
            "unit": "ns/iter",
            "extra": "iterations: 65525\ncpu: 10732.184662342619 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}