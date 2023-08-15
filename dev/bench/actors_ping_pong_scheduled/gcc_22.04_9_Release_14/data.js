window.BENCHMARK_DATA = {
  "lastUpdate": 1692110659526,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-9 22.04 Release c++-14": [
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
        "date": 1692110658520,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22193.83984999979,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7642.805 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 19923.860638761358,
            "unit": "ns/iter",
            "extra": "iterations: 91740\ncpu: 6965.790276869415 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 22543.18047126865,
            "unit": "ns/iter",
            "extra": "iterations: 84368\ncpu: 7691.959036601556 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 22274.480422879977,
            "unit": "ns/iter",
            "extra": "iterations: 84563\ncpu: 7873.184489670424 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 21432.754560000263,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7524.238999999997 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 21719.136820000243,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7460.483 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22345.098572045168,
            "unit": "ns/iter",
            "extra": "iterations: 88098\ncpu: 7773.103816204681 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 22398.813108087572,
            "unit": "ns/iter",
            "extra": "iterations: 93942\ncpu: 7870.999127120987 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 22217.413809145102,
            "unit": "ns/iter",
            "extra": "iterations: 88130\ncpu: 7763.75014183593 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 22421.174928338827,
            "unit": "ns/iter",
            "extra": "iterations: 92798\ncpu: 7916.753593827447 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}