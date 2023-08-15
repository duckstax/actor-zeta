window.BENCHMARK_DATA = {
  "lastUpdate": 1692110762565,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-7 18.04 Debug c++-17": [
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
        "date": 1692110761396,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22463.86515999973,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7229.991000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28274.13151712507,
            "unit": "ns/iter",
            "extra": "iterations: 74918\ncpu: 9261.63004885341 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28805.340496766436,
            "unit": "ns/iter",
            "extra": "iterations: 104838\ncpu: 9666.074324195426 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 29057.64740810728,
            "unit": "ns/iter",
            "extra": "iterations: 69891\ncpu: 9746.028816299664 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 29218.07363825358,
            "unit": "ns/iter",
            "extra": "iterations: 72150\ncpu: 9663.819819819824 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 29144.781414158333,
            "unit": "ns/iter",
            "extra": "iterations: 71958\ncpu: 9746.680007782314 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28651.127410487545,
            "unit": "ns/iter",
            "extra": "iterations: 70214\ncpu: 9533.389352550776 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28639.221380542305,
            "unit": "ns/iter",
            "extra": "iterations: 71682\ncpu: 9574.21946932285 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28931.514764477633,
            "unit": "ns/iter",
            "extra": "iterations: 73284\ncpu: 9497.041646198344 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28744.874951803413,
            "unit": "ns/iter",
            "extra": "iterations: 72620\ncpu: 9536.6414210961 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}