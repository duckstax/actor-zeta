window.BENCHMARK_DATA = {
  "lastUpdate": 1692110114239,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-7 20.04 Release c++-11": [
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
        "date": 1692110113643,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28989.897764435962,
            "unit": "ns/iter",
            "extra": "iterations: 78280\ncpu: 9621.096065406235 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 29711.833367470885,
            "unit": "ns/iter",
            "extra": "iterations: 73233\ncpu: 9624.042439883659 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 23084.818019905302,
            "unit": "ns/iter",
            "extra": "iterations: 76360\ncpu: 7276.326610790987 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 34722.08358074106,
            "unit": "ns/iter",
            "extra": "iterations: 61976\ncpu: 10550.634116432164 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 34991.474345694594,
            "unit": "ns/iter",
            "extra": "iterations: 72405\ncpu: 10097.747393135834 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 37940.63634914842,
            "unit": "ns/iter",
            "extra": "iterations: 62747\ncpu: 10685.868647106636 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 37264.99120893085,
            "unit": "ns/iter",
            "extra": "iterations: 63246\ncpu: 10683.994244695314 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 34572.78323723928,
            "unit": "ns/iter",
            "extra": "iterations: 212292\ncpu: 10048.862886967003 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 34453.63122000003,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 10090.120999999996 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 35909.20675796263,
            "unit": "ns/iter",
            "extra": "iterations: 75141\ncpu: 10068.33952169921 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}