#!/bin/bash

TV=${1:-80}
LO=${2:-20}
HI=${3:-20}
PV=${4:-255}

# ./ch10ex8 -1 ../images/without_chair.jpg -2 ../images/with_chair.jpg -t ${TV} -h ${HI} -l ${LO} -p ${PV}
# ./ch10ex8 -1 ../images/withoutChair2.jpg -2 ../images/withChair2.jpg -t ${TV} -h ${HI} -l ${LO}
./ch10ex8 -1 ../images/without_bottle.jpg -2 ../images/with_bottle.jpg -t ${TV} -h ${HI} -l ${LO} -p ${PV} -v
