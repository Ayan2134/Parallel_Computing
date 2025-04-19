#!/bin/bash
mpic++ -o mpi_matrix_mul mpi_matrix_mul.cpp

process_counts=(8)

for num_processes in "${process_counts[@]}"
do
    output_file="mpi_${num_processes}_results.csv"
    echo "matrix_size,time_taken" > $output_file  # Only need the number of processes in the filename

    for size in {100..5200..1000} 
    do
        start=$(date +%s.%N)
        mpirun --use-hwthread-cpus -np $num_processes ./mpi_matrix_mul $size
        end=$(date +%s.%N)
        time_taken=$(echo "$end - $start" | bc)
        echo "$size,$time_taken" >> $output_file  # Removed num_processes from the output
        echo "Matrix size $size with $num_processes processes completed in $time_taken seconds"
    done
done

echo "MPI Benchmarking completed. Results saved in separate files."
