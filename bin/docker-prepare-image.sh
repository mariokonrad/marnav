#!/bin/bash -e

SCRIPT_BASE=$(dirname `readlink -f $0`)

supported_gcc_versions=("5.5.0" "6.5.0" "7.4.0" "8.3.0" "9.1.0")
name=marnav

function build_gcc_image()
{
	version=$1

	docker build \
		--build-arg gcc_version=${version} \
		--tag ${name}:gcc-${version} \
		${SCRIPT_BASE}/docker
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
		build_gcc_image $1
		exit 1
	fi
done
echo "error: specified version not supported: $1"
exit 1

