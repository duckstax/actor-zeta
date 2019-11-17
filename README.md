[![Build Status](https://travis-ci.org/jinncrafters/actor-zeta.svg?branch=master)](https://travis-ci.org/jinncrafters/actor-zeta)

actor-zeta
========================

actor-zeta is an open source C++11  virtual actor model implementation featuring lightweight & fast and more.

### Example

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

## For Users

Add the corresponding remote to your conan:

```bash
    conan remote add jinncrafters https://api.bintray.com/conan/jinncrafters/conan
```

### Basic setup
```bash
    $ conan install sol2/2.20.6@jinncrafters/stable
```
### Project setup

If you handle multiple dependencies in your project is better to add a *conanfile.txt*

    [requires]
    actor-zeta/1.0.0@jinntechio/stable

    [generators]
    cmake

## Dependencies

* CMake
* Conan

## Supported Compilers

* GCC >= 4.8.5
* Clang >= 3.3
* Microsoft Visual Studio >= 2015

## Supported Operating Systems

* Linux
* Mac OS X
* FreeBSD 10
* Windows >= 7 (static builds)
