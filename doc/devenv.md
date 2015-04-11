Development Environment {#page_devenv}
=======================

This page describes the requirements in order to build the library.

[TOC]

Requirements {#sec_devenv_requirements}
============

Tools needed to build the library:
- GCC 4.9.2 or newer
- cmake 2.8.11 or newer
- clang-format 3.7 or newer
- doxygen

optional (used for development only):
- lcov / genhtml
- cppcheck

optional (no core dependency):
- Boost.ASIO (used only for some examples)

There are no other dependencies despite the standard library (C++11)
to build this library.

Other compilers may work, however untested.

Build {#sec_devenv_build}
=====

For normal, debug and release builds use the standard cmake CMAKE_BUILD_TYPE variable.
For example a debug build:

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

