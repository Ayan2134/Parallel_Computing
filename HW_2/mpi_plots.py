import pandas as pd
import matplotlib.pyplot as plt

# Define the filenames for each number of processes
files = {
    2: 'mpi_2_results.csv',
    4: 'mpi_4_results.csv',
    6: 'mpi_6_results.csv',
    8: 'mpi_8_results.csv'
}

# Create a plot
plt.figure(figsize=(12, 8))

# Iterate through each file and add its data to the plot
for num_processes, file in files.items():
    # Read the CSV file into a dataframe
    df = pd.read_csv(file)
    
    # Plot the data with a label indicating the number of processes
    plt.plot(df['matrix_size'], df['time_taken'], marker='o', linestyle='-', label=f'{num_processes} Processes')

# Add labels, title, and legend
plt.xlabel('Matrix Size')
plt.ylabel('Time Taken (seconds)')
plt.title('Comparison of Time Taken for Matrix Multiplication with Different Numbers of Processes')
plt.grid(True)
plt.legend()

# Save the plot as an image file
plt.savefig('mpi_comparison_plot.png')
plt.show()

print("Comparison plot generated and saved as mpi_comparison_plot.png.")
