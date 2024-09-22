#!/bin/bash

thread_counts=(2 4 6 8)
num_runs=5
#comment out one of them to study the other one

# g++ -fopenmp cosx_timing_trapezoidal.cpp -o cosx_timing_trapezoidal
# executable="./cosx_timing_trapezoidal"

g++ -fopenmp cosx_timing_mc.cpp -o cosx_timing_mc
executable="./cosx_timing_mc"

for threads in "${thread_counts[@]}"; do
    echo "Running with $threads threads"
    total_time=0
    
    for ((i=1; i<=num_runs; i++)); do
        export OMP_NUM_THREADS=$threads
        result=$($executable | grep "Elapsed Time" | awk '{print $3}')
        echo "Run $i: $result seconds"
        total_time=$(echo "$total_time + $result" | bc)
    done
    
    avg_time=$(echo "scale=4; $total_time / $num_runs" | bc)
    echo "Average Time for $threads threads: $avg_time seconds"
    echo ""
done
