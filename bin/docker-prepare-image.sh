#!/bin/bash -e

SCRIPT_BASE=$(dirname `readlink -f $0`)

supported_compilers=(
	"gcc-4.9.4"
	"gcc-5.5.0"
	"gcc-6.5.0"
	"gcc-7.4.0"
	"gcc-8.3.0"
	"gcc-9.1.0"
#	"clang-3.6.1"
#	"clang-3.6.2"
#	"clang-3.7.0"
#	"clang-3.7.1"
#	"clang-3.8.1"
#	"clang-3.9.0"
	"clang-3.9.1"
#	"clang-4.0.0"
#	"clang-4.0.1"
#	"clang-5.0.0"
#	"clang-5.0.1"
#	"clang-5.0.2"
	"clang-6.0.0"
#	"clang-6.0.1"
#	"clang-7.0.0"
#	"clang-7.0.1"
	"clang-7.1.0"
	"clang-8.0.0"
	)

name=marnav
account=mariokonrad/

function build_image()
{
	compiler=$1
	compiler_name=${compiler%-*}
	compiler_version=${compiler#${compiler_name}-}

	docker build \
		--force-rm \
		--build-arg compiler_version=${compiler_version} \
		--tag ${account}${name}:${compiler} \
		--file ${SCRIPT_BASE}/docker/Dockerfile.${compiler_name} \
		${SCRIPT_BASE}/docker
}

function usage()
{
	echo "usage: $(basename $0) compiler"
	echo ""
	echo "  supported compilers:"
	for v in ${supported_compilers[@]} ; do
		echo "   - $v"
	done
	echo ""
}

if [ $# -ne 1 ] ; then
	usage
	exit 1
fi

for v in ${supported_compilers[@]} ; do
	if [ "${v}" == "$1" ] ; then
		build_image $1
		exit 1
	fi
done
echo "error: specified compiler not supported: $1"
exit 1

