window.BENCHMARK_DATA = {
  "lastUpdate": 1692111217740,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-10 22.04 Release c++-17": [
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
        "date": 1692111216494,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 26496.573800000075,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8579.593 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 25674.776415234184,
            "unit": "ns/iter",
            "extra": "iterations: 80976\ncpu: 8877.90209444774 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 23040.724638919583,
            "unit": "ns/iter",
            "extra": "iterations: 81976\ncpu: 8019.400800234213 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 20244.6750699994,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 6976.3110000000015 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 29640.773739999986,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9378.062999999996 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 30355.565490438395,
            "unit": "ns/iter",
            "extra": "iterations: 67674\ncpu: 8926.447380086891 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 29846.98166051418,
            "unit": "ns/iter",
            "extra": "iterations: 78301\ncpu: 8833.238400531289 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28213.508312155227,
            "unit": "ns/iter",
            "extra": "iterations: 75552\ncpu: 8733.042143159677 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 26691.723187934753,
            "unit": "ns/iter",
            "extra": "iterations: 79964\ncpu: 8733.138662398074 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 25392.691170678318,
            "unit": "ns/iter",
            "extra": "iterations: 81252\ncpu: 8802.955004184518 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}