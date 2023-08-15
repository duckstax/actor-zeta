window.BENCHMARK_DATA = {
  "lastUpdate": 1692110284616,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-4.8 18.04 Debug c++-14": [
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
        "date": 1692110283271,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 33373.582818357645,
            "unit": "ns/iter",
            "extra": "iterations: 116834\ncpu: 10378.344488761833 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 32607.625056153003,
            "unit": "ns/iter",
            "extra": "iterations: 97948\ncpu: 10522.344509331484 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 32265.01265514801,
            "unit": "ns/iter",
            "extra": "iterations: 65744\ncpu: 10246.501581893408 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25528.79552857678,
            "unit": "ns/iter",
            "extra": "iterations: 87802\ncpu: 7683.363704699213 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 26750.745112071803,
            "unit": "ns/iter",
            "extra": "iterations: 69866\ncpu: 8251.366902355936 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 33596.59712820621,
            "unit": "ns/iter",
            "extra": "iterations: 68250\ncpu: 10484.865934065938 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 33720.32361636777,
            "unit": "ns/iter",
            "extra": "iterations: 70015\ncpu: 10353.351424694709 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 33075.80400348128,
            "unit": "ns/iter",
            "extra": "iterations: 68940\ncpu: 10245.04351610095 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 31752.418226422014,
            "unit": "ns/iter",
            "extra": "iterations: 66036\ncpu: 9633.998122236346 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 35762.14511765543,
            "unit": "ns/iter",
            "extra": "iterations: 66167\ncpu: 10986.153218371699 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}