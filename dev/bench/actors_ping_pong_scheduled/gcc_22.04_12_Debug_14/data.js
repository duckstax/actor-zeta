window.BENCHMARK_DATA = {
  "lastUpdate": 1692095869133,
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
        "date": 1692094642614,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 28415.557307036313,
            "unit": "ns/iter",
            "extra": "iterations: 106069\ncpu: 9030.197324383185 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28501.119175077238,
            "unit": "ns/iter",
            "extra": "iterations: 79765\ncpu: 9053.917131573999 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28213.661768932212,
            "unit": "ns/iter",
            "extra": "iterations: 111344\ncpu: 9005.042930018682 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28587.926769999965,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 9137.988999999998 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28404.65216071326,
            "unit": "ns/iter",
            "extra": "iterations: 75762\ncpu: 8984.678334785249 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28146.056713622427,
            "unit": "ns/iter",
            "extra": "iterations: 79011\ncpu: 8900.121502069325 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28675.02662779825,
            "unit": "ns/iter",
            "extra": "iterations: 91934\ncpu: 9058.029673461397 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28384.90634484335,
            "unit": "ns/iter",
            "extra": "iterations: 76771\ncpu: 9016.579177032992 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28180.079511263422,
            "unit": "ns/iter",
            "extra": "iterations: 76442\ncpu: 9077.344915099016 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28113.733389999994,
            "unit": "ns/iter",
            "extra": "iterations: 100000\ncpu: 8789.61499999999 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Benchmark actors_ping_pong_scheduled gcc-12 22.04 Debug c++-14": [
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
        "date": 1692095868650,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "fixture_t<int8_t>/ping_pong_single_threaded_1_int8_t/0",
            "value": 25745.77190526545,
            "unit": "ns/iter",
            "extra": "iterations: 78577\ncpu: 8153.627651857415 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t>/ping_pong_single_threaded_2_int8_t/0",
            "value": 28543.69922265567,
            "unit": "ns/iter",
            "extra": "iterations: 124012\ncpu: 9258.538689804212 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t>/ping_pong_single_threaded_3_int8_t/0",
            "value": 28232.84588786075,
            "unit": "ns/iter",
            "extra": "iterations: 75192\ncpu: 8961.042398127458 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_4_int8_t/0",
            "value": 28432.91847826071,
            "unit": "ns/iter",
            "extra": "iterations: 79304\ncpu: 8969.328154948047 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_5_int8_t/0",
            "value": 28999.271159688167,
            "unit": "ns/iter",
            "extra": "iterations: 92499\ncpu: 9197.872409431458 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_6_int8_t/0",
            "value": 28693.8780667676,
            "unit": "ns/iter",
            "extra": "iterations: 75935\ncpu: 9153.998814775796 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_7_int8_t/0",
            "value": 28322.9469725072,
            "unit": "ns/iter",
            "extra": "iterations: 78167\ncpu: 8990.366778819707 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_8_int8_t/0",
            "value": 28216.338777702797,
            "unit": "ns/iter",
            "extra": "iterations: 74450\ncpu: 9169.65211551376 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_9_int8_t/0",
            "value": 28458.229191661707,
            "unit": "ns/iter",
            "extra": "iterations: 133360\ncpu: 9173.954709058187 ns\nthreads: 1"
          },
          {
            "name": "fixture_t<int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t, int8_t>/ping_pong_single_threaded_10_int8_t/0",
            "value": 28691.064205291186,
            "unit": "ns/iter",
            "extra": "iterations: 77003\ncpu: 9179.244964481904 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}