window.BENCHMARK_DATA = {
  "lastUpdate": 1692109602750,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-4.9 16.04 Debug c++-11": [
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
        "date": 1692109601529,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28520.13688709649,
            "unit": "ns/iter",
            "extra": "iterations: 78846\ncpu: 9120.670674479365 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28795.573750880434,
            "unit": "ns/iter",
            "extra": "iterations: 75233\ncpu: 9215.802905639812 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 23864.402128492868,
            "unit": "ns/iter",
            "extra": "iterations: 94527\ncpu: 7519.3870534344705 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25449.65930999979,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8042.509 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28651.677478371435,
            "unit": "ns/iter",
            "extra": "iterations: 96747\ncpu: 9381.176677312993 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28735.273809999737,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9298.948999999999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28465.435906023667,
            "unit": "ns/iter",
            "extra": "iterations: 77636\ncpu: 9043.398681024273 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28898.682910636144,
            "unit": "ns/iter",
            "extra": "iterations: 75310\ncpu: 9300.367813039436 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28433.281731513398,
            "unit": "ns/iter",
            "extra": "iterations: 76257\ncpu: 9097.605465727735 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28566.198696677555,
            "unit": "ns/iter",
            "extra": "iterations: 75039\ncpu: 9199.199083143438 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}