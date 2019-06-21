#!/bin/bash -e

# builds the marnav library and tests if it is usable as library in
# various ways.

export SCRIPT_BASE=$(dirname `readlink -f $0`)
export BASE=${SCRIPT_BASE}/..
export BUILD=${BASE}/build

export NUM_PROC=${NUM_PROC:-$(nproc --all --ignore=2)}

function prepare_dir()
{
	dir=$1
	if [ -d ${dir} ] ; then
		rm -fr ${dir}
	fi
	mkdir -p ${dir}
}

function build_library()
{
	install_prefix=$1
	tarballs_install=$2
	builddir=${BUILD}/build-marnav

	mkdir -p ${install_prefix}
	mkdir -p ${tarballs_install}

	prepare_dir ${builddir}
	pushd ${builddir}
	cmake \
		-DCMAKE_INSTALL_PREFIX=${install_prefix} \
		-DCMAKE_BUILD_TYPE=Release \
		-DENABLE_EXAMPLES=OFF \
		-DENABLE_TESTS=OFF \
		-DENABLE_TOOLS=OFF \
		${BASE}
	cmake --build . -j ${NUM_PROC}
	cmake --build . --target install
	cpack -G TGZ
	mv marnav-*.tar.gz ${tarballs_install}
	popd
}

function test_example_use_installation()
{
	install_prefix=$1
	builddir=${BUILD}/build-example-installed

	prepare_dir ${builddir}
	pushd ${builddir}
	cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_PREFIX_PATH=${install_prefix} \
		${BASE}/examples/library
	cmake --build . -j ${NUM_PROC}
	./foobar
	popd
}

function test_example_use_tarball()
{
	tarball=$1
	builddir=${BUILD}/build-example-tarball
	unpackdir=${builddir}/marnav

	prepare_dir ${builddir}
	mkdir -p ${unpackdir}
	pushd ${builddir}
	tar --strip-components=1 -xzf ${tarball} -C ${unpackdir}
	cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_PREFIX_PATH=${unpackdir} \
		${BASE}/examples/library
	cmake --build . -j ${NUM_PROC}
	./foobar
	popd
}

function test_example_use_externalproject_import()
{
	builddir=${BUILD}/build-example-externalproject

	prepare_dir ${builddir}
	pushd ${builddir}
	cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DMARNAV_SOURCE_DIR=${BASE} \
		${BASE}/examples/subproject
	cmake --build . -j ${NUM_PROC}
	./src/marnav-demo
	popd
}

function test_example_use_subdirectory()
{
	builddir=${BUILD}/build-example-subdirectory

	prepare_dir ${builddir}
	pushd ${builddir}
	cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DMARNAV_SOURCE_DIR=${BASE} \
		${BASE}/examples/subdirectory
	cmake --build . -j ${NUM_PROC}
	./foobar
	popd
}

prepare_dir ${BUILD}
build_library ${BUILD}/install ${BUILD}/tarballs
test_example_use_installation ${BUILD}/install
test_example_use_tarball ${BUILD}/tarballs/marnav-*.tar.gz
test_example_use_externalproject_import
test_example_use_subdirectory

