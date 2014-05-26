#!/bin/bash

g++ -o prepare_submission prepare_submission.cpp
./prepare_submission jaccard.cpp >submission.cpp
g++ -o submission submission.cpp -O2

for i in `ls test_data`;
do
    echo $i
    cat test_data/$i | gunzip | ./submission
done > results

g++ -o stats stats.cpp
./stats <results
