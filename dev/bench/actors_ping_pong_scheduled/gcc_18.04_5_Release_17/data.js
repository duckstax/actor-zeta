window.BENCHMARK_DATA = {
  "lastUpdate": 1692110990425,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-5 18.04 Release c++-17": [
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
        "date": 1692110989806,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 21572.034250000343,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7641.56 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 21389.338871918706,
            "unit": "ns/iter",
            "extra": "iterations: 89373\ncpu: 7491.372114620747 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 21070.73883216508,
            "unit": "ns/iter",
            "extra": "iterations: 87461\ncpu: 7656.2810852837265 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 20170.86011981719,
            "unit": "ns/iter",
            "extra": "iterations: 92808\ncpu: 7265.196965778811 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 17298.96901000018,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 6270.091999999999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 20991.038736615134,
            "unit": "ns/iter",
            "extra": "iterations: 98434\ncpu: 7511.0205823191245 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 21224.25701207017,
            "unit": "ns/iter",
            "extra": "iterations: 92626\ncpu: 7640.335327014014 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 21088.660792256924,
            "unit": "ns/iter",
            "extra": "iterations: 88860\ncpu: 7614.695025883418 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 20828.45970010844,
            "unit": "ns/iter",
            "extra": "iterations: 94901\ncpu: 7468.447118576197 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 21090.664106190623,
            "unit": "ns/iter",
            "extra": "iterations: 91910\ncpu: 7448.5387879447235 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}