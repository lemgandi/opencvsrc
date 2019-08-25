#!/bin/bash

TV=${1:-80}
LO=${2:-20}
HI=${3:-20}

./ch10ex8 -1 ../images/withoutChair2.jpg -2 ../images/withChair2.jpg -t ${TV} -h ${HI} -l ${LO}
# ./ch10ex8 -1 ../images/without_bottle.jpg -2 ../images/with_bottle.jpg -t ${TV} -h ${HI} -l ${LO}
