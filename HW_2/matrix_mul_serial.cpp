#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size of square matrix>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);

    vector<vector<int>> m1(n, vector<int>(n, 0));
    vector<vector<int>> m2(n, vector<int>(n, 0));

    srand(time(0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m1[i][j] = rand() % 10;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m2[i][j] = rand() % 10;
        }
    }

    vector<vector<int>> prod(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                prod[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    cout<< prod.size() << " x " << prod[0].size() << endl;

    return 0;
}
