#!/bin/bash

source_path=$1
build_path=$2
executable=$3

rootdir=$(pwd)

cd ${build_path}

# Init coverage
echo Initializing coverage info...
lcov -q --zerocounters -d .
lcov -q --no-external --initial -d . -b ${source_path} --gcov-tool ${rootdir}/utils/coverage/llvm-gcov.sh -c -o init.info
# Run executable
echo Running executable...
./${executable}
# Compute updated coverage
echo Collecting coverage info...
lcov -q --no-external -d . -b ${source_path} --gcov-tool ${rootdir}/utils/coverage/llvm-gcov.sh -c -o ./test.info
# Merge before and after
echo Merging coverage info...
lcov -q -a init.info -a test.info -o lcov.info
# Generate HTML report
echo Generating coverage report....
genhtml -q lcov.info -o coverage
