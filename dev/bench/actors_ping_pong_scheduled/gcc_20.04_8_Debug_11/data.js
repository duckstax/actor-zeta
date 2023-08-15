window.BENCHMARK_DATA = {
  "lastUpdate": 1692099830943,
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
        "date": 1692094349108,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 23744.829527354716,
            "unit": "ns/iter",
            "extra": "iterations: 115520\ncpu: 7340.23978531856 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 29042.81594337126,
            "unit": "ns/iter",
            "extra": "iterations: 75580\ncpu: 9228.900502778515 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28933.41979644312,
            "unit": "ns/iter",
            "extra": "iterations: 75458\ncpu: 9110.294468446025 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28507.50643407541,
            "unit": "ns/iter",
            "extra": "iterations: 76701\ncpu: 9043.848189723733 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28759.193135864658,
            "unit": "ns/iter",
            "extra": "iterations: 76164\ncpu: 9105.846594191486 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28613.83749268548,
            "unit": "ns/iter",
            "extra": "iterations: 76895\ncpu: 9061.513752519664 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28793.090528505214,
            "unit": "ns/iter",
            "extra": "iterations: 76915\ncpu: 9154.331404797498 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 24126.12927502904,
            "unit": "ns/iter",
            "extra": "iterations: 76403\ncpu: 7587.5384474431585 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 29024.097721647155,
            "unit": "ns/iter",
            "extra": "iterations: 75142\ncpu: 9183.465971094722 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28065.51111368992,
            "unit": "ns/iter",
            "extra": "iterations: 77562\ncpu: 8956.405198421913 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Benchmark actors_ping_pong_scheduled gcc-8 20.04 Debug c++-11": [
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
        "date": 1692095610462,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 30971.50272237503,
            "unit": "ns/iter",
            "extra": "iterations: 69241\ncpu: 9885.700668678963 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 26616.51540557366,
            "unit": "ns/iter",
            "extra": "iterations: 128460\ncpu: 8092.57044994551 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 31039.176533406335,
            "unit": "ns/iter",
            "extra": "iterations: 73040\ncpu: 9835.855695509308 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 33916.42085379673,
            "unit": "ns/iter",
            "extra": "iterations: 71469\ncpu: 10122.124277658844 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 32323.0615613181,
            "unit": "ns/iter",
            "extra": "iterations: 67981\ncpu: 9813.0021623689 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 30784.614505372996,
            "unit": "ns/iter",
            "extra": "iterations: 68678\ncpu: 9825.72293893241 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 33198.755713476945,
            "unit": "ns/iter",
            "extra": "iterations: 67122\ncpu: 10042.235034712907 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 31303.360225479464,
            "unit": "ns/iter",
            "extra": "iterations: 66525\ncpu: 9856.360766629083 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 33140.67398133671,
            "unit": "ns/iter",
            "extra": "iterations: 64619\ncpu: 10417.700676271696 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 32232.511541026928,
            "unit": "ns/iter",
            "extra": "iterations: 67455\ncpu: 10130.782002816706 ns\nthreads: 1"
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
        "date": 1692098985757,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 29506.559614353773,
            "unit": "ns/iter",
            "extra": "iterations: 72709\ncpu: 9890.95847831768 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 29219.59563358901,
            "unit": "ns/iter",
            "extra": "iterations: 71821\ncpu: 9837.667256095014 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28516.46579042845,
            "unit": "ns/iter",
            "extra": "iterations: 104766\ncpu: 9462.315064047498 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 29069.59570880594,
            "unit": "ns/iter",
            "extra": "iterations: 71169\ncpu: 9655.438463375913 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 29142.207653371108,
            "unit": "ns/iter",
            "extra": "iterations: 72308\ncpu: 9767.491840460254 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28876.792787235936,
            "unit": "ns/iter",
            "extra": "iterations: 72954\ncpu: 9669.807001672278 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28980.512245012902,
            "unit": "ns/iter",
            "extra": "iterations: 70886\ncpu: 9697.912140620141 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 29076.32325841022,
            "unit": "ns/iter",
            "extra": "iterations: 74343\ncpu: 9571.34901739235 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28908.04262357362,
            "unit": "ns/iter",
            "extra": "iterations: 73762\ncpu: 9709.30018166536 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28944.505511831165,
            "unit": "ns/iter",
            "extra": "iterations: 77379\ncpu: 9556.0462140891 ns\nthreads: 1"
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
          "id": "c2c6dba33a83f1793a9af1ee3ee1557db685635e",
          "message": "Experiment inst git before actions checkout",
          "timestamp": "2023-08-15T14:38:13+03:00",
          "tree_id": "e35e31d21181071d5b4bb877297db85cc355e0ab",
          "url": "https://github.com/duckstax/actor-zeta/commit/c2c6dba33a83f1793a9af1ee3ee1557db685635e"
        },
        "date": 1692099830096,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 29094.258477915042,
            "unit": "ns/iter",
            "extra": "iterations: 62191\ncpu: 9004.275538261163 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 34951.069319762835,
            "unit": "ns/iter",
            "extra": "iterations: 63272\ncpu: 10839.113667973195 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 35510.75509794413,
            "unit": "ns/iter",
            "extra": "iterations: 59779\ncpu: 11073.305006774954 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 35163.402727958644,
            "unit": "ns/iter",
            "extra": "iterations: 84752\ncpu: 11276.398197092696 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 30724.50265999919,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9519.627 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 36195.59765650528,
            "unit": "ns/iter",
            "extra": "iterations: 61532\ncpu: 11479.792628225952 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 35001.78132500443,
            "unit": "ns/iter",
            "extra": "iterations: 64996\ncpu: 11198.070650501575 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 34995.967772635406,
            "unit": "ns/iter",
            "extra": "iterations: 60942\ncpu: 11205.608611466647 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 34645.43199697829,
            "unit": "ns/iter",
            "extra": "iterations: 63556\ncpu: 11040.06702750331 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 35669.239590070174,
            "unit": "ns/iter",
            "extra": "iterations: 60303\ncpu: 11407.502114322653 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}