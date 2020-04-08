[![Build Status](https://travis-ci.org/jinncrafters/actor-zeta.svg?branch=master)](https://travis-ci.org/jinncrafters/actor-zeta)

actor-zeta
========================

actor-zeta is an open source C++11/14/17 virtual actor model implementation featuring lightweight & fast and more.

### Example

## class method mode 

```C++

#include <actor-zeta/core.hpp>

using actor_zeta::basic_async_actor;

class key_value_storage_t final : public basic_async_actor {
public:
    explicit key_value_storage_t(dummy_supervisor &ref) : basic_async_actor(ref, "storage") {

        add_handler(
                "init",
                &key_value_storage_t::init
        );

        add_handler(
                "search",
                &key_value_storage_t::search
        );

        add_handler(
                "add",
                &key_value_storage_t::add
        );

    }

    ~key_value_storage_t() override = default;

    void init() {
       /// ...
    }

private:

    void search(std::string &key) {
        /// ...
    }

    void add(const std::string &key, const std::string &value) {
        /// ...
    }
    
};

```

## lambda mode

```C++

#include <actor-zeta/core.hpp>

using actor_zeta::basic_async_actor;

class storage_t final : public basic_async_actor {
public:
    storage_t() : basic_async_actor(nullptr, "storage") {
        add_handler(
                "update",
                [](storage_t & /*ctx*/, query_t& query) -> void {}
        );

        add_handler(
                "find",
                [](storage_t & /*ctx*/, query_t& query) -> void {}
        );

        add_handler(
                "remove",
                [](storage_t & /*ctx*/, query_t& query) -> void {}
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
    $ conan install actor-zeta/1.0.0a4@jinncrafters/stable
```
### Project setup

If you handle multiple dependencies in your project is better to add a *conanfile.txt*

    [requires]
    actor-zeta/1.0.0a4@jinncrafters/stable

    [generators]
    cmake

## Dependencies

* CMake >= 2.8

## Supported Compilers

* GCC >= 4.8.5
* Clang >= 3.3
* Microsoft Visual Studio >= 2015

## Supported Operating Systems

* Linux
* Mac OS X
* FreeBSD 10
* Windows >= 7 (static builds)
