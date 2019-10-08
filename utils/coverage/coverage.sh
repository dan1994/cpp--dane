#!/bin/bash
$1/$2
llvm-cov gcov -f -b $1/*.gcda
lcov -d $1 -b $1 --gcov-tool $(pwd)/utils/coverage/llvm-gcov.sh -c -o $1/lcov.info
genhtml $1/lcov.info -o $1/coverage
