window.BENCHMARK_DATA = {
  "lastUpdate": 1692111201718,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-8 20.04 Release c++-17": [
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
        "date": 1692111200703,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 27662.174667365864,
            "unit": "ns/iter",
            "extra": "iterations: 72452\ncpu: 9118.910451057252 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27761.570039116064,
            "unit": "ns/iter",
            "extra": "iterations: 75672\ncpu: 9060.119991542448 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28251.946499039062,
            "unit": "ns/iter",
            "extra": "iterations: 79064\ncpu: 9044.890215521604 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 23328.7143825904,
            "unit": "ns/iter",
            "extra": "iterations: 81105\ncpu: 7476.860859379821 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28071.814168500583,
            "unit": "ns/iter",
            "extra": "iterations: 83608\ncpu: 8937.991579753138 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27836.338230000023,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9058.663000000004 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 29992.82575419297,
            "unit": "ns/iter",
            "extra": "iterations: 78395\ncpu: 9231.855347917595 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 29508.92288631945,
            "unit": "ns/iter",
            "extra": "iterations: 79908\ncpu: 9188.569354757976 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27672.442991837197,
            "unit": "ns/iter",
            "extra": "iterations: 79015\ncpu: 9073.978358539514 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27803.51760563381,
            "unit": "ns/iter",
            "extra": "iterations: 77248\ncpu: 9141.507870753932 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}