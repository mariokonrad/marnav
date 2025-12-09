#!/bin/bash -e

export SCRIPT_BASE=$(dirname `readlink -f $0`)
export BASE=${SCRIPT_BASE}/..
export BUILD=${BASE}/build

function scan_supported_images()
{
	find ${SCRIPT_BASE}/docker -type f -name "Dockerfile.*" | while read fn ; do
		f=$(basename $fn)
		echo ${f##Dockerfile.}
	done | sort -Vr
}

supported_compilers=$(scan_supported_images)
supported_build_types=("Debug" "Release")
repository=${DOCKER_REPOSITORY:-marnav}
account=${DOCKER_ACCOUNT:-mariokonrad}

export NUM_PROC=${NUM_PROC:-$(nproc --ignore=2)}


function docker_run()
{
	dockerid=$1
	cmd="$2"

	docker run \
		--rm \
		--read-only \
		--volume $(pwd):$(pwd) \
		--workdir $(pwd) \
		--env HOME=$(pwd) \
		--user $(id -u):$(id -g) \
		${dockerid} \
		bash -c "${cmd}"
}

function build()
{
	compiler=$1
	build_type=$2
	dockerid=${account}/${repository}:${compiler}
	builddir=${BUILD_DIR:-${BUILD}/$(echo "${dockerid}_${build_type}" | tr '/:' '__')}

	if [ ! -d ${builddir} ] ; then
		mkdir -p ${builddir}
	fi

	docker_run ${dockerid} "cmake --version"
	docker_run ${dockerid} "cmake -B ${builddir} -DCMAKE_BUILD_TYPE=${build_type} ${BASE}"
	docker_run ${dockerid} "cmake --build ${builddir} -j ${NUM_PROC}"
	docker_run ${dockerid} "cmake --build ${builddir} --target unittest"
	docker_run ${dockerid} "cmake --build ${builddir} --target test"
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

