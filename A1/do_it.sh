#!/bin/bash
export LC_NUMERIC="en_US.UTF-8"

mpicc -g -std=c99 -o $4 $4.c

number_trials=$3
start=`date +%s%N`
for ((i=0; i < number_trials; i++)) ; do
	# Local
	# mpiexec -n $1 --use-hwthread-cpus --oversubscribe ./$4 $2
	# HPC
    mpiexec -n $1 ./$4 $2
done

end=`date +%s%N`
runtime=$( echo "$end - $start" | bc -l )
echo "Average time: $(($runtime / $number_trials))"
