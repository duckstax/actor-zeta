window.BENCHMARK_DATA = {
  "lastUpdate": 1692113334533,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled clang-16 18.04 Debug c++-11": [
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
        "date": 1692106080393,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 26439.935627364946,
            "unit": "ns/iter",
            "extra": "iterations: 176022\ncpu: 8756.961061685472 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 25792.66086311853,
            "unit": "ns/iter",
            "extra": "iterations: 83627\ncpu: 8296.379159840722 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 21506.323550000277,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7004.836000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 26408.719747821386,
            "unit": "ns/iter",
            "extra": "iterations: 80895\ncpu: 8590.676803263486 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 26395.997953330734,
            "unit": "ns/iter",
            "extra": "iterations: 81596\ncpu: 8526.018432276089 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 26388.031079345583,
            "unit": "ns/iter",
            "extra": "iterations: 77093\ncpu: 8734.115937893193 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 25563.718794781904,
            "unit": "ns/iter",
            "extra": "iterations: 81645\ncpu: 8448.924000244964 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 26372.966176612208,
            "unit": "ns/iter",
            "extra": "iterations: 93663\ncpu: 8613.996989205987 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 26532.069542960133,
            "unit": "ns/iter",
            "extra": "iterations: 78527\ncpu: 8537.14518573229 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 26244.179054012522,
            "unit": "ns/iter",
            "extra": "iterations: 81037\ncpu: 8668.98330392289 ns\nthreads: 1"
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
        "date": 1692108478897,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22731.14564131072,
            "unit": "ns/iter",
            "extra": "iterations: 302373\ncpu: 7572.912263991825 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 26622.65713150548,
            "unit": "ns/iter",
            "extra": "iterations: 78027\ncpu: 8975.603316800592 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 26715.886815889018,
            "unit": "ns/iter",
            "extra": "iterations: 80506\ncpu: 9079.823864059823 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 26879.6163403472,
            "unit": "ns/iter",
            "extra": "iterations: 77991\ncpu: 9011.510302470793 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 23805.9764414622,
            "unit": "ns/iter",
            "extra": "iterations: 76745\ncpu: 7937.919082676392 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 26583.88157946853,
            "unit": "ns/iter",
            "extra": "iterations: 75747\ncpu: 8904.913725956141 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 26690.90154794704,
            "unit": "ns/iter",
            "extra": "iterations: 76230\ncpu: 9058.398268398276 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 25892.49660444683,
            "unit": "ns/iter",
            "extra": "iterations: 78485\ncpu: 8676.832515767353 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 26713.98417700855,
            "unit": "ns/iter",
            "extra": "iterations: 76471\ncpu: 8955.347778896577 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 26418.482113380604,
            "unit": "ns/iter",
            "extra": "iterations: 79361\ncpu: 8891.883922833631 ns\nthreads: 1"
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
          "id": "a399537583db8a03197a97a8f198d4629df94140",
          "message": "rm redundant file",
          "timestamp": "2023-08-15T17:57:42+03:00",
          "tree_id": "3ad66e1340f7c9b7ea7b34a8ae8158a5059eed65",
          "url": "https://github.com/duckstax/actor-zeta/commit/a399537583db8a03197a97a8f198d4629df94140"
        },
        "date": 1692113333928,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 15926.031334267596,
            "unit": "ns/iter",
            "extra": "iterations: 151304\ncpu: 5150.96362290488 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27993.7592006601,
            "unit": "ns/iter",
            "extra": "iterations: 75212\ncpu: 9314.88326330905 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 23242.39907590826,
            "unit": "ns/iter",
            "extra": "iterations: 75750\ncpu: 7678.512211221126 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28454.40406844878,
            "unit": "ns/iter",
            "extra": "iterations: 112377\ncpu: 9613.084527972811 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 25856.570948636767,
            "unit": "ns/iter",
            "extra": "iterations: 75308\ncpu: 8647.211451638605 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27164.336972602996,
            "unit": "ns/iter",
            "extra": "iterations: 78404\ncpu: 9104.09672975869 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27543.26986105523,
            "unit": "ns/iter",
            "extra": "iterations: 76217\ncpu: 9223.252030386922 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 27657.07850493644,
            "unit": "ns/iter",
            "extra": "iterations: 78097\ncpu: 9389.213414087611 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27383.120515408627,
            "unit": "ns/iter",
            "extra": "iterations: 72331\ncpu: 9071.228104132384 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 26913.526709359532,
            "unit": "ns/iter",
            "extra": "iterations: 76359\ncpu: 8963.227648345306 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}