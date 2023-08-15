window.BENCHMARK_DATA = {
  "lastUpdate": 1692110081547,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-8 18.04 Release c++-11": [
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
        "date": 1692110080975,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 24369.505820000086,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8453.496000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 24504.826884357026,
            "unit": "ns/iter",
            "extra": "iterations: 77480\ncpu: 8358.779039752195 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 18386.251920212537,
            "unit": "ns/iter",
            "extra": "iterations: 85928\ncpu: 6489.2433199888255 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 24647.90452163772,
            "unit": "ns/iter",
            "extra": "iterations: 82448\ncpu: 8474.936929943722 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 24202.499609727052,
            "unit": "ns/iter",
            "extra": "iterations: 83275\ncpu: 8409.328129690786 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 24699.74652555964,
            "unit": "ns/iter",
            "extra": "iterations: 82963\ncpu: 8542.76002555356 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 24559.906480731977,
            "unit": "ns/iter",
            "extra": "iterations: 80315\ncpu: 8654.421963518651 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 24483.75072355358,
            "unit": "ns/iter",
            "extra": "iterations: 82924\ncpu: 8411.207852973812 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 24544.200900003834,
            "unit": "ns/iter",
            "extra": "iterations: 89333\ncpu: 8573.569677498805 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 24497.445862344877,
            "unit": "ns/iter",
            "extra": "iterations: 82438\ncpu: 8507.956282296998 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}