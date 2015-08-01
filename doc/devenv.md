Development Environment {#page_devenv}
=======================

This page describes the requirements in order to build the library.

[TOC]

Requirements {#sec_devenv_requirements}
============

Compiler supported (older/others may work, but not tested):
- GCC 4.9.2 or newer
- Clang 3.6 or newer

Tools needed to build the library:
- cmake 3.0 or newer
- clang-format 3.7 or newer
- doxygen
- graphviz

optional (used for development only):
- lcov / genhtml, c++filt
- cppcheck
- clang-analyze (3.7 or newer)
- ctags, cscope

optional (no core dependency):
- Boost.ASIO (used only for some examples)
- Qt 5 (used only for some examples)

There are no other dependencies despite the standard library (C++11)
to build this library.

Other compilers may work, however untested.

Build {#sec_devenv_build}
=====

For normal, debug and release builds use the standard cmake CMAKE_BUILD_TYPE variable.
For example a debug build:

Full information developpers build:

~~~~~~~~~~~~~{.sh}
	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Coverage ..
	make
	make coverage doc cppcheck
~~~~~~~~~~~~~

Debug build:

~~~~~~~~~~~~~{.sh}
	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make
~~~~~~~~~~~~~

If you like to perform code coverage using the unit tests, do:

~~~~~~~~~~~~~{.sh}
	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Coverage ..
	make
	make coverage
~~~~~~~~~~~~~

As packaging system, cpack is used. Do after build:

~~~~~~~~~~~~~{.sh}
	make package
~~~~~~~~~~~~~

or for individual package types:

~~~~~~~~~~~~~{.sh}
	cpack -G TGZ
	cpack -G DEB
~~~~~~~~~~~~~

Build documentation:

~~~~~~~~~~~~~{.sh}
	mkdir build
	cd build
	cmake ..
	make doc
~~~~~~~~~~~~~


Build Options {#sec_devenv_buildoptions}
-------------

The following build types (-DCMAKE_BUILD_TYPE=x) are possible:
- Debug
- Release
- Coverage

Build options:
- ENABLE_STATIC=[ON/OFF] : enables static build by default, if OFF,
  a shared library is being built


Static Analysis with Clang {#sec_devenv_clang_static_analysis}
==========================

~~~~~~~~~~~~~{.sh}
	mkdir build
	cd build
	cmake -DCMAKE_CXX_COMPILER=/usr/share/clang/scan-build-3.7/c++-analyzer ..
	scan-build-3.7 --use-analyzer=/usr/bin/clang++-3.7 make
~~~~~~~~~~~~~

After the build, ```scan-build``` will tell you what to do in order to inspect
the findings.



