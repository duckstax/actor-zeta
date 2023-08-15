
| compiler  | Master | Develop |
|:---:|:---:|:---:|
| gcc 4.8.5 - 11 | |[![ubuntu](https://github.com/cyberduckninja/actor-zeta/actions/workflows/ubuntu_gcc.yaml/badge.svg?branch=develop)](https://github.com/cyberduckninja/actor-zeta/actions/workflows/ubuntu_gcc.yaml) |
|clang 3.9 - 10 | |[![ubuntu](https://github.com/cyberduckninja/actor-zeta/actions/workflows/ubuntu_clang.yaml/badge.svg?branch=develop)](https://github.com/cyberduckninja/actor-zeta/actions/workflows/ubuntu_clang.yaml)|


# actor-zeta
========================

actor-zeta is an open source C++11/14/17 virtual actor model implementation featuring lightweight & fast and more.

## Example

```C++

#include <actor-zeta.hpp>

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

### Header-Only

To use as header-only; that is, to eliminate the requirement to
link a program to a static or dynamic library, simply
place the following line in exactly one new or existing source
file in your project.
```
#include <actor-zeta/src.hpp>
```

## For Users

Add the corresponding remote to your conan:

```bash
    conan remote add duckstax http://conan.duckstax.com
```

### Basic setup
```bash
    $ conan install actor-zeta/1.0.0a8@duckstax/stable
```
### Project setup

If you handle multiple dependencies in your project is better to add a *conanfile.txt*

    [requires]
    actor-zeta/1.0.0a8@duckstax/stable

    [generators]
    cmake

## Dependencies

* CMake >= 3.0


# Benchmarks

## Clang

OS: `ubuntu:18.04`

<table>
<tr>
    <td>Compiler Version</td>
    <td>Benchmark</td>
</tr>

<tr>
    <td rowspan=3>`clang-5.0`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_5.0_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_5.0_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_5.0_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-6.0`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_6.0_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_6.0_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_6.0_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-7`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_7_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_7_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_7_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-8`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_8_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_8_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_8_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-9`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_9_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_9_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_9_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-10`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_10_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_10_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_10_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-11`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_11_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_11_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_11_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-12`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_12_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_12_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_12_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-13`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_13_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_13_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_13_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-14`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_14_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_14_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_14_Release_17/)</td>
</tr>


<tr>
    <td rowspan=3>`clang-15`</td>
    <td>[Release_c++11](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_15_Release_11/)</td>
</tr>
<tr>
    <td>[Release_c++14](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_15_Release_14/)</td>
</tr>
<tr>
    <td>[Release_c++17](https://duckstax.github.io/actor-zeta/dev/bench/actors_ping_pong_scheduled/clang_18.04_15_Release_17/)</td>
</tr>


</table>
