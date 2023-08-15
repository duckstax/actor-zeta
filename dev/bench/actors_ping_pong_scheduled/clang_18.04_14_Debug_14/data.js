window.BENCHMARK_DATA = {
  "lastUpdate": 1692108804645,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled clang-14 18.04 Debug c++-14": [
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
        "date": 1692106469414,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 26700.44886465888,
            "unit": "ns/iter",
            "extra": "iterations: 194435\ncpu: 8999.832334713401 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 20060.3206800311,
            "unit": "ns/iter",
            "extra": "iterations: 78820\ncpu: 6513.689418929209 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 26523.166356357255,
            "unit": "ns/iter",
            "extra": "iterations: 76805\ncpu: 8981.36709849619 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 26544.25812086125,
            "unit": "ns/iter",
            "extra": "iterations: 73853\ncpu: 8935.905108797206 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 26332.351966507835,
            "unit": "ns/iter",
            "extra": "iterations: 79303\ncpu: 8734.844835630434 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 26578.698761654385,
            "unit": "ns/iter",
            "extra": "iterations: 75827\ncpu: 8840.94979360914 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27623.64599000023,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9001.729000000003 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 27823.359321890635,
            "unit": "ns/iter",
            "extra": "iterations: 71198\ncpu: 9116.716761706783 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28353.768840054086,
            "unit": "ns/iter",
            "extra": "iterations: 77176\ncpu: 9117.904529905672 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27740.3375921917,
            "unit": "ns/iter",
            "extra": "iterations: 72946\ncpu: 9043.32245770846 ns\nthreads: 1"
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
        "date": 1692108804061,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 27240.80857402145,
            "unit": "ns/iter",
            "extra": "iterations: 152064\ncpu: 9338.41080071549 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 20906.371627216293,
            "unit": "ns/iter",
            "extra": "iterations: 76087\ncpu: 6914.145649059626 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 26675.38214201627,
            "unit": "ns/iter",
            "extra": "iterations: 76414\ncpu: 9129.921218624857 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25270.70662377319,
            "unit": "ns/iter",
            "extra": "iterations: 79577\ncpu: 8466.17615642711 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 26987.068319696118,
            "unit": "ns/iter",
            "extra": "iterations: 96429\ncpu: 9235.682211782761 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 26935.983281520203,
            "unit": "ns/iter",
            "extra": "iterations: 72375\ncpu: 9203.379620034544 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 26987.655096632898,
            "unit": "ns/iter",
            "extra": "iterations: 77355\ncpu: 9270.484131601062 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 26836.469987196146,
            "unit": "ns/iter",
            "extra": "iterations: 78100\ncpu: 9030.23303457106 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 26924.75681608838,
            "unit": "ns/iter",
            "extra": "iterations: 79261\ncpu: 9023.88312032398 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 26931.71528767306,
            "unit": "ns/iter",
            "extra": "iterations: 72287\ncpu: 9208.587989541671 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}