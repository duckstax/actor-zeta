window.BENCHMARK_DATA = {
  "lastUpdate": 1696258842133,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled gcc-12 22.04 Release c++-17": [
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
        "date": 1692111360842,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 33105.02071999963,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 10117.369999999999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 25335.65407936711,
            "unit": "ns/iter",
            "extra": "iterations: 103570\ncpu: 8061.52264169161 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 31708.20244999959,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9713.463999999998 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 35099.46154074853,
            "unit": "ns/iter",
            "extra": "iterations: 67279\ncpu: 10288.259337980648 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 32909.89431115574,
            "unit": "ns/iter",
            "extra": "iterations: 66147\ncpu: 9905.381952318321 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 31530.236678461944,
            "unit": "ns/iter",
            "extra": "iterations: 66415\ncpu: 9632.710983964464 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 30236.083291863928,
            "unit": "ns/iter",
            "extra": "iterations: 74353\ncpu: 9240.681613384799 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 30458.151890960242,
            "unit": "ns/iter",
            "extra": "iterations: 66765\ncpu: 9682.29161986071 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 31815.514994881876,
            "unit": "ns/iter",
            "extra": "iterations: 78160\ncpu: 9289.834953940635 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28822.743370665805,
            "unit": "ns/iter",
            "extra": "iterations: 74555\ncpu: 9177.886124337743 ns\nthreads: 1"
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
        "date": 1692113248316,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22611.05575999977,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7315.8780000000015 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28114.79564924059,
            "unit": "ns/iter",
            "extra": "iterations: 68172\ncpu: 9045.857536818634 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 26053.700915245925,
            "unit": "ns/iter",
            "extra": "iterations: 83147\ncpu: 8306.929895245768 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25977.765584675708,
            "unit": "ns/iter",
            "extra": "iterations: 62385\ncpu: 8718.570169111164 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 25095.28119689785,
            "unit": "ns/iter",
            "extra": "iterations: 78269\ncpu: 8842.192949954644 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 24996.021847282525,
            "unit": "ns/iter",
            "extra": "iterations: 79598\ncpu: 8728.944194577758 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 25306.5477153613,
            "unit": "ns/iter",
            "extra": "iterations: 78612\ncpu: 8794.930799369053 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 24975.110245255266,
            "unit": "ns/iter",
            "extra": "iterations: 79305\ncpu: 8815.985120736394 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 24598.419638255906,
            "unit": "ns/iter",
            "extra": "iterations: 75689\ncpu: 8660.654784711114 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 25014.638751405488,
            "unit": "ns/iter",
            "extra": "iterations: 83646\ncpu: 8935.34538411878 ns\nthreads: 1"
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
        "date": 1692118139696,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 25917.52673000087,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7923.322 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28619.04198986151,
            "unit": "ns/iter",
            "extra": "iterations: 84830\ncpu: 8901.24248496994 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 20731.75073375299,
            "unit": "ns/iter",
            "extra": "iterations: 81090\ncpu: 6456.507584165743 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 26819.285119995766,
            "unit": "ns/iter",
            "extra": "iterations: 82211\ncpu: 8341.102772135113 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28270.458299999747,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8723.628000000004 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28344.49606072396,
            "unit": "ns/iter",
            "extra": "iterations: 79837\ncpu: 8781.7402958528 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 29129.961208791017,
            "unit": "ns/iter",
            "extra": "iterations: 81900\ncpu: 8684.463980463977 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 26871.55609433003,
            "unit": "ns/iter",
            "extra": "iterations: 75480\ncpu: 8618.289613142553 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 32985.549744965116,
            "unit": "ns/iter",
            "extra": "iterations: 74500\ncpu: 9425.2577181208 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 30762.17852354451,
            "unit": "ns/iter",
            "extra": "iterations: 73094\ncpu: 9256.851451555527 ns\nthreads: 1"
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
        "date": 1696258840677,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 24849.98515173949,
            "unit": "ns/iter",
            "extra": "iterations: 112067\ncpu: 8717.622493686813 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 24012.004889190648,
            "unit": "ns/iter",
            "extra": "iterations: 80995\ncpu: 8655.584912648928 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 24141.024799999966,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8634.703000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25236.222607276224,
            "unit": "ns/iter",
            "extra": "iterations: 74737\ncpu: 8935.599502254572 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 25161.46240377426,
            "unit": "ns/iter",
            "extra": "iterations: 78851\ncpu: 8987.992542897362 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 25940.761546261176,
            "unit": "ns/iter",
            "extra": "iterations: 78900\ncpu: 9347.72496831432 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 31182.236428304102,
            "unit": "ns/iter",
            "extra": "iterations: 74788\ncpu: 10004.11162218538 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 29610.349402779506,
            "unit": "ns/iter",
            "extra": "iterations: 69656\ncpu: 9964.875961869771 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28973.499219999896,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9551.314 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 29583.69574928708,
            "unit": "ns/iter",
            "extra": "iterations: 72976\ncpu: 9493.680114010076 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}