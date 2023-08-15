window.BENCHMARK_DATA = {
  "lastUpdate": 1692110807095,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-10 20.04 Debug c++-17": [
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
        "date": 1692110806050,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 23650.877700000023,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7154.041 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 34471.7080810376,
            "unit": "ns/iter",
            "extra": "iterations: 65895\ncpu: 10645.869944608849 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 32044.593239340866,
            "unit": "ns/iter",
            "extra": "iterations: 65112\ncpu: 10473.900356309128 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 32217.973816300662,
            "unit": "ns/iter",
            "extra": "iterations: 103996\ncpu: 10360.660986961033 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 32533.399991018014,
            "unit": "ns/iter",
            "extra": "iterations: 66799\ncpu: 10582.865012949302 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 31699.339670563622,
            "unit": "ns/iter",
            "extra": "iterations: 94100\ncpu: 10331.276301806589 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 32933.47277881112,
            "unit": "ns/iter",
            "extra": "iterations: 66676\ncpu: 10468.543403923457 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 31786.026363488993,
            "unit": "ns/iter",
            "extra": "iterations: 67859\ncpu: 10391.852222991787 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 33493.31716799651,
            "unit": "ns/iter",
            "extra": "iterations: 68418\ncpu: 10567.866643281006 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 31827.65868897907,
            "unit": "ns/iter",
            "extra": "iterations: 64179\ncpu: 10253.313389114806 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}