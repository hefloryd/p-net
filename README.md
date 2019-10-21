p-net: PROFINET device stack
============================
[![Build Status](https://travis-ci.org/rtlabs-com/p-net.svg?branch=master)](https://travis-ci.org/rtlabs-com/p-net)

The rt-labs PROFINET stack p-net is used for PROFINET device
implementations. It is easy to use and provides a small footprint. It
is especially well suited for embedded systems where resources are
limited and efficiency is crucial.

It is written in C and can be run on bare-metal hardware, an RTOS such
as rt-kernel, or on Linux or Windows. The main requirement is that the
platform can send and receive RAW Ethernet Layer 2 frames. The
p-net stack is supplied with full sources including a porting
layer.

rt-labs p-net is developed according to specification 2.3:

 * Conformance Class A (Class B upon request)
 * Real Time Class 1

Features:

 * TCP/IP
 * RT (real-time)
 * Address resolution
 * Parameterization
 * Process IO data exchange
 * Alarm handling
 * Configurable number of modules and sub-modules
 * Bare-metal or OS
 * Porting layer provided

The stack includes a comprehensive set of unit-tests.

Prerequisites for all platforms
===============================

 * CMake 3.13 or later
 * OSAL library

CMake
=====

Out-of-tree builds are recommended. After running cmake you can run
ccmake or cmake-gui to change settings.

OSAL
====

The p-net stack uses an abstraction layer that must be built before
building the stack. See the [OSAL README](https://github.com/rtlabs-com/osal/README.md)
for detailed instructions for all supported platforms. As an example,
the build instructions for Linux are:

```console
$ git clone -b OSAL-1.0 https://github.com/rtlabs-com/osal
$ cmake -S osal -B build.linux
$ cmake --build build.linux --target install
```

This builds and installs the OSAL library in build.linux/install. The
install directory will be used by the p-net stack build.

Windows
=======

 * Visual Studio 2013 or later
 * Kvaser CANlib SDK

The windows build supports Kvaser devices and requires the Kvaser
CANlib SDK.

Start a Visual Studio developer command prompt, then:

```
> cmake -S p-net -B build.windows -DOSAL_DIR=C:\path\to\osal\build.windows\install
> cmake --build build.windows --target all
> cmake --build build.windows --target check
```

This builds the stack and runs the unit tests.

Linux
=====

 * GCC 4.6 or later

```console
$ cmake -S p-net -B build.linux -DOSAL_DIR=/path/to/osal/build.linux/install
$ make -C build.linux all check
```

This builds the stack and runs the unit tests.

The clang static analyzer can also be used if installed:

```console
$ scan-build cmake -S p-net -B build.scan -DOSAL_DIR=/path/to/osal/build.linux/install
$ scan-build make -C build.scan
```

rt-kernel
=========

 * Workbench 2017.1 or later

Set the following environment variables. You should use a bash shell,
such as for instance the Command Line in your Toolbox
installation. Set BSP and ARCH values as appropriate for your
hardware.


```console
$ export COMPILERS=/opt/rt-tools/compilers
$ export RTK=/path/to/rt-kernel
$ export BSP=<bsp>
$ export ARCH=<arch>
```

Standalone project
------------------

This creates standalone makefiles.

```console
$ cmake $repo \
    -DCMAKE_TOOLCHAIN_FILE=/path/to/osal/build.rtk/install/cmake/toolchain/rt-kernel-$ARCH.cmake \
    -DOSAL_DIR=/path/to/osal/build.rtk/install \
    -G "Unix Makefiles"
$ make all
```

Workbench project
-----------------

This creates a Makefile project that can be imported to Workbench. The
project will be created in the build directory.

```console
$ cmake $repo \
    -DCMAKE_TOOLCHAIN_FILE=/path/to/osal/build.rtk/install/cmake/toolchain/rt-kernel-$ARCH.cmake \
    -DOSAL_DIR=/path/to/osal/build.rtk/install \
    -DCMAKE_ECLIPSE_EXECUTABLE=/opt/rt-tools/workbench/Workbench \
    -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
    -G "Eclipse CDT4 - Unix Makefiles"
```

A source project will also be created in the source folder. This
project can also be imported to Workbench. After importing,
right-click on the project and choose *New* -> *Convert to a C/C++
project*. This will setup the project so that the indexer works
correctly and the Workbench revision control tools can be used.

The library and the unit tests will be built. Note that the tests
require a stack of at least 6 kB. You may have to increase
CFG_MAIN_STACK_SIZE in your bsp include/config.h file.

Contributions
=============

Contributions are welcome. If you want to contribute you will need to
sign a Contributor License Agreement and send it to us either by
e-mail or by physical mail. More information is available
[here](https://rt-labs.com/contribution).
