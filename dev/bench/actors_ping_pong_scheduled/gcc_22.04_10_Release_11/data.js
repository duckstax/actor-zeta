window.BENCHMARK_DATA = {
  "lastUpdate": 1692110194613,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-10 22.04 Release c++-11": [
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
        "date": 1692110193491,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 25420.028820000196,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8983.782000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 24755.3638630899,
            "unit": "ns/iter",
            "extra": "iterations: 76985\ncpu: 8804.917841137885 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 27886.797519892225,
            "unit": "ns/iter",
            "extra": "iterations: 80561\ncpu: 8982.309057732647 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25584.355447154394,
            "unit": "ns/iter",
            "extra": "iterations: 79950\ncpu: 9110.345215759851 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 21149.832969999807,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7526.866000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28673.22665733877,
            "unit": "ns/iter",
            "extra": "iterations: 77187\ncpu: 8933.918924171167 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 26876.34211528586,
            "unit": "ns/iter",
            "extra": "iterations: 73522\ncpu: 9305.391583471614 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 25443.127292421697,
            "unit": "ns/iter",
            "extra": "iterations: 80319\ncpu: 9013.798727573798 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 25076.713625668617,
            "unit": "ns/iter",
            "extra": "iterations: 82029\ncpu: 8821.678918431286 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 25265.622800190748,
            "unit": "ns/iter",
            "extra": "iterations: 119499\ncpu: 8860.714315600972 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}