window.BENCHMARK_DATA = {
  "lastUpdate": 1692110261904,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-6 18.04 Debug c++-14": [
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
        "date": 1692110261328,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 27174.987779999923,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8923.596 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28360.474775241477,
            "unit": "ns/iter",
            "extra": "iterations: 75303\ncpu: 9347.318167934876 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28348.215347599133,
            "unit": "ns/iter",
            "extra": "iterations: 74396\ncpu: 9338.76686918652 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28529.2214062008,
            "unit": "ns/iter",
            "extra": "iterations: 73119\ncpu: 9394.261409483164 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28814.48627794482,
            "unit": "ns/iter",
            "extra": "iterations: 107309\ncpu: 9478.794882069538 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28665.540345807825,
            "unit": "ns/iter",
            "extra": "iterations: 103121\ncpu: 9389.904093249683 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28372.12360311877,
            "unit": "ns/iter",
            "extra": "iterations: 75257\ncpu: 9336.35143574684 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28521.63039093924,
            "unit": "ns/iter",
            "extra": "iterations: 74871\ncpu: 9399.146532035098 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 30428.854111050965,
            "unit": "ns/iter",
            "extra": "iterations: 67428\ncpu: 10185.58758972534 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28676.81034682343,
            "unit": "ns/iter",
            "extra": "iterations: 77705\ncpu: 9472.80097805804 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}