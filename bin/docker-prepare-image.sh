#!/bin/bash -e

SCRIPT_BASE=$(dirname `readlink -f $0`)

supported_compilers=(
	"gcc-5.5.0"
	"gcc-6.5.0"
	"gcc-7.4.0"
	"gcc-8.3.0"
	"gcc-9.1.0"
	)

name=marnav
account=mariokonrad/

function build_image()
{
	compiler=$1
	version=${compiler#gcc-}

	docker build \
		--build-arg gcc_version=${version} \
		--tag ${account}${name}:${compiler} \
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

