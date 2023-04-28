#!/bin/bash -e

SCRIPT_BASE=$(dirname `readlink -f $0`)

function scan_supported_images()
{
	find ${SCRIPT_BASE}/docker -type f -name "Dockerfile.*" | while read fn ; do
		f=$(basename $fn)
		echo ${f##Dockerfile.}
	done | sort -Vr
}

supported_compilers=$(scan_supported_images)
repository=${DOCKER_REPOSITORY:-marnav}
account=${DOCKER_ACCOUNT:-mariokonrad}

# Note: rename image name:
#
#   docker tag "old-repo":"old-version" "new-repo":"new-version"
#

function build_image()
{
	compiler=$1

	docker build \
		--force-rm \
		--tag "${account}/${repository}:${compiler}" \
		--file "${SCRIPT_BASE}/docker/Dockerfile.${compiler}" \
		"${SCRIPT_BASE}/docker"
}

function usage()
{
	echo "usage: $(basename $0) compiler"
	echo ""
	echo "  supported compilers:"
	for v in ${supported_compilers[@]} ; do
		echo "   - ${v}"
	done
	echo ""
}

if [ $# -ne 1 ] ; then
	usage
	exit 1
fi

for v in ${supported_compilers[@]} ; do
	if [ "${v}" == "$1" ] ; then
		build_image ${v}
		exit 0
	fi
done
echo "error: specified compiler not supported: $1"
exit 1

