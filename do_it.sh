#!/bin/bash

mpicc -g -Wall -std=c99 -o $4 $4.c

number_trials=$3
start=$(date +%s.%N)
for ((i=0; i < number_trials; i++)) ; do
    mpiexec -n $1 --use-hwthread-cpus --oversubscribe ./$4 $2
done

duration=$(echo "$(date +%s.%N) - $start" | bc)
execution_time=`printf "%.2f seconds" $duration / $number_trials`

echo "Time: $execution_time"
