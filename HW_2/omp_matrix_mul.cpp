#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size>" << endl;
        return 1;
    }
    int n = atoi(argv[1]);

    vector<vector<int>> m1(n, vector<int>(n, 0));
    vector<vector<int>> m2(n, vector<int>(n, 0));
    vector<vector<int>> prod(n, vector<int>(n, 0));

    #pragma omp parallel
    {
        #pragma omp for schedule(static) nowait
        for (int i = 0; i < n; i++) {
            unsigned int seed = time(0) + omp_get_thread_num();
            for (int j = 0; j < n; j++) {
                m1[i][j] = rand_r(&seed) % 10;
            }
        }
        #pragma omp for schedule(static)
        for (int i = 0; i < n; i++) {
            unsigned int seed = time(0) + omp_get_thread_num();
            for (int j = 0; j < n; j++) {
                m2[i][j] = rand_r(&seed) % 10;
            }
        }
        #pragma omp for collapse(2) schedule(auto) nowait
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += m1[i][k] * m2[k][j];
                }
                prod[i][j] = sum;
            }
        }
    }

    cout << prod.size() << " x " << prod[0].size() << endl;
    return 0;
}
