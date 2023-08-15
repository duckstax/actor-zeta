window.BENCHMARK_DATA = {
  "lastUpdate": 1692117603265,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-6 18.04 Debug c++-17": [
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
        "date": 1692110807076,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 33486.25373000004,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 10550.576 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 25863.630301237517,
            "unit": "ns/iter",
            "extra": "iterations: 87904\ncpu: 8284.759510374954 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 33669.59538345388,
            "unit": "ns/iter",
            "extra": "iterations: 63554\ncpu: 10765.578877804704 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 32746.803776884375,
            "unit": "ns/iter",
            "extra": "iterations: 69793\ncpu: 10758.720788617773 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 32775.53815046111,
            "unit": "ns/iter",
            "extra": "iterations: 67260\ncpu: 10737.224204579248 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 32802.35435485814,
            "unit": "ns/iter",
            "extra": "iterations: 65536\ncpu: 10799.78179931641 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 32672.793849015954,
            "unit": "ns/iter",
            "extra": "iterations: 65583\ncpu: 10740.011893326018 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 33996.43633838037,
            "unit": "ns/iter",
            "extra": "iterations: 66233\ncpu: 10839.560340011772 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 33937.05783459644,
            "unit": "ns/iter",
            "extra": "iterations: 67036\ncpu: 11473.916999821 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 33408.21199118923,
            "unit": "ns/iter",
            "extra": "iterations: 61295\ncpu: 11257.120482910514 ns\nthreads: 1"
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
        "date": 1692112598880,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 27906.14165192671,
            "unit": "ns/iter",
            "extra": "iterations: 107983\ncpu: 9256.162544104165 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28590.02228710356,
            "unit": "ns/iter",
            "extra": "iterations: 75694\ncpu: 9584.92218669908 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28333.015339634214,
            "unit": "ns/iter",
            "extra": "iterations: 73535\ncpu: 9583.352145236964 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27926.142447882758,
            "unit": "ns/iter",
            "extra": "iterations: 107162\ncpu: 9346.92708236129 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 27908.634655835885,
            "unit": "ns/iter",
            "extra": "iterations: 75589\ncpu: 9354.443106801247 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27905.271079527414,
            "unit": "ns/iter",
            "extra": "iterations: 75144\ncpu: 9297.955924624723 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27730.46582151342,
            "unit": "ns/iter",
            "extra": "iterations: 75647\ncpu: 9323.759038692886 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28173.507507144393,
            "unit": "ns/iter",
            "extra": "iterations: 74529\ncpu: 9515.073327161235 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27814.92722768248,
            "unit": "ns/iter",
            "extra": "iterations: 75482\ncpu: 9309.918921067274 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27837.085815009697,
            "unit": "ns/iter",
            "extra": "iterations: 75453\ncpu: 9276.26204392136 ns\nthreads: 1"
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
        "date": 1692117601561,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 39235.194278632545,
            "unit": "ns/iter",
            "extra": "iterations: 61314\ncpu: 12023.443259288257 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 39293.236049027684,
            "unit": "ns/iter",
            "extra": "iterations: 91947\ncpu: 11865.5551567751 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 35744.14290073813,
            "unit": "ns/iter",
            "extra": "iterations: 58985\ncpu: 10852.840552682892 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 38494.21840215088,
            "unit": "ns/iter",
            "extra": "iterations: 58754\ncpu: 11801.896041120606 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 39190.670300673504,
            "unit": "ns/iter",
            "extra": "iterations: 57604\ncpu: 11956.857162697037 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 39593.608195026834,
            "unit": "ns/iter",
            "extra": "iterations: 60012\ncpu: 12361.087782443517 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 41188.78729756978,
            "unit": "ns/iter",
            "extra": "iterations: 59280\ncpu: 12171.356275303639 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 38527.27351867437,
            "unit": "ns/iter",
            "extra": "iterations: 60537\ncpu: 11882.33642235327 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 37826.05531522997,
            "unit": "ns/iter",
            "extra": "iterations: 60797\ncpu: 11384.139020017446 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 37774.38134697272,
            "unit": "ns/iter",
            "extra": "iterations: 58650\ncpu: 11837.111679454385 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}