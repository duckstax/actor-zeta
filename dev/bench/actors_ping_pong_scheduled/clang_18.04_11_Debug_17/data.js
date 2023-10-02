window.BENCHMARK_DATA = {
  "lastUpdate": 1696257946326,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled clang-11 18.04 Debug c++-17": [
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
          "id": "a5b7db6b2410da02082326530de010ad26bc6bf0",
          "message": "Clang build bm",
          "timestamp": "2023-08-15T16:18:27+03:00",
          "tree_id": "2aba661033231e5336973dbca7867784dd351421",
          "url": "https://github.com/duckstax/actor-zeta/commit/a5b7db6b2410da02082326530de010ad26bc6bf0"
        },
        "date": 1692106803022,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 20930.597148141733,
            "unit": "ns/iter",
            "extra": "iterations: 83805\ncpu: 6708.340791122249 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 21472.67139736599,
            "unit": "ns/iter",
            "extra": "iterations: 78283\ncpu: 6948.260797363412 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 27117.749749662195,
            "unit": "ns/iter",
            "extra": "iterations: 79892\ncpu: 8912.444299804738 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27323.862199631578,
            "unit": "ns/iter",
            "extra": "iterations: 76531\ncpu: 9104.278004991444 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 27130.047867237576,
            "unit": "ns/iter",
            "extra": "iterations: 77130\ncpu: 9025.289770517309 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27307.57623107882,
            "unit": "ns/iter",
            "extra": "iterations: 77757\ncpu: 8935.618658127238 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27274.68391848172,
            "unit": "ns/iter",
            "extra": "iterations: 78755\ncpu: 8960.839311789736 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 26756.02956261394,
            "unit": "ns/iter",
            "extra": "iterations: 90858\ncpu: 8781.613066543394 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27210.833480322573,
            "unit": "ns/iter",
            "extra": "iterations: 78237\ncpu: 8967.1625957028 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27352.410489902028,
            "unit": "ns/iter",
            "extra": "iterations: 78628\ncpu: 9058.881060182115 ns\nthreads: 1"
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
          "id": "13f5d5708aa4baefe68655e94d167b4efc46662f",
          "message": "BM run GCC and Clang",
          "timestamp": "2023-08-15T17:01:02+03:00",
          "tree_id": "0582bed100837da8b35e1568fdf6634365e7ed04",
          "url": "https://github.com/duckstax/actor-zeta/commit/13f5d5708aa4baefe68655e94d167b4efc46662f"
        },
        "date": 1692109177419,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22869.783382177895,
            "unit": "ns/iter",
            "extra": "iterations: 87352\ncpu: 7345.7734224745855 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27228.289081485997,
            "unit": "ns/iter",
            "extra": "iterations: 80652\ncpu: 8961.29420225165 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 27344.236999919667,
            "unit": "ns/iter",
            "extra": "iterations: 75038\ncpu: 8997.118793144806 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27207.89819846764,
            "unit": "ns/iter",
            "extra": "iterations: 73604\ncpu: 8913.625618172926 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 27386.958789958746,
            "unit": "ns/iter",
            "extra": "iterations: 85683\ncpu: 9015.655380880691 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 25926.86328220622,
            "unit": "ns/iter",
            "extra": "iterations: 118463\ncpu: 8452.328575166932 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 27164.125190006722,
            "unit": "ns/iter",
            "extra": "iterations: 76971\ncpu: 8915.277182315413 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 27510.25565731414,
            "unit": "ns/iter",
            "extra": "iterations: 120110\ncpu: 9093.254516693032 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27431.583133305354,
            "unit": "ns/iter",
            "extra": "iterations: 74573\ncpu: 9118.894237860892 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27587.338470869036,
            "unit": "ns/iter",
            "extra": "iterations: 75847\ncpu: 9011.627355070063 ns\nthreads: 1"
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
        "date": 1692114239077,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 29089.255659999933,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8857.762 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 33219.88594999993,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 10442.133 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 40600.34720649563,
            "unit": "ns/iter",
            "extra": "iterations: 108627\ncpu: 12739.716645033004 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 40207.82108136788,
            "unit": "ns/iter",
            "extra": "iterations: 56780\ncpu: 12751.032053539973 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 41188.085764697935,
            "unit": "ns/iter",
            "extra": "iterations: 54976\ncpu: 13309.17127473806 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 39290.60649160603,
            "unit": "ns/iter",
            "extra": "iterations: 55333\ncpu: 12974.44382195074 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 41575.24681323154,
            "unit": "ns/iter",
            "extra": "iterations: 60406\ncpu: 12936.584114160845 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 44533.96731829919,
            "unit": "ns/iter",
            "extra": "iterations: 53302\ncpu: 13443.578102134998 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 41158.06693320981,
            "unit": "ns/iter",
            "extra": "iterations: 49273\ncpu: 12580.141253830701 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 42336.806606932434,
            "unit": "ns/iter",
            "extra": "iterations: 55245\ncpu: 13004.691827314698 ns\nthreads: 1"
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
        "date": 1692119123695,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28163.848890000052,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7877.88 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 29057.280419999643,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9827.937 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 34946.66090486025,
            "unit": "ns/iter",
            "extra": "iterations: 63811\ncpu: 11098.780774474622 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 32587.84149588625,
            "unit": "ns/iter",
            "extra": "iterations: 66850\ncpu: 10553.961106955874 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 32327.06953672892,
            "unit": "ns/iter",
            "extra": "iterations: 65016\ncpu: 10654.000553709853 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 34390.365807157286,
            "unit": "ns/iter",
            "extra": "iterations: 63990\ncpu: 10618.748241912801 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 33586.789326634906,
            "unit": "ns/iter",
            "extra": "iterations: 78026\ncpu: 10016.441955245684 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 34260.11144306387,
            "unit": "ns/iter",
            "extra": "iterations: 60919\ncpu: 11328.523120865406 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 34283.599238539864,
            "unit": "ns/iter",
            "extra": "iterations: 58309\ncpu: 10432.567871169125 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 33273.636658779855,
            "unit": "ns/iter",
            "extra": "iterations: 57907\ncpu: 11403.438271711557 ns\nthreads: 1"
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
        "date": 1696257945606,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22157.215510000013,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7044.997000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 27748.59735431643,
            "unit": "ns/iter",
            "extra": "iterations: 76124\ncpu: 8863.671115548315 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28221.346758903328,
            "unit": "ns/iter",
            "extra": "iterations: 78060\ncpu: 9117.419933384579 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27849.011463974697,
            "unit": "ns/iter",
            "extra": "iterations: 115405\ncpu: 9004.43308348858 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 26608.787748870698,
            "unit": "ns/iter",
            "extra": "iterations: 78605\ncpu: 8595.13898606959 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27714.88799805931,
            "unit": "ns/iter",
            "extra": "iterations: 78329\ncpu: 8945.982969270637 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 25900.79155267794,
            "unit": "ns/iter",
            "extra": "iterations: 80783\ncpu: 8240.263421759524 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 24911.93187179293,
            "unit": "ns/iter",
            "extra": "iterations: 82242\ncpu: 8023.580409036749 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27827.30724000004,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8962.481000000002 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27474.04112548499,
            "unit": "ns/iter",
            "extra": "iterations: 77300\ncpu: 8926.16041397155 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}