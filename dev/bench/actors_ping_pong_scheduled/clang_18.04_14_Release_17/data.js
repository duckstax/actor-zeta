window.BENCHMARK_DATA = {
  "lastUpdate": 1692109548742,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled clang-14 18.04 Release c++-17": [
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
          "id": "a5b7db6b2410da02082326530de010ad26bc6bf0",
          "message": "Clang build bm",
          "timestamp": "2023-08-15T16:18:27+03:00",
          "tree_id": "2aba661033231e5336973dbca7867784dd351421",
          "url": "https://github.com/duckstax/actor-zeta/commit/a5b7db6b2410da02082326530de010ad26bc6bf0"
        },
        "date": 1692107243564,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22309.483698293756,
            "unit": "ns/iter",
            "extra": "iterations: 154309\ncpu: 7844.567718020335 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 18797.145533759398,
            "unit": "ns/iter",
            "extra": "iterations: 86303\ncpu: 6666.34879436404 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 22336.047122731063,
            "unit": "ns/iter",
            "extra": "iterations: 90572\ncpu: 7851.135008611933 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 22523.077316714276,
            "unit": "ns/iter",
            "extra": "iterations: 89696\ncpu: 7906.791830181948 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 22272.694366197127,
            "unit": "ns/iter",
            "extra": "iterations: 107920\ncpu: 7806.007227575985 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 22350.934755557544,
            "unit": "ns/iter",
            "extra": "iterations: 83578\ncpu: 7903.716288975561 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22214.03514496955,
            "unit": "ns/iter",
            "extra": "iterations: 122578\ncpu: 7822.344140057755 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 19545.25392232204,
            "unit": "ns/iter",
            "extra": "iterations: 300651\ncpu: 6872.003419246903 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 22105.272424394436,
            "unit": "ns/iter",
            "extra": "iterations: 89445\ncpu: 7789.554474816933 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 21726.606345462045,
            "unit": "ns/iter",
            "extra": "iterations: 90742\ncpu: 7741.873663794045 ns\nthreads: 1"
          }
        ]
      },
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
        "date": 1692109548070,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 17664.224405318582,
            "unit": "ns/iter",
            "extra": "iterations: 122965\ncpu: 6314.321148294231 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 18470.340889999763,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 6425.663 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 21914.820709999956,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7612.317000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 21918.736277722786,
            "unit": "ns/iter",
            "extra": "iterations: 94281\ncpu: 7685.196381031174 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 21740.160308693186,
            "unit": "ns/iter",
            "extra": "iterations: 93426\ncpu: 7507.504334981694 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 22216.62256913023,
            "unit": "ns/iter",
            "extra": "iterations: 93845\ncpu: 7882.309126751552 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22125.121573466662,
            "unit": "ns/iter",
            "extra": "iterations: 86713\ncpu: 7795.174887271807 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 22170.975773195474,
            "unit": "ns/iter",
            "extra": "iterations: 93120\ncpu: 7751.839561855679 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 22159.228971495897,
            "unit": "ns/iter",
            "extra": "iterations: 90199\ncpu: 7787.067484118446 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 22111.211390036962,
            "unit": "ns/iter",
            "extra": "iterations: 90307\ncpu: 7776.7736720298535 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}