window.BENCHMARK_DATA = {
  "lastUpdate": 1696257215387,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled clang-11 18.04 Debug c++-14": [
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
        "date": 1692106549863,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 35407.21242203653,
            "unit": "ns/iter",
            "extra": "iterations: 118966\ncpu: 10972.062606122758 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 35295.475131955165,
            "unit": "ns/iter",
            "extra": "iterations: 66310\ncpu: 11180.820389081588 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 36101.67014391385,
            "unit": "ns/iter",
            "extra": "iterations: 62885\ncpu: 10877.03744931223 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 33529.58448335228,
            "unit": "ns/iter",
            "extra": "iterations: 104636\ncpu: 10503.567605795331 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 34934.53233941247,
            "unit": "ns/iter",
            "extra": "iterations: 63050\ncpu: 11095.9254559873 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 37205.82772204601,
            "unit": "ns/iter",
            "extra": "iterations: 62701\ncpu: 11169.828232404587 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 37333.1756106196,
            "unit": "ns/iter",
            "extra": "iterations: 62109\ncpu: 11762.477257724324 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 36133.35147392368,
            "unit": "ns/iter",
            "extra": "iterations: 64827\ncpu: 11334.44706680857 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 36157.340078252295,
            "unit": "ns/iter",
            "extra": "iterations: 59551\ncpu: 11144.511427180058 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 34987.69054155729,
            "unit": "ns/iter",
            "extra": "iterations: 61194\ncpu: 11071.41059581007 ns\nthreads: 1"
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
        "date": 1692108785819,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22655.279713603853,
            "unit": "ns/iter",
            "extra": "iterations: 94275\ncpu: 7305.012993900822 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27624.508491335026,
            "unit": "ns/iter",
            "extra": "iterations: 74841\ncpu: 9303.169385764486 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 21210.769146873532,
            "unit": "ns/iter",
            "extra": "iterations: 115528\ncpu: 6799.912575306418 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27225.612524099743,
            "unit": "ns/iter",
            "extra": "iterations: 75726\ncpu: 9000.999656656897 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 27318.09461372238,
            "unit": "ns/iter",
            "extra": "iterations: 77716\ncpu: 8990.749652581191 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 23728.480736375062,
            "unit": "ns/iter",
            "extra": "iterations: 75505\ncpu: 7622.544202370714 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27003.693967861727,
            "unit": "ns/iter",
            "extra": "iterations: 80900\ncpu: 8646.912237330032 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 27338.517886365713,
            "unit": "ns/iter",
            "extra": "iterations: 73939\ncpu: 9142.727112890358 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 26976.68288867733,
            "unit": "ns/iter",
            "extra": "iterations: 79912\ncpu: 8841.677094804289 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27257.86029392916,
            "unit": "ns/iter",
            "extra": "iterations: 78250\ncpu: 8903.964217252396 ns\nthreads: 1"
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
        "date": 1692113738061,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 38257.29700514651,
            "unit": "ns/iter",
            "extra": "iterations: 236272\ncpu: 11476.32474436243 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28306.102469999812,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8927.404999999999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 41884.69322644272,
            "unit": "ns/iter",
            "extra": "iterations: 55259\ncpu: 11919.553375920674 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 42063.63640003301,
            "unit": "ns/iter",
            "extra": "iterations: 59945\ncpu: 11896.01468012344 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 42279.60831253424,
            "unit": "ns/iter",
            "extra": "iterations: 58899\ncpu: 12461.707329496263 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 41537.60979661115,
            "unit": "ns/iter",
            "extra": "iterations: 56591\ncpu: 12021.20655227863 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 30218.07889999991,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8967.681 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 37288.569691968216,
            "unit": "ns/iter",
            "extra": "iterations: 63013\ncpu: 11594.859790836823 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 38426.98625757989,
            "unit": "ns/iter",
            "extra": "iterations: 60688\ncpu: 12055.272871078289 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 38702.5418956886,
            "unit": "ns/iter",
            "extra": "iterations: 65496\ncpu: 11435.617442286555 ns\nthreads: 1"
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
          "id": "83edc9ba42e3d906163786de1e04b82b74d1c7d7",
          "message": "Add bm to README clang",
          "timestamp": "2023-08-15T19:19:03+03:00",
          "tree_id": "a8ce11e570c94b0b45155ece3758e54b11ac634b",
          "url": "https://github.com/duckstax/actor-zeta/commit/83edc9ba42e3d906163786de1e04b82b74d1c7d7"
        },
        "date": 1692118635992,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 20647.160830524503,
            "unit": "ns/iter",
            "extra": "iterations: 137648\ncpu: 6548.978553992794 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 33536.343092614785,
            "unit": "ns/iter",
            "extra": "iterations: 65886\ncpu: 11155.936010685124 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 38848.802589968,
            "unit": "ns/iter",
            "extra": "iterations: 56603\ncpu: 11121.8645654824 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 31341.236660125098,
            "unit": "ns/iter",
            "extra": "iterations: 64206\ncpu: 9104.262841478985 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 38043.23683999996,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 11113.732 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 33180.9200164443,
            "unit": "ns/iter",
            "extra": "iterations: 65676\ncpu: 11031.766550947064 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 35197.65983220133,
            "unit": "ns/iter",
            "extra": "iterations: 63648\ncpu: 11358.47316490698 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 38730.67366247383,
            "unit": "ns/iter",
            "extra": "iterations: 62466\ncpu: 11267.050875676372 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 43132.85381382608,
            "unit": "ns/iter",
            "extra": "iterations: 63768\ncpu: 12659.934449880813 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 45164.09294790579,
            "unit": "ns/iter",
            "extra": "iterations: 51233\ncpu: 11317.582417582418 ns\nthreads: 1"
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
          "id": "e6499af0a2e4580e50bce215f461727623d2dd8b",
          "message": "Fix build",
          "timestamp": "2023-10-02T17:18:16+03:00",
          "tree_id": "86790aa7bcef29acd2c836826f6288dfe4721578",
          "url": "https://github.com/duckstax/actor-zeta/commit/e6499af0a2e4580e50bce215f461727623d2dd8b"
        },
        "date": 1696257214093,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28115.182212526368,
            "unit": "ns/iter",
            "extra": "iterations: 118724\ncpu: 8421.804352953068 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 31953.71614034487,
            "unit": "ns/iter",
            "extra": "iterations: 59311\ncpu: 9882.283218964441 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 36486.674797919186,
            "unit": "ns/iter",
            "extra": "iterations: 62475\ncpu: 11327.343737494999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 29505.785650000005,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9108.25 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 39397.38978875699,
            "unit": "ns/iter",
            "extra": "iterations: 56428\ncpu: 12186.958602112416 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 32753.357223863135,
            "unit": "ns/iter",
            "extra": "iterations: 67014\ncpu: 9695.759095114456 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 36276.43121865488,
            "unit": "ns/iter",
            "extra": "iterations: 61412\ncpu: 11703.76310818732 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 29369.352164221546,
            "unit": "ns/iter",
            "extra": "iterations: 60114\ncpu: 8970.231560035938 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 37277.711840000055,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 11489.786999999998 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 29704.128686372704,
            "unit": "ns/iter",
            "extra": "iterations: 58662\ncpu: 8857.838123487096 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}