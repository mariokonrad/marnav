#!/bin/bash -e

export SCRIPT_BASE=$(dirname `readlink -f $0`)

${SCRIPT_BASE}/bin/docker-prepare-image.sh \
| grep -E "^\s+-" \
| sed -e 's/^\s\+-\s//' \
| while read ln ; do bin/docker-prepare-image.sh $ln ; done

