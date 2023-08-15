window.BENCHMARK_DATA = {
  "lastUpdate": 1692111129364,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-6 18.04 Release c++-17": [
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
        "date": 1692111128090,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 25806.783571258486,
            "unit": "ns/iter",
            "extra": "iterations: 92326\ncpu: 8546.361804908694 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 25048.007089999377,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8343.851999999999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 24387.101087587325,
            "unit": "ns/iter",
            "extra": "iterations: 79258\ncpu: 8833.89058517752 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25679.653048595363,
            "unit": "ns/iter",
            "extra": "iterations: 82415\ncpu: 8637.294181884363 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 24617.43374999969,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8772.003 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 26440.954914614096,
            "unit": "ns/iter",
            "extra": "iterations: 81512\ncpu: 9422.911963882625 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 24868.119155238375,
            "unit": "ns/iter",
            "extra": "iterations: 91150\ncpu: 8762.526604498087 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 25177.656720730698,
            "unit": "ns/iter",
            "extra": "iterations: 86501\ncpu: 8648.387879908909 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 24122.465889669194,
            "unit": "ns/iter",
            "extra": "iterations: 74303\ncpu: 8599.273246033123 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 25534.925465241013,
            "unit": "ns/iter",
            "extra": "iterations: 83290\ncpu: 8914.429103133634 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}