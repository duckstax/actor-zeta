window.BENCHMARK_DATA = {
  "lastUpdate": 1692110745280,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-10 22.04 Release c++-14": [
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
        "date": 1692110743937,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 26499.398210000323,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8231.224 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 20099.706217189287,
            "unit": "ns/iter",
            "extra": "iterations: 83623\ncpu: 6667.150185953626 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 29224.86160065106,
            "unit": "ns/iter",
            "extra": "iterations: 68772\ncpu: 8979.58907694992 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27289.69788991726,
            "unit": "ns/iter",
            "extra": "iterations: 73599\ncpu: 8516.975774127364 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 27529.682668274825,
            "unit": "ns/iter",
            "extra": "iterations: 91220\ncpu: 8425.153475115103 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28535.02699544498,
            "unit": "ns/iter",
            "extra": "iterations: 92423\ncpu: 8602.693052595134 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27042.20203193046,
            "unit": "ns/iter",
            "extra": "iterations: 89570\ncpu: 8296.944289382605 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 26983.21608649112,
            "unit": "ns/iter",
            "extra": "iterations: 85003\ncpu: 8319.513428937807 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27391.54218822704,
            "unit": "ns/iter",
            "extra": "iterations: 79489\ncpu: 8509.61642491414 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28173.79670186735,
            "unit": "ns/iter",
            "extra": "iterations: 76892\ncpu: 8562.988347292297 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}