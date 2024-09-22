import matplotlib.pyplot as plt
import numpy as np
import subprocess
import os

cpp_code_filename = "cosx_trapezoidal_parallel.cpp"
cpp_executable = "cosx_trapezoidal_parallel"

iteration_list = np.arange(10,10000,100) #plotted till 10000 as the error becomes less than the precision i.e. it becomes 0 anyways

analytical_integral = 2.0

errors = []
iteration_values = []

compile_command = f"g++ -fopenmp {cpp_code_filename} -o {cpp_executable}"
subprocess.run(compile_command, shell=True, check=True)

for iter_count in iteration_list:
    run_command = f"./{cpp_executable} {iter_count}"
    result = subprocess.run(run_command, shell=True, capture_output=True, text=True)

    numerical_integral = float(result.stdout.strip())
    
    error = abs(numerical_integral - analytical_integral)
    
    iteration_values.append(iter_count)
    errors.append(error)

# Plotting the error vs number of iterations

plt.figure(figsize=(10, 6))
plt.plot(iteration_values, errors, marker='o', linestyle='-', color='r')
plt.xscale('log')  # used log scale so that even small errors can be scaled
plt.yscale('log')
plt.xlabel('Number of Iterations (log scale)')
plt.ylabel('Error (log scale)')
plt.title('Error in Trapezoidal Integration vs Number of Iterations')
plt.grid(True)

# Save the plot to a file
plt.savefig('trapezoidal_convergence_plot.png')
