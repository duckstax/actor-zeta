window.BENCHMARK_DATA = {
  "lastUpdate": 1692110325886,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-7 20.04 Debug c++-14": [
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
        "date": 1692110325354,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 27290.040899999894,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8657.678000000002 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28526.59751139885,
            "unit": "ns/iter",
            "extra": "iterations: 72812\ncpu: 9293.972147448223 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 24792.888800000128,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7737.273 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28228.222475681036,
            "unit": "ns/iter",
            "extra": "iterations: 76278\ncpu: 9111.240462518681 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28997.21662345852,
            "unit": "ns/iter",
            "extra": "iterations: 75989\ncpu: 9279.335166932055 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28543.738264662596,
            "unit": "ns/iter",
            "extra": "iterations: 86427\ncpu: 9191.561664757537 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28697.951145843992,
            "unit": "ns/iter",
            "extra": "iterations: 73832\ncpu: 9288.27337739734 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 27172.116509960604,
            "unit": "ns/iter",
            "extra": "iterations: 77959\ncpu: 8656.321912800318 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 29373.834138362883,
            "unit": "ns/iter",
            "extra": "iterations: 78258\ncpu: 9435.722865393955 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 22911.798582389296,
            "unit": "ns/iter",
            "extra": "iterations: 71811\ncpu: 6971.234212028787 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}