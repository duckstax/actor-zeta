window.BENCHMARK_DATA = {
  "lastUpdate": 1692105486092,
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
        "date": 1692094359130,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28019.05009677934,
            "unit": "ns/iter",
            "extra": "iterations: 74396\ncpu: 8836.37023495887 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28648.01480094355,
            "unit": "ns/iter",
            "extra": "iterations: 77968\ncpu: 9090.276780217526 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28981.78781999416,
            "unit": "ns/iter",
            "extra": "iterations: 108752\ncpu: 9147.380278063849 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28946.047091027747,
            "unit": "ns/iter",
            "extra": "iterations: 78911\ncpu: 9169.976302416648 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28829.348675800375,
            "unit": "ns/iter",
            "extra": "iterations: 76650\ncpu: 9105.12589693411 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28995.271045414203,
            "unit": "ns/iter",
            "extra": "iterations: 75836\ncpu: 9001.58368057387 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28862.77868381255,
            "unit": "ns/iter",
            "extra": "iterations: 76524\ncpu: 9290.193926088543 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28807.14754286556,
            "unit": "ns/iter",
            "extra": "iterations: 78384\ncpu: 9172.591345172486 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28824.48806593165,
            "unit": "ns/iter",
            "extra": "iterations: 74744\ncpu: 9016.714385101153 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28789.4822893306,
            "unit": "ns/iter",
            "extra": "iterations: 75830\ncpu: 9139.641302914411 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Benchmark actors_ping_pong_scheduled gcc-9 20.04 Debug c++-14": [
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
        "date": 1692095616229,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 33692.28241202126,
            "unit": "ns/iter",
            "extra": "iterations: 76268\ncpu: 9958.771699795458 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 37793.704795424055,
            "unit": "ns/iter",
            "extra": "iterations: 68190\ncpu: 10896.033142689545 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 34615.644935165525,
            "unit": "ns/iter",
            "extra": "iterations: 108276\ncpu: 10036.841959436995 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 36810.71561975669,
            "unit": "ns/iter",
            "extra": "iterations: 67357\ncpu: 10700.46468815417 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 35013.17910318326,
            "unit": "ns/iter",
            "extra": "iterations: 69178\ncpu: 10067.85538755095 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 30494.010866457294,
            "unit": "ns/iter",
            "extra": "iterations: 69940\ncpu: 8795.328853302832 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 36226.77931760384,
            "unit": "ns/iter",
            "extra": "iterations: 68406\ncpu: 10371.518580241493 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 40324.57137994217,
            "unit": "ns/iter",
            "extra": "iterations: 61691\ncpu: 11142.763125901673 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 37608.75605232003,
            "unit": "ns/iter",
            "extra": "iterations: 62538\ncpu: 10485.949342799584 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 35664.44585952191,
            "unit": "ns/iter",
            "extra": "iterations: 72709\ncpu: 10156.533579061737 ns\nthreads: 1"
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
        "date": 1692098994974,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28729.177260519198,
            "unit": "ns/iter",
            "extra": "iterations: 71488\ncpu: 9668.687052372428 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 24487.362974834658,
            "unit": "ns/iter",
            "extra": "iterations: 131651\ncpu: 8035.191529118652 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28674.93339053694,
            "unit": "ns/iter",
            "extra": "iterations: 72257\ncpu: 9638.918028703101 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28637.215165560578,
            "unit": "ns/iter",
            "extra": "iterations: 71847\ncpu: 9622.283463470989 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28538.588590802457,
            "unit": "ns/iter",
            "extra": "iterations: 74624\ncpu: 9492.720840480277 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28730.37609238832,
            "unit": "ns/iter",
            "extra": "iterations: 77239\ncpu: 9574.467561724 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28385.690235826358,
            "unit": "ns/iter",
            "extra": "iterations: 74292\ncpu: 9407.175738975937 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28717.508503542253,
            "unit": "ns/iter",
            "extra": "iterations: 71970\ncpu: 9660.140336251216 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28813.344838945817,
            "unit": "ns/iter",
            "extra": "iterations: 69821\ncpu: 9728.14196301971 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28577.051695593404,
            "unit": "ns/iter",
            "extra": "iterations: 72482\ncpu: 9511.780855936644 ns\nthreads: 1"
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
        "date": 1692105484983,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 33499.50424379276,
            "unit": "ns/iter",
            "extra": "iterations: 66450\ncpu: 10984.80963130173 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 35050.67990977803,
            "unit": "ns/iter",
            "extra": "iterations: 75813\ncpu: 11181.97406777202 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 34221.89322605008,
            "unit": "ns/iter",
            "extra": "iterations: 63508\ncpu: 11047.406625936888 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 31049.26491378636,
            "unit": "ns/iter",
            "extra": "iterations: 64085\ncpu: 10065.260201295152 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 31792.77901999967,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 10127.423999999997 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 35548.269133950256,
            "unit": "ns/iter",
            "extra": "iterations: 59985\ncpu: 10994.658664666174 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 34674.69146333476,
            "unit": "ns/iter",
            "extra": "iterations: 61312\ncpu: 11701.820198329859 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 35108.32578118817,
            "unit": "ns/iter",
            "extra": "iterations: 63205\ncpu: 11071.560794240966 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 35497.009378989686,
            "unit": "ns/iter",
            "extra": "iterations: 61094\ncpu: 11167.579467705511 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 36019.17835608723,
            "unit": "ns/iter",
            "extra": "iterations: 64018\ncpu: 11175.466275110135 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}