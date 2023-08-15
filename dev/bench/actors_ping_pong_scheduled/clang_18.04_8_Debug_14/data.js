window.BENCHMARK_DATA = {
  "lastUpdate": 1692113854383,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled clang-8 18.04 Debug c++-14": [
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
        "date": 1692106534097,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 23732.80783000558,
            "unit": "ns/iter",
            "extra": "iterations: 254738\ncpu: 7899.753472194961 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 26550.42088000016,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8930.613 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 27168.830806340495,
            "unit": "ns/iter",
            "extra": "iterations: 75452\ncpu: 9157.579653289506 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27121.652129297217,
            "unit": "ns/iter",
            "extra": "iterations: 79909\ncpu: 9093.588957439093 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 26612.586360996596,
            "unit": "ns/iter",
            "extra": "iterations: 79214\ncpu: 8829.574317671124 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 22668.270079528964,
            "unit": "ns/iter",
            "extra": "iterations: 74815\ncpu: 7470.610171756997 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27125.253249873713,
            "unit": "ns/iter",
            "extra": "iterations: 74926\ncpu: 9157.527427061368 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 27201.98987999993,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9143.348999999991 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27199.723091878957,
            "unit": "ns/iter",
            "extra": "iterations: 80236\ncpu: 9169.511191983662 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 24567.801450000385,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8117.071999999989 ns\nthreads: 1"
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
        "date": 1692108869155,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28059.971717411245,
            "unit": "ns/iter",
            "extra": "iterations: 202386\ncpu: 9383.61052641981 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 26799.590991797584,
            "unit": "ns/iter",
            "extra": "iterations: 104971\ncpu: 8970.069828809861 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28049.988036565843,
            "unit": "ns/iter",
            "extra": "iterations: 75480\ncpu: 9379.322999470063 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28142.726537217182,
            "unit": "ns/iter",
            "extra": "iterations: 76014\ncpu: 9546.950561738624 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 27696.387141606578,
            "unit": "ns/iter",
            "extra": "iterations: 71953\ncpu: 9294.747960474195 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 23336.991740788086,
            "unit": "ns/iter",
            "extra": "iterations: 72404\ncpu: 7805.432020330365 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27707.54284317161,
            "unit": "ns/iter",
            "extra": "iterations: 71575\ncpu: 9360.470834788684 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 27781.400343550726,
            "unit": "ns/iter",
            "extra": "iterations: 75098\ncpu: 9377.157847079809 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27835.620803644757,
            "unit": "ns/iter",
            "extra": "iterations: 71997\ncpu: 9341.557287109195 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27172.758708988054,
            "unit": "ns/iter",
            "extra": "iterations: 73028\ncpu: 9146.879279180608 ns\nthreads: 1"
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
        "date": 1692113853707,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 18157.650969999966,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5773.91 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27106.791544950447,
            "unit": "ns/iter",
            "extra": "iterations: 79077\ncpu: 8909.488220342195 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 22325.20242999954,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7338.234999999998 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27619.952769439333,
            "unit": "ns/iter",
            "extra": "iterations: 82616\ncpu: 9101.03975016946 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 27714.968953728938,
            "unit": "ns/iter",
            "extra": "iterations: 75468\ncpu: 9095.081358986587 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 25938.526088431616,
            "unit": "ns/iter",
            "extra": "iterations: 76624\ncpu: 8427.967738567548 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 26990.6127718541,
            "unit": "ns/iter",
            "extra": "iterations: 94536\ncpu: 8869.048827959721 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28123.211361389684,
            "unit": "ns/iter",
            "extra": "iterations: 76892\ncpu: 9350.365447640837 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27672.7736749793,
            "unit": "ns/iter",
            "extra": "iterations: 75829\ncpu: 9138.915190758154 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27439.834752237457,
            "unit": "ns/iter",
            "extra": "iterations: 100782\ncpu: 9140.683852275204 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}