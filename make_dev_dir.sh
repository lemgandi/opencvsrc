#!/bin/bash
CMAKELISTT=./CMakeLists.txt.template
GITIGNORET=gitignore.template
CCT=./template.cc

usage() {
    echo Usage: $1 -n dirname
    echo Create dirname as a development directory, with a CMakeList.txt
    echo from the ${CMAKELISTT} file  and a .gitignore from the
    echo ${GITIGNORET} file.
}


args=$( getopt "n:" $*)
if [ $? -gt 0 ]
then
    usage $0
    exit 1
fi

set -- $args

while true
do
    case $1 in
	-n) DIRNAME=$2 ; shift ;;
	--)  break ;;
	*)   echo Oops. Argparse error ; exit 1 ;;
    esac
    shift
done

if [ ${DIRNAME:-nothing} = nothing ]
then
    usage $0
    exit 1;
fi
if [ -d ${DIRNAME} ]
then
    echo ${DIRNAME} already exists.  Sorry.
    usage $0
    exit 1;
fi

set -x
mkdir ${DIRNAME}
sed -e "s/%PROGRAM%/${DIRNAME}/g" < ${CMAKELISTT} > ${DIRNAME}/CMakeLists.txt
sed -e "s/%PROGRAM%/${DIRNAME}/g" < ${GITIGNORET} > ${DIRNAME}/.gitignore
cp ${CCT} ${DIRNAME}/${DIRNAME}.cc
set +x
    
