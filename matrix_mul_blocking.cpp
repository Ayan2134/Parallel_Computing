#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main(){
    int r1 = 10000;
    int c1 = 1000;
    int r2 = c1;
    int c2 = 1000;

    vector<vector<int>> m1(r1, vector<int>(c1, 0));
    vector<vector<int>> m2(r2, vector<int>(c2, 0));
    vector<vector<int>> prod(r1, vector<int>(c2, 0));

    // Randomly initialize matrices
    srand(time(0));

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            m1[i][j] = rand() % 10;
        }
    }

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            m2[i][j] = rand() % 10;
        }
    }

    // Define block size based on cache size (e.g., L1 cache is usually around 32KB or 64KB per core)
    int blockSize = 32;  // Can be tuned for performance based on your hardware

    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int ii = 0; ii < r1; ii += blockSize) {
        for (int jj = 0; jj < c2; jj += blockSize) {
            for (int kk = 0; kk < c1; kk += blockSize) {
                // Perform matrix multiplication on the smaller block
                for (int i = ii; i < min(ii + blockSize, r1); i++) {
                    for (int j = jj; j < min(jj + blockSize, c2); j++) {
                        int sum = 0;
                        for (int k = kk; k < min(kk + blockSize, c1); k++) {
                            sum += m1[i][k] * m2[k][j];
                        }
                        prod[i][j] += sum;
                    }
                }
            }
        }
    }

    cout << prod.size() << " x " << prod[0].size() << endl;
}
