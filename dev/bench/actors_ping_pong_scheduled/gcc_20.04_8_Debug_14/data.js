window.BENCHMARK_DATA = {
  "lastUpdate": 1692110353930,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-8 20.04 Debug c++-14": [
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
        "date": 1692110352838,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 29509.90251163982,
            "unit": "ns/iter",
            "extra": "iterations: 76245\ncpu: 9623.553019870156 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27683.207267945498,
            "unit": "ns/iter",
            "extra": "iterations: 72235\ncpu: 8789.215754135806 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 24274.210709999694,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7666.0329999999985 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 30079.591038169532,
            "unit": "ns/iter",
            "extra": "iterations: 71838\ncpu: 9701.848603803002 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 31836.23280474632,
            "unit": "ns/iter",
            "extra": "iterations: 72142\ncpu: 10529.184109118129 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 30606.554118539316,
            "unit": "ns/iter",
            "extra": "iterations: 67269\ncpu: 10033.776330850766 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 30036.63521206564,
            "unit": "ns/iter",
            "extra": "iterations: 74128\ncpu: 9838.750539607156 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 25166.141070000096,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8179.7039999999915 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28727.48262422383,
            "unit": "ns/iter",
            "extra": "iterations: 73637\ncpu: 9646.80527452231 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 32058.61968216636,
            "unit": "ns/iter",
            "extra": "iterations: 64688\ncpu: 10386.906381399962 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}