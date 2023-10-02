window.BENCHMARK_DATA = {
  "lastUpdate": 1696256501923,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-4.9 16.04 Release c++-11": [
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
        "date": 1692110066494,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 26076.152974538483,
            "unit": "ns/iter",
            "extra": "iterations: 82164\ncpu: 8745.934959349594 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 24880.203333290872,
            "unit": "ns/iter",
            "extra": "iterations: 77941\ncpu: 8427.066627320664 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 19912.49402834854,
            "unit": "ns/iter",
            "extra": "iterations: 82473\ncpu: 6587.364349544702 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 20710.272311593337,
            "unit": "ns/iter",
            "extra": "iterations: 78076\ncpu: 6783.665915262056 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 25886.81284038826,
            "unit": "ns/iter",
            "extra": "iterations: 163967\ncpu: 8764.467240359343 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 25777.666414734234,
            "unit": "ns/iter",
            "extra": "iterations: 86002\ncpu: 8442.622264598489 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 26217.60509127713,
            "unit": "ns/iter",
            "extra": "iterations: 79155\ncpu: 8495.729897037454 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 25490.782219999346,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8374.147 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 26694.036023265508,
            "unit": "ns/iter",
            "extra": "iterations: 81836\ncpu: 8546.271811916513 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 25269.927680560722,
            "unit": "ns/iter",
            "extra": "iterations: 94691\ncpu: 8397.431646090978 ns\nthreads: 1"
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
        "date": 1692111942889,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 36485.327653069624,
            "unit": "ns/iter",
            "extra": "iterations: 70654\ncpu: 10029.61332691709 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 34294.16086595744,
            "unit": "ns/iter",
            "extra": "iterations: 66285\ncpu: 10582.440974579467 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 24175.922634988325,
            "unit": "ns/iter",
            "extra": "iterations: 66839\ncpu: 7745.124852256917 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 34007.580483349906,
            "unit": "ns/iter",
            "extra": "iterations: 73363\ncpu: 10018.7683164538 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 34950.96624837176,
            "unit": "ns/iter",
            "extra": "iterations: 70604\ncpu: 10664.147923630395 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 34850.159782464296,
            "unit": "ns/iter",
            "extra": "iterations: 67667\ncpu: 10199.957143068268 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 34063.54448108237,
            "unit": "ns/iter",
            "extra": "iterations: 58834\ncpu: 10260.152292891862 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 31088.214925931596,
            "unit": "ns/iter",
            "extra": "iterations: 69396\ncpu: 9665.32653178857 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 33054.66719595852,
            "unit": "ns/iter",
            "extra": "iterations: 69275\ncpu: 9890.367376398419 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 31463.44199242443,
            "unit": "ns/iter",
            "extra": "iterations: 69965\ncpu: 9810.998356321012 ns\nthreads: 1"
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
        "date": 1692116724986,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22060.815090000004,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7882.772000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 21871.677997409744,
            "unit": "ns/iter",
            "extra": "iterations: 88785\ncpu: 7661.280621726644 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 18529.32971893426,
            "unit": "ns/iter",
            "extra": "iterations: 88627\ncpu: 6626.0123890010955 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 21944.489112985826,
            "unit": "ns/iter",
            "extra": "iterations: 88454\ncpu: 7729.674180930201 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 22241.265906578647,
            "unit": "ns/iter",
            "extra": "iterations: 91393\ncpu: 7938.86293260972 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 21890.221518029197,
            "unit": "ns/iter",
            "extra": "iterations: 92462\ncpu: 7799.7966732279165 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22322.023781295906,
            "unit": "ns/iter",
            "extra": "iterations: 85193\ncpu: 7803.055415351029 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 21813.03941503247,
            "unit": "ns/iter",
            "extra": "iterations: 91082\ncpu: 7696.318701829115 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 22212.498510985795,
            "unit": "ns/iter",
            "extra": "iterations: 90664\ncpu: 7863.013985705462 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 22152.81202931387,
            "unit": "ns/iter",
            "extra": "iterations: 88966\ncpu: 7873.677584695277 ns\nthreads: 1"
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
        "date": 1696256500864,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 18676.503462991768,
            "unit": "ns/iter",
            "extra": "iterations: 141063\ncpu: 6794.394703075931 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 21859.89056419761,
            "unit": "ns/iter",
            "extra": "iterations: 84031\ncpu: 7774.532017945759 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 22215.84200263716,
            "unit": "ns/iter",
            "extra": "iterations: 90261\ncpu: 7972.5773035973425 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 22312.981164754096,
            "unit": "ns/iter",
            "extra": "iterations: 87761\ncpu: 7973.275144996069 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 21959.33590096195,
            "unit": "ns/iter",
            "extra": "iterations: 90875\ncpu: 7874.269050894084 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 19175.06583999966,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 6966.040999999992 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22176.56451243238,
            "unit": "ns/iter",
            "extra": "iterations: 87270\ncpu: 7997.22814254612 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 21791.040504616172,
            "unit": "ns/iter",
            "extra": "iterations: 84262\ncpu: 7796.550046284212 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 22128.141196823788,
            "unit": "ns/iter",
            "extra": "iterations: 90172\ncpu: 7966.643747504774 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 22344.957006539382,
            "unit": "ns/iter",
            "extra": "iterations: 84571\ncpu: 8033.3873313547265 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}