#!/bin/bash -e

export SCRIPT_BASE=$(dirname `readlink -f $0`)
export BASE=${SCRIPT_BASE}/..
export BUILD=${BASE}/build

supported_compilers=(
	"gcc-4.9.4"
	"gcc-5.5.0"
	"gcc-6.5.0"
	"gcc-7.4.0"
	"gcc-8.3.0"
	"gcc-9.1.0"
	"gcc-9.2.0"
	"clang-3.9.1"
	"clang-5.0.2"
	"clang-6.0.0"
	"clang-7.1.0"
	"clang-8.0.0"
	"clang-9.0.0"
	)
supported_build_types=("Debug" "Release")
name=marnav
account=mariokonrad/

# ask system about number of processors, accept already specified number
export NUM_PROC=${NUM_PROC:-$(cat /proc/cpuinfo | grep -E "^processor" | wc -l)}


function build()
{
	compiler=$1
	build_type=$2
	dockerid=${account}${name}:${compiler}
	builddir=${BUILD_DIR:-${BUILD}/$(echo "${dockerid}_${build_type}" | tr '/:' '__')}

	if [ ! -d ${builddir} ] ; then
		mkdir -p ${builddir}
	fi

	# TODO: support configurations
	${SCRIPT_BASE}/docker-run.sh ${dockerid} "cmake -B ${builddir} -DCMAKE_BUILD_TYPE=${build_type} ${BASE}"
	${SCRIPT_BASE}/docker-run.sh ${dockerid} "cmake --build ${builddir} -j ${NUM_PROC}"
	${SCRIPT_BASE}/docker-run.sh ${dockerid} "cmake --build ${builddir} --target unittest"
	${SCRIPT_BASE}/docker-run.sh ${dockerid} "cmake --build ${builddir} --target test"
}

function usage()
{
	echo "usage: $(basename $0) compiler build-type"
	echo ""
	echo "  supported compilers:"
	for v in ${supported_compilers[@]} ; do
		echo "   - $v"
	done
	echo ""
	echo "  supported build types:"
	for v in ${supported_build_types[@]} ; do
		echo "   - $v"
	done
	echo ""
}

function check_supported_compilers()
{
	compiler=$1
	for v in ${supported_compilers[@]} ; do
		if [ "${v}" == "${compiler}" ] ; then
			return
		fi
	done
	echo "error: specified compiler not supported: ${compiler}"
	exit -1
}

function check_supported_build_types()
{
	build_type=$1
	for v in ${supported_build_types[@]} ; do
		if [ "${v}" == "${build_type}" ] ; then
			return
		fi
	done
	echo "error: specified build type not supported: ${build_type}"
	exit -1
}

if [ $# -ne 2 ] ; then
	usage
	exit 1
fi

check_supported_compilers $1
check_supported_build_types $2
build $1 $2

