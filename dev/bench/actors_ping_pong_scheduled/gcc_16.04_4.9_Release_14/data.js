window.BENCHMARK_DATA = {
  "lastUpdate": 1692110544732,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-4.9 16.04 Release c++-14": [
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
        "date": 1692110543518,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 21503.34600509642,
            "unit": "ns/iter",
            "extra": "iterations: 89464\ncpu: 7480.300456049362 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 26083.629875571343,
            "unit": "ns/iter",
            "extra": "iterations: 78760\ncpu: 8883.735398679533 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 25484.25914973601,
            "unit": "ns/iter",
            "extra": "iterations: 80822\ncpu: 8934.031575561108 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 21506.55509834582,
            "unit": "ns/iter",
            "extra": "iterations: 82870\ncpu: 7532.4604802703025 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 26662.179540001034,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9161.292000000003 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27308.26432758079,
            "unit": "ns/iter",
            "extra": "iterations: 73704\ncpu: 9445.102029740578 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 26439.044811631204,
            "unit": "ns/iter",
            "extra": "iterations: 76074\ncpu: 8935.228856113776 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 25616.17883311751,
            "unit": "ns/iter",
            "extra": "iterations: 80248\ncpu: 8819.504535938593 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 25910.759951954577,
            "unit": "ns/iter",
            "extra": "iterations: 82421\ncpu: 8939.250919061888 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 25790.331145906075,
            "unit": "ns/iter",
            "extra": "iterations: 74212\ncpu: 8823.955694496857 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}