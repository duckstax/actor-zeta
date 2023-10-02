window.BENCHMARK_DATA = {
  "lastUpdate": 1696258586147,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-7 20.04 Release c++-14": [
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
        "date": 1692110677451,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 27953.358820000176,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8895.113 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 26189.175350979953,
            "unit": "ns/iter",
            "extra": "iterations: 82697\ncpu: 8581.31612996844 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 25871.668200500055,
            "unit": "ns/iter",
            "extra": "iterations: 67152\ncpu: 9874.045449130332 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25991.615845949596,
            "unit": "ns/iter",
            "extra": "iterations: 64862\ncpu: 8582.6801517067 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28009.33075681326,
            "unit": "ns/iter",
            "extra": "iterations: 73096\ncpu: 9382.226113604023 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27887.328397253674,
            "unit": "ns/iter",
            "extra": "iterations: 84480\ncpu: 8918.74763257576 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 26553.875480776136,
            "unit": "ns/iter",
            "extra": "iterations: 65259\ncpu: 8784.658054827689 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 27995.4783776697,
            "unit": "ns/iter",
            "extra": "iterations: 80033\ncpu: 9061.369685004938 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27353.34576275609,
            "unit": "ns/iter",
            "extra": "iterations: 77397\ncpu: 8275.446076721326 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27437.930342208754,
            "unit": "ns/iter",
            "extra": "iterations: 87169\ncpu: 9289.110807741288 ns\nthreads: 1"
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
        "date": 1692112554692,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 21840.673051078982,
            "unit": "ns/iter",
            "extra": "iterations: 91525\ncpu: 7737.048893744878 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 22352.829376974707,
            "unit": "ns/iter",
            "extra": "iterations: 98744\ncpu: 7994.917159523617 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 22170.024817452075,
            "unit": "ns/iter",
            "extra": "iterations: 87922\ncpu: 7842.160096449126 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 20474.33465614142,
            "unit": "ns/iter",
            "extra": "iterations: 93236\ncpu: 7226.308507443474 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 21732.726111916625,
            "unit": "ns/iter",
            "extra": "iterations: 86225\ncpu: 7770.638445926355 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 21994.860436075047,
            "unit": "ns/iter",
            "extra": "iterations: 90489\ncpu: 7893.600327111584 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22398.98339382356,
            "unit": "ns/iter",
            "extra": "iterations: 87618\ncpu: 8046.109246958384 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 22206.46505569317,
            "unit": "ns/iter",
            "extra": "iterations: 86366\ncpu: 7884.445267813721 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 21029.706533515735,
            "unit": "ns/iter",
            "extra": "iterations: 106145\ncpu: 7392.2332658156265 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 22127.47218365721,
            "unit": "ns/iter",
            "extra": "iterations: 91475\ncpu: 7875.471986881656 ns\nthreads: 1"
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
        "date": 1692117575397,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 31870.628479999825,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 10006.4 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 31321.64641795995,
            "unit": "ns/iter",
            "extra": "iterations: 69667\ncpu: 9785.15078875221 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 37755.24548163382,
            "unit": "ns/iter",
            "extra": "iterations: 66783\ncpu: 10555.108335953753 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 31923.645169999872,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 10050.667 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 33236.19339588795,
            "unit": "ns/iter",
            "extra": "iterations: 69805\ncpu: 9662.137382708977 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 35101.10376616738,
            "unit": "ns/iter",
            "extra": "iterations: 64867\ncpu: 10201.26258343997 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 37039.819727790564,
            "unit": "ns/iter",
            "extra": "iterations: 67154\ncpu: 10466.95952586592 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 33816.252256748914,
            "unit": "ns/iter",
            "extra": "iterations: 66135\ncpu: 10361.799349814773 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 33121.04710144936,
            "unit": "ns/iter",
            "extra": "iterations: 72312\ncpu: 10016.087233101003 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 30908.70776381579,
            "unit": "ns/iter",
            "extra": "iterations: 79819\ncpu: 10091.915458725358 ns\nthreads: 1"
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
          "id": "82aeadab4616f514c112e4040236e1f437d656eb",
          "message": "PMR for 17 std fix : no dyncast with nortti",
          "timestamp": "2023-10-02T17:29:14+03:00",
          "tree_id": "ea1869a91dd06f5d847cc1aa3cbed77af47ee437",
          "url": "https://github.com/duckstax/actor-zeta/commit/82aeadab4616f514c112e4040236e1f437d656eb"
        },
        "date": 1696258585499,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 21720.013982513134,
            "unit": "ns/iter",
            "extra": "iterations: 141820\ncpu: 7738.286560428714 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 15467.588238495322,
            "unit": "ns/iter",
            "extra": "iterations: 91876\ncpu: 5702.4304497366 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 22369.718819999776,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7989.399999999995 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 20199.110624176315,
            "unit": "ns/iter",
            "extra": "iterations: 86482\ncpu: 7296.904558173956 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 17016.900020633067,
            "unit": "ns/iter",
            "extra": "iterations: 87238\ncpu: 6226.176666131731 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 21649.701330000255,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7783.4990000000025 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22402.77851588545,
            "unit": "ns/iter",
            "extra": "iterations: 90020\ncpu: 7873.793601421902 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 16603.785975697123,
            "unit": "ns/iter",
            "extra": "iterations: 83612\ncpu: 6068.378940821889 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 21910.522579999848,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7869.033000000005 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 20016.54416643631,
            "unit": "ns/iter",
            "extra": "iterations: 86808\ncpu: 7237.902036678647 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}