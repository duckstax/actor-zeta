[![Build Status](https://travis-ci.org/smart-cloud/actor-zeta.svg?branch=master)](https://travis-ci.org/smart-cloud/actor-zeta)
[![Build Status](https://travis-ci.org/jinntechio/actor-zeta.svg?branch=master)](https://travis-ci.org/jinntechio/actor-zeta)

actor-zeta
========================

actor-zeta is an open source C++11  virtual actor model implementation featuring lightweight & fast and more.


```C++

#include <actor-zeta/core.hpp>

using actor_zeta::context;
using actor_zeta::basic_async_actor;


class storage_t final : public basic_async_actor {
public:
    storage_t() : basic_async_actor(nullptr, "storage") {
        add_handler(
                "update",
                [](context & /*ctx*/, query_t& query) -> void {
                
                }
        );

        add_handler(
                "find",
                [](context & /*ctx*/, query_t& query) -> void {
                
                }
        );

        add_handler(
                "remove",
                [](context & /*ctx*/, query_t& query) -> void {
                                                               
                }
        );
    }

    ~storage_t() override = default;
};

```

## Dependencies

* CMake

## Supported Compilers

* GCC >= 4.8.5
* Clang >= 3.3
* Microsoft Visual Studio >= 2015

## Supported Operating Systems

* Linux
* Mac OS X
* FreeBSD 10
* Windows >= 7 (static builds)
