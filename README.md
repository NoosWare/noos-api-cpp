# NOOS API [0.9.1]
-----------------------

## Contents
- [Dependencies](#dependencies)
- [Building](#building)
- [CMake Options](#cmake-options)
- [Installing](#installing)
- [Testing](#testing)
- [Examples](#examples)
- [Old Compilers](#old-compilers)
- [Tutorials](#tutorials)
- [Documentation](#documentation)
- [Help](#help)

[![Build Status](https://travis-ci.org/NoosWare/noos-api-cpp.svg?branch=master)](https://travis-ci.org/NoosWare/noos-api-cpp)

The NOOS API for C++ uses C++14 features and allows your apps to access the NOOS platform.
It is portable on Linuxes and relies on cross-platform libraries: 
[lib BOOST](http://www.boost.org) and [C++ STL](https://en.wikipedia.org/wiki/Standard_Template_Library).

It uses asynchronous execution, inspired (and supported) by BOOST ASIO.
It has been designed this way on purpose: you can send one or many *queries* (e.g., service calls)
to the cloud platform, and in the meantime keep the Robot busy with other local processing.

This enables you to write both asynchronous and multithreaded robot controllers,
by *daisy-chanining* delegates via subsequent callbacks.

All callback schemes use the `std::function` therefore you can pass 
*lambdas, function pointers, class members and struct functors* as callbacks.

This API allows you to start multiple connections and queries (named `callables`),
which template the actual data being sent and received.
You are free to inherit from `callable`, define your own `error_handler`,
or even compose objects for those classes internally.

The basic design is as follows:
- you construct `callables` 
- you control when and how often you call them (method `send`)
- your own callback receives the reply.

The callback must be defined by you and you pass it to a callable at construction:
- whereas you can update and change the data (e.g., `cloud_type`)
- you cannot change the functor
- the only exception is `vision_batch<...>` which has its own internal functor
- however `vision_batch<...>` requires that you pass tied pairs of cloud data and functors (see example)

In general, you can chain calls (e.g., one after another), parallelise them (call them at the same time)
and in the case of vision calls, you can batch them (see `vision_batch<...>`).

Because certain scenarios require you to send frequent cloud queries, class `callable`
keeps a connection open (for up to 2 seconds) with the cloud platform, thus
all you need to do is keep a callable object active (but please don't spam too frequently or you will get blacklisted).

Non-continuous calls (e.g., a one-off query) can be controlled by the lifetime of the callble object.

_NOTE_: current version 0.9.1 is **under developlment**!

## Dependencies

The following dependencies are **required** to build the C++ API:

* gcc/g++ >= 4.9
* boost >= 1.58
* cmake >= 2.8
* libssl-dev >= 1.0

On a Ubuntu/Debian machine you can install all dependencies using (you milage may vary depending on distro version)

```shell
sudo apt-get install cmake gcc g++ libboost-all-dev libssl-dev
```

## CMake Options

*Note* that you can pass a variety of CMake arguments to suit your needs:

* `-DNOOS_SHARED=ON`		                        (Default: compile a shared libnoos)
* `-DNOOS_STATIC=ON`		                        (Optional: compile a static libnoos)
* `-DBUILD_TESTS=ON`                                (Optional: compile various tests - run with `make test`)
* `-DBUILD_EXAMPLES=ON`                             (Optional: compile various examples)
* `-DCMAKE_BUILD_TYPE=Debug`                        (Optional: enable debug symbols)
* `-DOPEN_NAO=ON`                                   (Optional: compiling on OpenNAO builds binaries for ATOM CPU)
* `-DCMAKE_INSTALL_PREFIX=/usr`	                    (Optional: specify the library install directory
* `-DOPENSSL_ROOT_DIR=/usr/local/opt/openssl`       (Optional: specify OpenSSL root directory)
* `-DOPENSSL_LIBRARIES=/usr/local/opt/openssl/lib/` (Optional: specify OpenSSL library directory)

All of those arguments are optional, however depending on your scenario you may have to adjust.
For example, building for a NAO robot the convenience flag `-DOPEN_NAO=ON` will create a static library optimising for an ATOM cpu
using i386 architecture.

## Building

To build simply do:

```shell
mkdir build
cd build
cmake ..
make
```

You should end up with a library and/or tests and examples under your build directory.

## Installing

You may install if you wish to (as root or using `sudo`):

```shell
sudo make install
```

The produced library will be installed in `/usr/local/lib/` whereas the headers are installed in `/usr/local/include/` by default.

If you wish to install to another location or a user directory then run:

```shell
-DCMAKE_INSTALL_PREFIX=/other/dir
```

*Bear in mind* that this only changes the library installation location and **not** the header install location.

## Testing

Enable tests when you run cmake with:

```shell
cmake .. -DBUILD_TESTS=ON
```

This will create a `noos-api/cpp/build/tests` directory for each file in `noos-api/cpp/tests`.
There are three types of tests:

* JSON (de)serialisation tests.
* Class unit tests.
* Cloud functionality tests.

To execute them, type:

```shell
make test
```

*_Warning_*: do not run individual tests from within the `/noos-api/cpp/build/tests` directory!

*_Note_*: all examples and test have been checked with `valgrind --leak-check=full` under Ubuntu 16.04 and found
to have no memory leaks or segfaults.

If you do happen to run across such issues, please open an issue on GitHub.

## Examples

The source files for the examples are under `/noos-api/cpp/examples` and if you use the CMake option flag `-DBUILD_EXAMPLES=ON` they
will be built under `/noos-api/cpp/build/examples/`.

You can run them individually, or use them as templates.

_WARNING_: The communication between the platform and the API is with TLS, so you will need your own
SSL certificate to use it. Place the certificate in `/build/examples/` and call it `cert.pem`.

## Old Compilers

Some OSes do not ship with a newer *g++* (versions 4.9 and up), or you may be for whatever reason stuck with an older version.
A requirement for version 0.8.0 is to have gcc/g++ >= 4.9, therefore if you are targetting an older platform you have two options:

* build a gcc 4.9 [from source](https://gcc.gnu.org/wiki/InstallingGCC)
* build your apps using a static noos library and static libstdc++

Because the noos library relies only on `libstdc++` a static link with it increases the executable size,
but allows you to target older systems.
To do so use the cmake flag `-DNOOS_STATIC=ON` by building on a modern machine with *g++* >= 4.9.
However, the boost dependencies also require a somewhat new version of the C runtime libraries.
For further details please see the advanced tutorials.

## Tutorials

We have created a repository with ROS tutorials and examples, ranging from simple use to advanced projects.

* [noos_ros_tutorials](https://github.com/NoosWare/noos_ros_tutorials)

## Documentation

For a complete list of the cloud classes and the object classes used by the C++ API,
execute:

```shell
doxygen doxy.conf
```

A folder `docs` will be created, with HTML doxygen files.

## Help

If you run into any bugs or issues, please report them on github. 

## Contributing

If you would like to contribute (thanks btw :-), please read `CONTRIBUTING.md` beforehand.
