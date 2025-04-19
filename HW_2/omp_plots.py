import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file into a pandas dataframe
df = pd.read_csv('omp_results.csv')

# Create a plot
plt.figure(figsize=(10, 6))
plt.plot(df['matrix_size'], df['time_taken'], marker='o', linestyle='-', color='r', label='Time Taken')

# Add labels and title
plt.xlabel('Matrix Size')
plt.ylabel('Time Taken (seconds)')
plt.title('Time Taken for Matrix Multiplication using OpenMP')
plt.grid(True)
plt.legend()

# Save the plot as an image file
plt.savefig('omp_results_plot.png')
plt.show()

print("Plot generated and saved as omp_results_plot.png.")
