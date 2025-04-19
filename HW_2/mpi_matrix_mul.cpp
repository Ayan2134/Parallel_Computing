#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void multiply_partial(const vector<vector<int>>& m1, const vector<vector<int>>& m2, vector<vector<int>>& prod, int start_row, int end_row, int n) {
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += m1[i][k] * m2[k][j];
            }
            prod[i - start_row][j] = sum;
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (argc != 2) {
        if (rank == 0) {
            cerr << "Usage: " << argv[0] << " <size of square matrix>" << endl;
        }
        MPI_Finalize();
        return 1;
    }
    int n = atoi(argv[1]);

    vector<vector<int>> m1, m2;
    vector<vector<int>> partial_prod;

    if (rank == 0) {
        m1.resize(n, vector<int>(n, 0));
        m2.resize(n, vector<int>(n, 0));

        unsigned int seed = time(0) + rank;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m1[i][j] = rand_r(&seed) % 10;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m2[i][j] = rand_r(&seed) % 10;
            }
        }
    }

    if (rank != 0) {
        m2.resize(n, vector<int>(n, 0));
    }

    for (int i = 0; i < n; i++) {
        MPI_Bcast(m2[i].data(), n, MPI_INT, 0, MPI_COMM_WORLD);
    }
    int rows_per_process = n / size;
    int extra_rows = n % size;

    int start_row, end_row;
    if (rank < extra_rows) {
        start_row = rank * (rows_per_process + 1);
        end_row = start_row + rows_per_process + 1;
    } else {
        start_row = rank * rows_per_process + extra_rows;
        end_row = start_row + rows_per_process;
    }

    partial_prod.resize(end_row - start_row, vector<int>(n, 0));
    vector<vector<int>> local_m1(end_row - start_row, vector<int>(n, 0));
    if (rank == 0) {
        for (int proc = 1; proc < size; proc++) {
            int start_proc, end_proc;
            if (proc < extra_rows) {
                start_proc = proc * (rows_per_process + 1);
                end_proc = start_proc + rows_per_process + 1;
            } else {
                start_proc = proc * rows_per_process + extra_rows;
                end_proc = start_proc + rows_per_process;
            }

            for (int i = start_proc; i < end_proc; i++) {
                MPI_Send(m1[i].data(), n, MPI_INT, proc, 0, MPI_COMM_WORLD);
            }
        }
        for (int i = start_row; i < end_row; i++) {
            local_m1[i - start_row] = m1[i];
        }
    } else {
        for (int i = start_row; i < end_row; i++) {
            MPI_Recv(local_m1[i - start_row].data(), n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    multiply_partial(local_m1, m2, partial_prod, 0, end_row - start_row, n);

    if (rank == 0) {
        vector<vector<int>> prod(n, vector<int>(n, 0));

        for (int i = 0; i < end_row - start_row; i++) {
            prod[i] = partial_prod[i];
        }

        for (int proc = 1; proc < size; proc++) {
            int start_proc, end_proc;
            if (proc < extra_rows) {
                start_proc = proc * (rows_per_process + 1);
                end_proc = start_proc + rows_per_process + 1;
            } else {
                start_proc = proc * rows_per_process + extra_rows;
                end_proc = start_proc + rows_per_process;
            }

            for (int i = start_proc; i < end_proc; i++) {
                MPI_Recv(prod[i].data(), n, MPI_INT, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        cout << prod.size() << " x " << prod[0].size() << endl;
    } else {
        for (int i = 0; i < end_row - start_row; i++) {
            MPI_Send(partial_prod[i].data(), n, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
