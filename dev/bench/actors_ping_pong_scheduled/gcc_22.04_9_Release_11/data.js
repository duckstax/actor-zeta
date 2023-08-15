window.BENCHMARK_DATA = {
  "lastUpdate": 1692105401084,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark": [
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
          "id": "9ea7db2e5ada69e5d48b60cf590979573f31e1d1",
          "message": "Clear ci cd gcc builds",
          "timestamp": "2023-08-15T13:08:01+03:00",
          "tree_id": "cf67563764789fb9c14f5ae68cf63d38a82d2fb9",
          "url": "https://github.com/duckstax/actor-zeta/commit/9ea7db2e5ada69e5d48b60cf590979573f31e1d1"
        },
        "date": 1692094517594,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28995.049661244542,
            "unit": "ns/iter",
            "extra": "iterations: 116308\ncpu: 9464.321456821544 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 23926.98760829727,
            "unit": "ns/iter",
            "extra": "iterations: 76987\ncpu: 7867.371114603761 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28722.43280551647,
            "unit": "ns/iter",
            "extra": "iterations: 75847\ncpu: 9528.126359645074 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28338.574329999916,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9322.224000000002 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 29415.969051799664,
            "unit": "ns/iter",
            "extra": "iterations: 77452\ncpu: 9343.407529824917 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27754.737014829814,
            "unit": "ns/iter",
            "extra": "iterations: 72217\ncpu: 9314.749989614635 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28205.07479164999,
            "unit": "ns/iter",
            "extra": "iterations: 74634\ncpu: 9282.788005466675 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28740.223683695815,
            "unit": "ns/iter",
            "extra": "iterations: 76711\ncpu: 9445.478484180892 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28100.07239477132,
            "unit": "ns/iter",
            "extra": "iterations: 83390\ncpu: 9105.491066075083 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28384.41968797134,
            "unit": "ns/iter",
            "extra": "iterations: 72237\ncpu: 9122.56599803426 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Benchmark actors_ping_pong_scheduled gcc-9 22.04 Release c++-11": [
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
          "id": "86aa937ef15f5428085e7cc8c00d54ef97859541",
          "message": "Named bm",
          "timestamp": "2023-08-15T13:27:57+03:00",
          "tree_id": "ae04af2b4d57ab6b294a91fd6505a3e455ab9971",
          "url": "https://github.com/duckstax/actor-zeta/commit/86aa937ef15f5428085e7cc8c00d54ef97859541"
        },
        "date": 1692095714726,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 31862.91657884067,
            "unit": "ns/iter",
            "extra": "iterations: 141379\ncpu: 9251.623649905574 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27251.0915700002,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8096.828000000002 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 31531.68233909202,
            "unit": "ns/iter",
            "extra": "iterations: 73909\ncpu: 9295.150793543411 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 29801.520238579982,
            "unit": "ns/iter",
            "extra": "iterations: 76117\ncpu: 9181.1540129012 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 30032.18804294781,
            "unit": "ns/iter",
            "extra": "iterations: 80003\ncpu: 9175.389672887259 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 31171.73869205632,
            "unit": "ns/iter",
            "extra": "iterations: 124669\ncpu: 9420.676350977394 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 29422.7907100003,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9264.660999999998 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 30845.276676778103,
            "unit": "ns/iter",
            "extra": "iterations: 76143\ncpu: 9370.275665524074 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 30035.899223179087,
            "unit": "ns/iter",
            "extra": "iterations: 76208\ncpu: 9247.950346420334 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28045.065742767983,
            "unit": "ns/iter",
            "extra": "iterations: 73529\ncpu: 9037.672210964385 ns\nthreads: 1"
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
          "id": "490632efe51dc425ebf32ac4485bf86d928365b6",
          "message": "Experiment rt sudo",
          "timestamp": "2023-08-15T14:25:02+03:00",
          "tree_id": "02143fed47c04344cc6c9642bc07111ce871053f",
          "url": "https://github.com/duckstax/actor-zeta/commit/490632efe51dc425ebf32ac4485bf86d928365b6"
        },
        "date": 1692099134703,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 29349.423141968142,
            "unit": "ns/iter",
            "extra": "iterations: 164973\ncpu: 8774.361259115129 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 30255.45012000066,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9530.11 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 30602.58696000005,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9356.846999999998 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 29384.319572757922,
            "unit": "ns/iter",
            "extra": "iterations: 65162\ncpu: 9783.620821951441 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 30080.341949439124,
            "unit": "ns/iter",
            "extra": "iterations: 73970\ncpu: 8938.28173583885 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 34254.98007459952,
            "unit": "ns/iter",
            "extra": "iterations: 83110\ncpu: 9469.10600409096 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 30045.28509751396,
            "unit": "ns/iter",
            "extra": "iterations: 295085\ncpu: 9244.360099632311 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 30067.2194925079,
            "unit": "ns/iter",
            "extra": "iterations: 76809\ncpu: 9109.63558957935 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 30615.74132794899,
            "unit": "ns/iter",
            "extra": "iterations: 70831\ncpu: 9409.197950050106 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 30776.840930902545,
            "unit": "ns/iter",
            "extra": "iterations: 62520\ncpu: 10103.93474088289 ns\nthreads: 1"
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
          "id": "88fdd486465e72f0ba6fdbacb36d637519982659",
          "message": "install git and checkout in container : git config safe dir 2",
          "timestamp": "2023-08-15T16:04:18+03:00",
          "tree_id": "a81fd4e4b3527f88adc1c100b561e1ed0bf34c24",
          "url": "https://github.com/duckstax/actor-zeta/commit/88fdd486465e72f0ba6fdbacb36d637519982659"
        },
        "date": 1692105400267,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 24674.054000000182,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7805.033 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 24521.592758752315,
            "unit": "ns/iter",
            "extra": "iterations: 88714\ncpu: 7539.3906260567655 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 24311.712428138722,
            "unit": "ns/iter",
            "extra": "iterations: 95670\ncpu: 7552.70722274485 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 18987.687263599182,
            "unit": "ns/iter",
            "extra": "iterations: 87246\ncpu: 6369.309767783047 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 17499.70488226269,
            "unit": "ns/iter",
            "extra": "iterations: 156280\ncpu: 5667.691323265932 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 24374.802785057695,
            "unit": "ns/iter",
            "extra": "iterations: 88903\ncpu: 7901.299168756952 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 24992.703860592355,
            "unit": "ns/iter",
            "extra": "iterations: 97498\ncpu: 7618.144987589483 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 23875.466077718742,
            "unit": "ns/iter",
            "extra": "iterations: 89425\ncpu: 7691.590718479172 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 24221.049459999904,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7869.431000000002 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 23840.3217364494,
            "unit": "ns/iter",
            "extra": "iterations: 81085\ncpu: 7523.615958562012 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}