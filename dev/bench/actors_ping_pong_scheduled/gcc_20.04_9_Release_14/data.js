window.BENCHMARK_DATA = {
  "lastUpdate": 1692110681545,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-9 20.04 Release c++-14": [
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
        "date": 1692110680608,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 20308.884849999915,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7205.726 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 21357.741119334714,
            "unit": "ns/iter",
            "extra": "iterations: 90393\ncpu: 7636.570309647871 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 19270.379684639873,
            "unit": "ns/iter",
            "extra": "iterations: 107052\ncpu: 6891.614355640249 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 21622.929898203627,
            "unit": "ns/iter",
            "extra": "iterations: 89099\ncpu: 7657.440599782263 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 21457.863959105467,
            "unit": "ns/iter",
            "extra": "iterations: 92531\ncpu: 7788.818882320521 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 21297.98121231406,
            "unit": "ns/iter",
            "extra": "iterations: 94530\ncpu: 7530.622024754049 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 21595.629158460022,
            "unit": "ns/iter",
            "extra": "iterations: 92913\ncpu: 7730.084057128714 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 21566.462378378008,
            "unit": "ns/iter",
            "extra": "iterations: 92500\ncpu: 7723.322162162157 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 21590.26689633607,
            "unit": "ns/iter",
            "extra": "iterations: 89694\ncpu: 7804.125136575469 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 21595.022353612716,
            "unit": "ns/iter",
            "extra": "iterations: 90992\ncpu: 7536.9911640583805 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}