window.BENCHMARK_DATA = {
  "lastUpdate": 1692099113069,
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
        "date": 1692094383144,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28227.656723764496,
            "unit": "ns/iter",
            "extra": "iterations: 83309\ncpu: 9250.01620473178 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28880.612579635665,
            "unit": "ns/iter",
            "extra": "iterations: 71576\ncpu: 9463.13708505644 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28156.85438657839,
            "unit": "ns/iter",
            "extra": "iterations: 83083\ncpu: 9305.435528327096 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 25453.813545467212,
            "unit": "ns/iter",
            "extra": "iterations: 132118\ncpu: 8289.24522018196 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28820.225634669496,
            "unit": "ns/iter",
            "extra": "iterations: 73424\ncpu: 9489.221507953802 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28789.833094992304,
            "unit": "ns/iter",
            "extra": "iterations: 70627\ncpu: 9743.906721225596 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28625.533703609635,
            "unit": "ns/iter",
            "extra": "iterations: 71298\ncpu: 9431.620802827561 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28904.89165914788,
            "unit": "ns/iter",
            "extra": "iterations: 73158\ncpu: 9350.42647420651 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28755.233212229192,
            "unit": "ns/iter",
            "extra": "iterations: 73491\ncpu: 9530.34929447142 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 27095.625204673262,
            "unit": "ns/iter",
            "extra": "iterations: 72677\ncpu: 8954.672042049056 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Benchmark actors_ping_pong_scheduled gcc-7 20.04 Debug c++-14": [
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
        "date": 1692095560340,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 26523.497144500525,
            "unit": "ns/iter",
            "extra": "iterations: 121695\ncpu: 8393.023542462715 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28327.48224337506,
            "unit": "ns/iter",
            "extra": "iterations: 77633\ncpu: 9120.446202001725 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 22889.02141887089,
            "unit": "ns/iter",
            "extra": "iterations: 77315\ncpu: 7012.524089762659 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28371.80997835776,
            "unit": "ns/iter",
            "extra": "iterations: 77628\ncpu: 9098.552068841136 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28751.68324479618,
            "unit": "ns/iter",
            "extra": "iterations: 73792\ncpu: 9167.148200346928 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28542.710809099342,
            "unit": "ns/iter",
            "extra": "iterations: 108973\ncpu: 9002.31158176796 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28664.89267639993,
            "unit": "ns/iter",
            "extra": "iterations: 79237\ncpu: 9037.19474487928 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28369.006272266462,
            "unit": "ns/iter",
            "extra": "iterations: 79716\ncpu: 9231.856841788342 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28463.804239157533,
            "unit": "ns/iter",
            "extra": "iterations: 76619\ncpu: 9150.153356217119 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28081.81037589845,
            "unit": "ns/iter",
            "extra": "iterations: 78798\ncpu: 9022.2937130384 ns\nthreads: 1"
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
        "date": 1692099111876,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 39541.29164468764,
            "unit": "ns/iter",
            "extra": "iterations: 62559\ncpu: 11186.377659489443 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 36779.88589547519,
            "unit": "ns/iter",
            "extra": "iterations: 66071\ncpu: 10964.609283952112 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 38543.25890096963,
            "unit": "ns/iter",
            "extra": "iterations: 57578\ncpu: 11222.084824064754 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 36966.48724800922,
            "unit": "ns/iter",
            "extra": "iterations: 59873\ncpu: 11071.987373273427 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 26673.488645311827,
            "unit": "ns/iter",
            "extra": "iterations: 63498\ncpu: 7926.73785001103 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 36976.54497396283,
            "unit": "ns/iter",
            "extra": "iterations: 63370\ncpu: 11299.60706959128 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 38745.922419157214,
            "unit": "ns/iter",
            "extra": "iterations: 62683\ncpu: 11520.726512770603 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 37860.352853545046,
            "unit": "ns/iter",
            "extra": "iterations: 65112\ncpu: 11364.244686079375 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 37916.021427386055,
            "unit": "ns/iter",
            "extra": "iterations: 60250\ncpu: 11074.746887966807 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 40420.71600532851,
            "unit": "ns/iter",
            "extra": "iterations: 65297\ncpu: 11834.897468490122 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}