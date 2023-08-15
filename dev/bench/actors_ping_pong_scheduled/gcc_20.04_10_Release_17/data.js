window.BENCHMARK_DATA = {
  "lastUpdate": 1692111166547,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-10 20.04 Release c++-17": [
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
        "date": 1692111165322,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 25333.71026765039,
            "unit": "ns/iter",
            "extra": "iterations: 80067\ncpu: 8692.283962181675 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 25203.319269660886,
            "unit": "ns/iter",
            "extra": "iterations: 76841\ncpu: 8724.417953956869 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 20305.564346575145,
            "unit": "ns/iter",
            "extra": "iterations: 81333\ncpu: 6914.299238931306 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28683.91464466092,
            "unit": "ns/iter",
            "extra": "iterations: 81190\ncpu: 8658.741224288704 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 20874.721485913058,
            "unit": "ns/iter",
            "extra": "iterations: 73867\ncpu: 7349.50519176358 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 20281.764899999645,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7015.006000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 26211.242070543678,
            "unit": "ns/iter",
            "extra": "iterations: 78221\ncpu: 9131.31511998057 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 26381.476094284113,
            "unit": "ns/iter",
            "extra": "iterations: 80692\ncpu: 8924.574926882471 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28249.777645959857,
            "unit": "ns/iter",
            "extra": "iterations: 79234\ncpu: 9151.923416715053 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 26546.050772069568,
            "unit": "ns/iter",
            "extra": "iterations: 79138\ncpu: 8904.399909019692 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}