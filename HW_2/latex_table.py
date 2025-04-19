import pandas as pd

# Read the CSV file into a DataFrame
df = pd.read_csv('omp_results.csv')

# Function to convert DataFrame to LaTeX table format
def convert_to_latex(df):
    latex_table = ""
    for _, row in df.iterrows():
        latex_table += f"        {int(row['matrix_size'])} & {row['time_taken']} \\\\ \\hline\n"
    return latex_table

# Get the LaTeX formatted table
latex_table = convert_to_latex(df)

# Print the LaTeX table
print(latex_table)
