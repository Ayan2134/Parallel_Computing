#!/bin/bash
g++ -fopenmp -o omp_matrix_mul omp_matrix_mul.cpp
output_file="omp_results_extra.csv"
echo "matrix_size,time_taken" > $output_file

for size in {200..3000..100}
do
    start=$(date +%s.%N)
    ./omp_matrix_mul $size
    end=$(date +%s.%N)
    time_taken=$(echo "$end - $start" | bc)
    echo "$size,$time_taken" >> $output_file

    echo "Matrix size $size completed in $time_taken seconds"
done

echo "Benchmarking completed. Results saved in $output_file."
