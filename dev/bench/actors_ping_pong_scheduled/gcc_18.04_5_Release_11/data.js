window.BENCHMARK_DATA = {
  "lastUpdate": 1692110088168,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-5 18.04 Release c++-11": [
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
        "date": 1692110086838,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 29432.25223000013,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9416.459 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27572.30378000031,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7532.378999999999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28896.638803108603,
            "unit": "ns/iter",
            "extra": "iterations: 80308\ncpu: 9133.758778701995 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 31247.667782519766,
            "unit": "ns/iter",
            "extra": "iterations: 81552\ncpu: 9326.948450068669 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28379.82419606712,
            "unit": "ns/iter",
            "extra": "iterations: 74913\ncpu: 8941.476112290256 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 35903.051449673934,
            "unit": "ns/iter",
            "extra": "iterations: 80156\ncpu: 9754.304106991378 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 36529.418104922544,
            "unit": "ns/iter",
            "extra": "iterations: 73063\ncpu: 9832.36248169389 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 41691.12163947682,
            "unit": "ns/iter",
            "extra": "iterations: 67363\ncpu: 10535.783738847738 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 38224.25983442623,
            "unit": "ns/iter",
            "extra": "iterations: 71992\ncpu: 9952.803089232137 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 35471.94145058771,
            "unit": "ns/iter",
            "extra": "iterations: 73391\ncpu: 9773.650720115538 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}