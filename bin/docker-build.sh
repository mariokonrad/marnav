#!/bin/bash -e

export SCRIPT_BASE=$(dirname `readlink -f $0`)
export BASE=${SCRIPT_BASE}/..
export BUILD=${BASE}/build

supported_gcc_versions=("5.5.0" "6.5.0" "7.4.0" "8.3.0" "9.1.0")

function build()
{
	version=$1
	dockerid=marnav:gcc-${version}
	builddir=${BUILD}/$(echo "${dockerid}" | tr '/:' '__')

	if [ ! -d ${builddir} ] ; then
		mkdir -p ${builddir}
	fi

	${SCRIPT_BASE}/docker-run.sh ${dockerid} "cmake -B ${builddir} -DCMAKE_BUILD_TYPE=Debug ${BASE}"
	${SCRIPT_BASE}/docker-run.sh ${dockerid} "cmake --build ${builddir} -j 2"
}

function usage()
{
	echo "usage: $(basename $0) gcc-version"
	echo ""
	echo "  supported gcc versions:"
	for v in ${supported_gcc_versions[@]} ; do
		echo "   - $v"
	done
	echo ""
}

if [ $# -ne 1 ] ; then
	usage
	exit 1
fi

for v in ${supported_gcc_versions[@]} ; do
	if [ "${v}" == "$1" ] ; then
		build $1
		exit 1
	fi
done
echo "error: specified version not supported: $1"
exit 1

