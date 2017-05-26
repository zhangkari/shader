#!/bin/bash

function usage() {
	echo "Usage: $0 [debug | release | clean]";
}

if [ $# -eq 0 ] ; then
	build_type="Debug";

elif [ $# -eq 1 ] ; then
	build_type=$(echo $1 | tr [A-Z] [a-z])
	if [ $build_type == "release" ] ; then
		build_type="Release"
	elif [ $build_type == "debug" ] ; then
		build_type="Debug"
    elif [ $build_type == "clean" ] ; then
        #rm -rvf !(build.sh|CMakeLists.txt)
        rm -rvf Makefile
        echo "clean finish."
        exit 0
	else
		usage;
		exit 1
	fi

else
	usage;
	exit 3
fi

echo "Build $build_type"
cmake -DCMAKE_BUILD_TYPE=$build_type .
make
