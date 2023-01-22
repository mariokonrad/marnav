#!/bin/bash -e

SCRIPT_BASE=$(dirname `readlink -f $0`)

supported_compilers=(
	"gcc-4.9.4;gcc:4.9.4"
	"gcc-5.5.0;gcc:5.5.0"
	"gcc-6.5.0;gcc:6.5.0"
	"gcc-7.4.0;gcc:7.4.0"
	"gcc-8.3.0;gcc:8.3.0"
	"gcc-8.4.0;gcc:8.4.0"
	"gcc-9.1.0;gcc:9.1.0"
	"gcc-9.2.0;gcc:9.2.0"
	"gcc-9.3.0;gcc:9.3.0"
	"gcc-9.4.0;gcc:9.4.0"
	"gcc-9.5.0;gcc:9.5.0"
	"gcc-10.1.0;gcc:10.1.0"
	"gcc-10.2.0;gcc:10.2.0"
	"gcc-10.3.0;gcc:10.3.0"
	"gcc-10.4.0;gcc:10.4.0"
	"gcc-11.1.0;gcc:11.1.0"
	"gcc-11.2.0;gcc:11.2.0"
	"gcc-11.3.0;gcc:11.3.0"
	"gcc-12.1.0;gcc:12.1.0"
	"gcc-12.2.0;gcc:12.2.0"
#	"clang-3.6.1;debian:buster"
#	"clang-3.6.2;debian:buster"
#	"clang-3.7.0;debian:buster"
#	"clang-3.7.1;debian:buster"
#	"clang-3.8.1;debian:buster"
#	"clang-3.9.0;debian:buster"
#	"clang-3.9.1;debian:buster"
#	"clang-4.0.0;debian:buster"
#	"clang-4.0.1;debian:buster"
#	"clang-5.0.0;debian:buster"
#	"clang-5.0.1;debian:buster"
	"clang-5.0.2;debian:buster"
	"clang-6.0.0;debian:buster"
#	"clang-6.0.1;debian:buster"
#	"clang-7.0.0;debian:buster"
#	"clang-7.0.1;debian:buster"
	"clang-7.1.0;debian:buster"
	"clang-8.0.0;debian:buster"
	"clang-9.0.0;debian:buster"
	"clang-10.0.0;debian:buster"
	"clang-11.0.0;ubuntu:20.04"
	"clang-12.0.0;ubuntu:20.04"
	"clang-13.0.0;ubuntu:20.04"
	"clang-14.0.0;debian:buster"
	"clang-15.0.6;debian:buster"
	)

repository=${DOCKER_REPOSITORY:-marnav}
account=${DOCKER_ACCOUNT:-mariokonrad}

# Note: rename image name:
#
#   docker tag "old-repo":"old-version" "new-repo":"new-version"
#

function build_image()
{
	compiler=$1
	base_image=$2
	compiler_name=${compiler%-*}
	compiler_version=${compiler#${compiler_name}-}

	docker build \
		--force-rm \
		--build-arg compiler_version="${compiler_version}" \
		--build-arg base_image="${base_image}" \
		--tag "${account}/${repository}:${compiler}" \
		--file "${SCRIPT_BASE}/docker/Dockerfile.${compiler_name}" \
		"${SCRIPT_BASE}/docker"
}

function usage()
{
	echo "usage: $(basename $0) compiler"
	echo ""
	echo "  supported compilers:"
	for v in ${supported_compilers[@]} ; do
		IFS=";" read -r -a vec <<< "${v}"
		local comp="${vec[0]}"
		local dist="${vec[1]}"

		echo "   - ${comp}  (${dist})"
	done
	echo ""
}

if [ $# -ne 1 ] ; then
	usage
	exit 1
fi

for v in ${supported_compilers[@]} ; do
	IFS=";" read -r -a vec <<< "${v}"
	comp="${vec[0]}"
	dist="${vec[1]}"

	if [ "${comp}" == "$1" ] ; then
		build_image ${comp} ${dist}
		exit 0
	fi
done
echo "error: specified compiler not supported: $1"
exit 1

