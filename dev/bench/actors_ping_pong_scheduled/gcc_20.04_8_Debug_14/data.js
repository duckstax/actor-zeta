window.BENCHMARK_DATA = {
  "lastUpdate": 1692105484609,
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
        "date": 1692094412591,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 31482.65977781214,
            "unit": "ns/iter",
            "extra": "iterations: 77952\ncpu: 10103.84467364532 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 33921.3647370032,
            "unit": "ns/iter",
            "extra": "iterations: 61617\ncpu: 11135.657367285003 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 33313.42219245282,
            "unit": "ns/iter",
            "extra": "iterations: 62706\ncpu: 10964.392562115272 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 33468.18449167959,
            "unit": "ns/iter",
            "extra": "iterations: 62431\ncpu: 10967.208598292511 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 33307.92650940265,
            "unit": "ns/iter",
            "extra": "iterations: 96992\ncpu: 10909.51006268558 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 33228.09724544763,
            "unit": "ns/iter",
            "extra": "iterations: 74749\ncpu: 10801.157206116464 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 33281.947588148156,
            "unit": "ns/iter",
            "extra": "iterations: 63955\ncpu: 10824.678289422252 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 33419.89899499908,
            "unit": "ns/iter",
            "extra": "iterations: 63383\ncpu: 10834.18897811716 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 33441.65900509681,
            "unit": "ns/iter",
            "extra": "iterations: 63564\ncpu: 10952.032597067524 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 33116.90832320687,
            "unit": "ns/iter",
            "extra": "iterations: 64182\ncpu: 10749.467140319703 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Benchmark actors_ping_pong_scheduled gcc-8 20.04 Debug c++-14": [
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
        "date": 1692095551305,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 30621.497430798507,
            "unit": "ns/iter",
            "extra": "iterations: 113654\ncpu: 9200.551674380135 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28044.794862583225,
            "unit": "ns/iter",
            "extra": "iterations: 77938\ncpu: 8809.901460134983 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 23224.44361999999,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 6997.236 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27939.090479857336,
            "unit": "ns/iter",
            "extra": "iterations: 79211\ncpu: 8901.128631124466 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28084.254469621803,
            "unit": "ns/iter",
            "extra": "iterations: 76964\ncpu: 8758.59102957227 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 25113.915669579947,
            "unit": "ns/iter",
            "extra": "iterations: 79983\ncpu: 7893.777427703389 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27964.762360056655,
            "unit": "ns/iter",
            "extra": "iterations: 130946\ncpu: 8843.42171582179 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 26547.322661117745,
            "unit": "ns/iter",
            "extra": "iterations: 79771\ncpu: 8370.810194180844 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28184.36277594756,
            "unit": "ns/iter",
            "extra": "iterations: 80722\ncpu: 8737.69852084933 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27927.062976462545,
            "unit": "ns/iter",
            "extra": "iterations: 80935\ncpu: 8637.841477729033 ns\nthreads: 1"
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
        "date": 1692099053428,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 37457.26088029953,
            "unit": "ns/iter",
            "extra": "iterations: 72907\ncpu: 11563.794971676247 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 36644.9060880827,
            "unit": "ns/iter",
            "extra": "iterations: 98816\ncpu: 11601.915681670987 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 37522.93228373612,
            "unit": "ns/iter",
            "extra": "iterations: 63707\ncpu: 11824.253221780966 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 36641.062248996685,
            "unit": "ns/iter",
            "extra": "iterations: 59262\ncpu: 11533.05659613243 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 36128.52232490204,
            "unit": "ns/iter",
            "extra": "iterations: 61680\ncpu: 11557.563229571988 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 36374.67586546622,
            "unit": "ns/iter",
            "extra": "iterations: 62943\ncpu: 11262.370716362424 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 32689.58196600127,
            "unit": "ns/iter",
            "extra": "iterations: 60885\ncpu: 9983.004023979636 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 37022.085552149634,
            "unit": "ns/iter",
            "extra": "iterations: 116128\ncpu: 11161.422740424356 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 36450.885587021156,
            "unit": "ns/iter",
            "extra": "iterations: 61514\ncpu: 11543.399876450872 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 35643.074112341594,
            "unit": "ns/iter",
            "extra": "iterations: 60975\ncpu: 11343.690036900363 ns\nthreads: 1"
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
        "date": 1692105482229,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 39353.98221757263,
            "unit": "ns/iter",
            "extra": "iterations: 56404\ncpu: 11818.670661655202 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 41619.59019760164,
            "unit": "ns/iter",
            "extra": "iterations: 54048\ncpu: 12546.893502072235 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 41065.14386417773,
            "unit": "ns/iter",
            "extra": "iterations: 90648\ncpu: 12495.752802047478 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 41410.416227099406,
            "unit": "ns/iter",
            "extra": "iterations: 74505\ncpu: 12247.917589423525 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 39557.14457108576,
            "unit": "ns/iter",
            "extra": "iterations: 58345\ncpu: 11994.890736138486 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 43571.09335986988,
            "unit": "ns/iter",
            "extra": "iterations: 55270\ncpu: 12836.17152162113 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 43107.84236799289,
            "unit": "ns/iter",
            "extra": "iterations: 54088\ncpu: 12827.137257802087 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 44865.13269329417,
            "unit": "ns/iter",
            "extra": "iterations: 68225\ncpu: 12759.693660681567 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 46376.36262768942,
            "unit": "ns/iter",
            "extra": "iterations: 54527\ncpu: 12173.381994241396 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 40491.74808051475,
            "unit": "ns/iter",
            "extra": "iterations: 57828\ncpu: 11944.851974821864 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}