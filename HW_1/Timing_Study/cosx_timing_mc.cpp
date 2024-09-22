#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

const int iter = 100000000;
const double lower_limit = -M_PI_2;
const double upper_limit = M_PI_2;
const double y_min = 0;
const double y_max = 1;

int main() {
    int inside_func = 0;
    double start_time = omp_get_wtime();

    #pragma omp parallel 
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis_x(lower_limit, upper_limit);
        uniform_real_distribution<double> dis_y(y_min, y_max);

        int local_inside_func = 0;
        #pragma omp for schedule(static) nowait
        for (int i = 0; i < iter; i++) {
            double random_x = dis_x(gen);
            double random_y = dis_y(gen);
            if (random_y <= cos(random_x)) {
                local_inside_func++;
            }
        }

        #pragma omp atomic
        inside_func += local_inside_func;
    }

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    double area_of_rect = abs((upper_limit - lower_limit) * (y_max - y_min));
    double integral_cosx = ((double)inside_func / (double)iter) * area_of_rect;

    cout << "Integral result: " << integral_cosx << endl;
    cout << "Elapsed Time: " << elapsed_time << " seconds" << endl;

    return 0;
}
