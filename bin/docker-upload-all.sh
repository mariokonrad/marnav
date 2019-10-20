#!/bin/bash -e

docker image ls \
| grep "mariokonrad/marnav" \
| awk '{print $1":"$2}' \
| while read c ; do docker push $c ; done

