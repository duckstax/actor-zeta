window.BENCHMARK_DATA = {
  "lastUpdate": 1692110414079,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-4.8 18.04 Release c++-14": [
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
        "date": 1692110413435,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22439.26126999952,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7832.108000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 22735.892279999913,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7960.913999999999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 22820.89742979537,
            "unit": "ns/iter",
            "extra": "iterations: 84040\ncpu: 8074.858400761541 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 22662.959356959396,
            "unit": "ns/iter",
            "extra": "iterations: 86091\ncpu: 7873.8637023614565 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 16304.265056745833,
            "unit": "ns/iter",
            "extra": "iterations: 86174\ncpu: 5821.374196393345 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 22716.972402901607,
            "unit": "ns/iter",
            "extra": "iterations: 112077\ncpu: 7903.2754267155615 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22729.882262109222,
            "unit": "ns/iter",
            "extra": "iterations: 91313\ncpu: 7893.398530329741 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 22572.997433799494,
            "unit": "ns/iter",
            "extra": "iterations: 89237\ncpu: 7966.602418279414 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 23014.014042079176,
            "unit": "ns/iter",
            "extra": "iterations: 85315\ncpu: 7952.140889644253 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 22866.361060537467,
            "unit": "ns/iter",
            "extra": "iterations: 87880\ncpu: 8145.913746017301 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}