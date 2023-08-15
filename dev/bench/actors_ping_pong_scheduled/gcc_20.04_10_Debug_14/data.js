window.BENCHMARK_DATA = {
  "lastUpdate": 1692105365112,
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
        "date": 1692094361897,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28663.91344652757,
            "unit": "ns/iter",
            "extra": "iterations: 92879\ncpu: 8932.482046533662 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 29412.041545333705,
            "unit": "ns/iter",
            "extra": "iterations: 75893\ncpu: 9248.812143412437 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 29345.439733180137,
            "unit": "ns/iter",
            "extra": "iterations: 73158\ncpu: 9387.589873971403 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 29255.168097282127,
            "unit": "ns/iter",
            "extra": "iterations: 74094\ncpu: 9272.28115636894 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 21637.557063278084,
            "unit": "ns/iter",
            "extra": "iterations: 79885\ncpu: 6613.864930838082 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 29216.688966116166,
            "unit": "ns/iter",
            "extra": "iterations: 82872\ncpu: 9193.576841393962 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 29241.99190721748,
            "unit": "ns/iter",
            "extra": "iterations: 73893\ncpu: 9289.104515989338 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 26523.483562866553,
            "unit": "ns/iter",
            "extra": "iterations: 78420\ncpu: 8333.874011731703 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 29345.54486922624,
            "unit": "ns/iter",
            "extra": "iterations: 72377\ncpu: 9453.305608135177 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 29354.15745580603,
            "unit": "ns/iter",
            "extra": "iterations: 76142\ncpu: 9285.071314123612 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Benchmark actors_ping_pong_scheduled gcc-10 20.04 Debug c++-14": [
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
        "date": 1692095585894,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 23701.40877017519,
            "unit": "ns/iter",
            "extra": "iterations: 71994\ncpu: 7476.149401339 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28935.32838293315,
            "unit": "ns/iter",
            "extra": "iterations: 104436\ncpu: 9512.041824658163 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 29068.60539542109,
            "unit": "ns/iter",
            "extra": "iterations: 69837\ncpu: 9606.424960980572 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 29050.94875474388,
            "unit": "ns/iter",
            "extra": "iterations: 74563\ncpu: 9518.140364523962 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28767.629501413943,
            "unit": "ns/iter",
            "extra": "iterations: 71061\ncpu: 9408.052236810627 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28877.679496420158,
            "unit": "ns/iter",
            "extra": "iterations: 83244\ncpu: 9556.151794723946 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 29059.12488871799,
            "unit": "ns/iter",
            "extra": "iterations: 75259\ncpu: 9445.235785753199 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28919.550961662197,
            "unit": "ns/iter",
            "extra": "iterations: 77470\ncpu: 9616.88782754615 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 29092.154625404975,
            "unit": "ns/iter",
            "extra": "iterations: 75615\ncpu: 9519.47364940818 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28967.88035161522,
            "unit": "ns/iter",
            "extra": "iterations: 74627\ncpu: 9538.169831294304 ns\nthreads: 1"
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
        "date": 1692099053184,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 38653.6874153585,
            "unit": "ns/iter",
            "extra": "iterations: 59811\ncpu: 11035.996723010818 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 37420.26257164717,
            "unit": "ns/iter",
            "extra": "iterations: 67692\ncpu: 10556.813212787329 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 32978.96410667795,
            "unit": "ns/iter",
            "extra": "iterations: 64831\ncpu: 10285.565547346177 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 33834.76723643313,
            "unit": "ns/iter",
            "extra": "iterations: 66226\ncpu: 10381.061818621085 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 27229.021241747676,
            "unit": "ns/iter",
            "extra": "iterations: 119058\ncpu: 8407.770162441837 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 32926.46022957678,
            "unit": "ns/iter",
            "extra": "iterations: 71523\ncpu: 10008.591641849478 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 32176.20808706747,
            "unit": "ns/iter",
            "extra": "iterations: 73599\ncpu: 9932.201524477236 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 33503.58698203995,
            "unit": "ns/iter",
            "extra": "iterations: 68152\ncpu: 10595.700786477282 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 33576.636533865916,
            "unit": "ns/iter",
            "extra": "iterations: 65687\ncpu: 10108.752112290113 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 33686.51577858142,
            "unit": "ns/iter",
            "extra": "iterations: 63789\ncpu: 10753.827462415162 ns\nthreads: 1"
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
        "date": 1692105364545,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 23121.096814216235,
            "unit": "ns/iter",
            "extra": "iterations: 102361\ncpu: 6996.7536464083005 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 29305.214378223543,
            "unit": "ns/iter",
            "extra": "iterations: 86478\ncpu: 9246.071833298643 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 29520.765687678173,
            "unit": "ns/iter",
            "extra": "iterations: 77529\ncpu: 9272.727624501804 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 29172.846561952425,
            "unit": "ns/iter",
            "extra": "iterations: 76526\ncpu: 9188.18832814991 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 29163.095191183842,
            "unit": "ns/iter",
            "extra": "iterations: 76131\ncpu: 9211.47627116418 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 29361.795399353796,
            "unit": "ns/iter",
            "extra": "iterations: 74946\ncpu: 9309.021161903236 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 29396.86342622834,
            "unit": "ns/iter",
            "extra": "iterations: 107290\ncpu: 9311.519246900918 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 29405.51224214424,
            "unit": "ns/iter",
            "extra": "iterations: 82992\ncpu: 9189.86769809138 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 29173.696252229696,
            "unit": "ns/iter",
            "extra": "iterations: 75138\ncpu: 9216.508291410477 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 29187.417209320192,
            "unit": "ns/iter",
            "extra": "iterations: 79701\ncpu: 9183.799450446028 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}