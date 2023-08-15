window.BENCHMARK_DATA = {
  "lastUpdate": 1692099254648,
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
        "date": 1692094692200,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 31294.061960263334,
            "unit": "ns/iter",
            "extra": "iterations: 66236\ncpu: 9049.128872516456 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 32168.074319999963,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9428.314999999999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 34785.47800789432,
            "unit": "ns/iter",
            "extra": "iterations: 63591\ncpu: 10750.62037080719 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 35616.03523170338,
            "unit": "ns/iter",
            "extra": "iterations: 78225\ncpu: 10757.903483541071 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 35250.77535413367,
            "unit": "ns/iter",
            "extra": "iterations: 65512\ncpu: 10606.383563316645 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 34223.60410706591,
            "unit": "ns/iter",
            "extra": "iterations: 66763\ncpu: 10309.635576591823 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 36835.93863308636,
            "unit": "ns/iter",
            "extra": "iterations: 64481\ncpu: 10654.813045703379 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 36424.69124624083,
            "unit": "ns/iter",
            "extra": "iterations: 64498\ncpu: 10780.545133182424 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 36251.24221469705,
            "unit": "ns/iter",
            "extra": "iterations: 63485\ncpu: 10780.412695912417 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 34523.08724340194,
            "unit": "ns/iter",
            "extra": "iterations: 66836\ncpu: 10519.030163384989 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Benchmark actors_ping_pong_scheduled gcc-9 22.04 Debug c++-14": [
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
        "date": 1692095878076,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 36478.86520738593,
            "unit": "ns/iter",
            "extra": "iterations: 94293\ncpu: 11358.846361872038 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 34074.18100110228,
            "unit": "ns/iter",
            "extra": "iterations: 63530\ncpu: 11171.08924917362 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 33699.20986527386,
            "unit": "ns/iter",
            "extra": "iterations: 63536\ncpu: 10951.090720221604 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 34134.39567887838,
            "unit": "ns/iter",
            "extra": "iterations: 64474\ncpu: 11195.55945032106 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 32123.728506320473,
            "unit": "ns/iter",
            "extra": "iterations: 77453\ncpu: 9835.555756394198 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 36864.09250214946,
            "unit": "ns/iter",
            "extra": "iterations: 61631\ncpu: 11268.05016955753 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 36936.57669475786,
            "unit": "ns/iter",
            "extra": "iterations: 61823\ncpu: 11639.245911715703 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 36624.47564948447,
            "unit": "ns/iter",
            "extra": "iterations: 61087\ncpu: 12165.532764745358 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 37474.773626340706,
            "unit": "ns/iter",
            "extra": "iterations: 65118\ncpu: 11062.474277465524 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 36911.40018417196,
            "unit": "ns/iter",
            "extra": "iterations: 56469\ncpu: 11247.80499034868 ns\nthreads: 1"
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
        "date": 1692099254095,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 29960.331456767628,
            "unit": "ns/iter",
            "extra": "iterations: 74782\ncpu: 9550.39849161563 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 30063.149665339366,
            "unit": "ns/iter",
            "extra": "iterations: 70818\ncpu: 9658.352396283433 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 23347.29051719442,
            "unit": "ns/iter",
            "extra": "iterations: 92325\ncpu: 7306.856214459786 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 30326.850115780948,
            "unit": "ns/iter",
            "extra": "iterations: 72983\ncpu: 9700.785114341692 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 30312.205296329612,
            "unit": "ns/iter",
            "extra": "iterations: 74731\ncpu: 9564.097897793417 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 30370.638302869855,
            "unit": "ns/iter",
            "extra": "iterations: 72381\ncpu: 9878.271922189528 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 30124.88734696141,
            "unit": "ns/iter",
            "extra": "iterations: 72204\ncpu: 9662.380200542904 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 29758.07546567437,
            "unit": "ns/iter",
            "extra": "iterations: 72046\ncpu: 9674.924353885019 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 30332.925587314898,
            "unit": "ns/iter",
            "extra": "iterations: 85644\ncpu: 9780.351221334826 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 29920.60447480814,
            "unit": "ns/iter",
            "extra": "iterations: 71869\ncpu: 9472.113150315156 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}