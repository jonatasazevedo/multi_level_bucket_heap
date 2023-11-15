#!/usr/bin/env bash

if [ -z "$1" ]; then
  echo "Usage: $0 <number of tests>"
  exit 1
elif [ "$1" -le 0 ]; then
  echo "Number of tests must be positive"
  exit 2
fi


CPP_GEN=tests/src/generator.cpp
CPP_STR=tests/src/structure.cpp
BIN_GEN=tests/exec/generator
BIN_STR=tests/exec/structure
RUN_MLB=./runner
RUN_GEN=./tests/exec/generator
RUN_STR=./tests/exec/structure
IN_FILE=files/testcase
SOL_FILE=files/out1
OUT_FILE=files/out2

g++ $CPP_GEN -o $BIN_GEN
g++ $CPP_STR -o $BIN_STR

# loop $1 times
for (( i=0; i<$1; i++ ))
do
  $RUN_GEN > $IN_FILE
  # $RUN_STR < $IN_FILE > $SOL_FILE
  # $RUN_MLB < $IN_FILE > $OUT_FILE
  if cmp -s $OUT_FILE $SOL_FILE; then
    echo "Test case passed"
  else
    echo "Test case failed"
    exit 3
  fi
done