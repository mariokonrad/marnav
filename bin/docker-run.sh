#!/bin/bash -e

if [ $# -lt 1 ] ; then
	echo "usage: $(basename $0) container-id [args...]"
	exit 1
fi

[[ $# == 1 ]] && arg="" || arg="-c"

docker run \
	--interactive \
	--tty \
	--rm \
	--read-only \
	--volume $(pwd):$(pwd) \
	--workdir $(pwd) \
	--env HOME=$(pwd) \
	--user $(id -u):$(id -g) \
	${1} \
	bash ${arg} "${@:2}"
