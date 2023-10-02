window.BENCHMARK_DATA = {
  "lastUpdate": 1696257594266,
  "repoUrl": "https://github.com/duckstax/actor-zeta",
  "entries": {
    "Benchmark actors_ping_pong_scheduled clang-8 18.04 Release c++-11": [
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
        "date": 1692106465779,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 13274.164397411738,
            "unit": "ns/iter",
            "extra": "iterations: 101869\ncpu: 4951.270749688326 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 21964.41853848995,
            "unit": "ns/iter",
            "extra": "iterations: 90687\ncpu: 7842.396374342517 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 18686.914170974196,
            "unit": "ns/iter",
            "extra": "iterations: 87651\ncpu: 6739.518088783924 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 21577.39958466585,
            "unit": "ns/iter",
            "extra": "iterations: 85714\ncpu: 7694.247147490494 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 21923.38362838653,
            "unit": "ns/iter",
            "extra": "iterations: 90718\ncpu: 7809.833770585768 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 21865.968859999615,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7953.947999999995 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 21681.136546661543,
            "unit": "ns/iter",
            "extra": "iterations: 92635\ncpu: 7788.976088951262 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 21536.594647080306,
            "unit": "ns/iter",
            "extra": "iterations: 87541\ncpu: 7744.091340057798 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 20553.253259324352,
            "unit": "ns/iter",
            "extra": "iterations: 89359\ncpu: 7464.839579673 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 21599.1885152601,
            "unit": "ns/iter",
            "extra": "iterations: 94003\ncpu: 7849.397359658727 ns\nthreads: 1"
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
        "date": 1692108907207,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 21743.72928012428,
            "unit": "ns/iter",
            "extra": "iterations: 110908\ncpu: 7784.350091968117 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 24757.009484836923,
            "unit": "ns/iter",
            "extra": "iterations: 78441\ncpu: 8770.829030736479 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 25116.76378071466,
            "unit": "ns/iter",
            "extra": "iterations: 79604\ncpu: 8934.994472639568 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 24632.96649073982,
            "unit": "ns/iter",
            "extra": "iterations: 80336\ncpu: 8855.295259908386 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 19154.576785903188,
            "unit": "ns/iter",
            "extra": "iterations: 75704\ncpu: 6893.1139701997245 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 23553.18023999985,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8374.727000000003 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 21784.403633906713,
            "unit": "ns/iter",
            "extra": "iterations: 79914\ncpu: 7749.513226718721 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 25030.445460127194,
            "unit": "ns/iter",
            "extra": "iterations: 86313\ncpu: 8921.586551272692 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 24836.191719616407,
            "unit": "ns/iter",
            "extra": "iterations: 79006\ncpu: 8880.520466799984 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 24839.825862315975,
            "unit": "ns/iter",
            "extra": "iterations: 83612\ncpu: 8893.192364732337 ns\nthreads: 1"
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
        "date": 1692113726656,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22855.75848922621,
            "unit": "ns/iter",
            "extra": "iterations: 126690\ncpu: 7812.503749309338 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 25660.98634283379,
            "unit": "ns/iter",
            "extra": "iterations: 81935\ncpu: 8686.563739549645 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 25077.63237157167,
            "unit": "ns/iter",
            "extra": "iterations: 77358\ncpu: 8803.156751725743 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 23720.601042507762,
            "unit": "ns/iter",
            "extra": "iterations: 70599\ncpu: 8753.786880834014 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 24246.150511026346,
            "unit": "ns/iter",
            "extra": "iterations: 74360\ncpu: 8772.933028509951 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 24257.618835761747,
            "unit": "ns/iter",
            "extra": "iterations: 80018\ncpu: 8741.286960433903 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 24205.920892990664,
            "unit": "ns/iter",
            "extra": "iterations: 77806\ncpu: 8911.167519214461 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 23984.080309324665,
            "unit": "ns/iter",
            "extra": "iterations: 74873\ncpu: 8924.892818506009 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 24073.067341605714,
            "unit": "ns/iter",
            "extra": "iterations: 78822\ncpu: 8918.734617238837 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 23056.427677681357,
            "unit": "ns/iter",
            "extra": "iterations: 77203\ncpu: 8164.152947424333 ns\nthreads: 1"
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
        "date": 1692118542051,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 22196.071091560614,
            "unit": "ns/iter",
            "extra": "iterations: 137766\ncpu: 7771.609105294483 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 20773.401119741404,
            "unit": "ns/iter",
            "extra": "iterations: 93593\ncpu: 7376.56021283643 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 22297.045649735883,
            "unit": "ns/iter",
            "extra": "iterations: 98971\ncpu: 7818.244738357699 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 22530.575940000974,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7785.614999999994 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 22188.92642317037,
            "unit": "ns/iter",
            "extra": "iterations: 89009\ncpu: 7754.8753496837435 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 22343.3523402487,
            "unit": "ns/iter",
            "extra": "iterations: 86337\ncpu: 7827.4447803375115 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 21770.084830103257,
            "unit": "ns/iter",
            "extra": "iterations: 89025\ncpu: 7567.570907048579 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 22390.83910202486,
            "unit": "ns/iter",
            "extra": "iterations: 92742\ncpu: 7805.279161544926 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 22698.58676778524,
            "unit": "ns/iter",
            "extra": "iterations: 88345\ncpu: 7853.146188239288 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 22207.226690719934,
            "unit": "ns/iter",
            "extra": "iterations: 90908\ncpu: 7880.550666607993 ns\nthreads: 1"
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
        "date": 1696257055247,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 16970.639734622906,
            "unit": "ns/iter",
            "extra": "iterations: 105661\ncpu: 5807.4379383121495 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 29186.3930417112,
            "unit": "ns/iter",
            "extra": "iterations: 67919\ncpu: 10024.558665469161 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 27500.87843655984,
            "unit": "ns/iter",
            "extra": "iterations: 77112\ncpu: 9376.39018570391 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25139.081061529654,
            "unit": "ns/iter",
            "extra": "iterations: 123030\ncpu: 8779.807364057548 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 29015.769339976425,
            "unit": "ns/iter",
            "extra": "iterations: 73255\ncpu: 9971.499556344275 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 23498.158842728302,
            "unit": "ns/iter",
            "extra": "iterations: 131136\ncpu: 7810.598157637867 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 30950.470860102745,
            "unit": "ns/iter",
            "extra": "iterations: 69887\ncpu: 9813.15409160502 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 26913.378223466076,
            "unit": "ns/iter",
            "extra": "iterations: 98225\ncpu: 9239.987783150924 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27112.142866899445,
            "unit": "ns/iter",
            "extra": "iterations: 73208\ncpu: 9247.337722653268 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 18606.069599757764,
            "unit": "ns/iter",
            "extra": "iterations: 85848\ncpu: 6207.594818749418 ns\nthreads: 1"
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
        "date": 1696257593484,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 17234.59832000003,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 5819.389 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 24453.336898242364,
            "unit": "ns/iter",
            "extra": "iterations: 104631\ncpu: 8300.408100849652 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 25713.60522582156,
            "unit": "ns/iter",
            "extra": "iterations: 84580\ncpu: 8273.181603215888 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 27466.59192999999,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9248.753999999999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 22077.439415808447,
            "unit": "ns/iter",
            "extra": "iterations: 81754\ncpu: 7282.492599750472 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 27249.687135570926,
            "unit": "ns/iter",
            "extra": "iterations: 79405\ncpu: 9035.647629242481 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 22161.325440000044,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 7282.459000000001 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28146.554970053945,
            "unit": "ns/iter",
            "extra": "iterations: 81981\ncpu: 8989.713470194314 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 27733.840059125985,
            "unit": "ns/iter",
            "extra": "iterations: 76447\ncpu: 8785.260376469974 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28631.45347745504,
            "unit": "ns/iter",
            "extra": "iterations: 80950\ncpu: 8975.857936998145 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}