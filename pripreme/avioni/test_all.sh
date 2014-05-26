#!/bin/bash

mkdir bin
mkdir tmp
g++ -o bin/prepare_submission prepare_submission.cpp
bin/prepare_submission jaccard.cpp >tmp/submission.cpp
g++ -o bin/submission tmp/submission.cpp -O2

for i in `ls test_data`;
do
    echo $i
    cat test_data/$i | gunzip | bin/submission
done > tmp/results

g++ -o bin/stats stats.cpp
bin/stats <tmp/results
rm -r bin
rm -r tmp
