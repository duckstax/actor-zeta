window.BENCHMARK_DATA = {
  "lastUpdate": 1692110691951,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-11 22.04 Release c++-14": [
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
        "date": 1692110691313,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 23853.44917135111,
            "unit": "ns/iter",
            "extra": "iterations: 171665\ncpu: 8427.5373547316 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 23833.906067663404,
            "unit": "ns/iter",
            "extra": "iterations: 83294\ncpu: 8411.543448507697 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 18502.347350104246,
            "unit": "ns/iter",
            "extra": "iterations: 82758\ncpu: 6667.852050557043 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 24253.07450000105,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8545.2 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 24218.4309770946,
            "unit": "ns/iter",
            "extra": "iterations: 81118\ncpu: 8308.372987499699 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 23983.550716621496,
            "unit": "ns/iter",
            "extra": "iterations: 84982\ncpu: 8407.849897625383 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 24858.18895852642,
            "unit": "ns/iter",
            "extra": "iterations: 84246\ncpu: 8858.233031835342 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 24248.963643655883,
            "unit": "ns/iter",
            "extra": "iterations: 82269\ncpu: 8676.444347202465 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 24235.131743453738,
            "unit": "ns/iter",
            "extra": "iterations: 81264\ncpu: 8539.068960425278 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 23389.095930000396,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8081.994999999988 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}