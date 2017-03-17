Example: marnav in a CMake build environment
============================================

This is an example project, to show a way to use marnav from a project
using the CMake build system.

If you are using this library within a cmake environment, you might
want to use `find_package`.

Build and install the library:

```bash
mkdir build
cd build
mkdir local
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/local ..
make
make install
```

Now the installation of the library is in the directory `marnav/build/local`.

To build the test program:
```bash
cd build
export marnav_DIR=`pwd`/local
mkdir test
cd test
cmake ../../example/library
make
./foobar
```

The `export` is necessary because cmake would not find the necessary
configuration of the library, which is installed in `.../lib/marnav/cmake`.

The tarball also contains the configuration files:
```bash
tar -xf marnav-0.3.1-Linux.tar.gz
export marnav_DIR=`pwd`/marnav-0.3.1-Linux
mkdir test
cd test
cmake ../../example/library
make
./foobar
```

You might want to consider extending the cmake modules path (in your `CMakeLists.txt`)
accordingly.


