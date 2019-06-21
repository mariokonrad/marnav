Example: marnav as subproject (git submodule/subtree)
=====================================================

This is an example project, to show a way to use marnav as a subproject.

This demo uses the *ExternalProject* module from CMake.

**Note:** it is not advisable to test this demo using git submodule right here,
          copy this demo somewhere outside the repository.

**Note:** this is not a tutrial about git submodule.


Directory Structure
-------------------

```
marnav-demo
+- cmake
|  +- ExternMarnav.cmake
|
+- extern
|  +- README.md
|
+- src
|  +- CMakeLists.txt
|  +- main.cpp
|
+- CMakeLists.txt
+- README.md
```

with

- `cmake`  as the cmake module directory.
- `extern` the place where submodules are being kept.
- `src`    the source of the demo project.

For easier demonstration and testing purposes, the environment variable
`MARNAV_SOURCE_DIR` needs to be set accordingly.


Test
----

Copy the demo to some place, `/tmp/subproject` will do for now,
and make it a repository. The variable `${PATH_TO_MARNAV}` points
to you local clone. No need to set the variable, just replace it
as you execute the following.

```bash
cp -R ${PATH_TO_MARNAV}/examples/subproject /tmp/
cd /tmp/subproject
git init
git add *
git commit -am "Initial Import"
```

Add the library as git submodule:

```bash
git submodule add ${PATH_TO_MARNAV} /tmp/subproject/extern/marnav
```

Build the library and demo:

```bash
export MARNAV_SOURCE_DIR=/tmp/subproject/extern/marnav
cmake -H. -Bbuild
cmake --build build
```

**Note:** the library part (release mode) of *marnav* is being built, no unit tests
          no tools and no examples. See `cmake/ExternMarnav.cmake` for build options.

