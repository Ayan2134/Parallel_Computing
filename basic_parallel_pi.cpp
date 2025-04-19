#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

const int num_steps = 1000000000;

double f (double x){
    double ans = 4.0/(1 + x*x);
    return ans;
}

int main(){
    double pi = 0;
    double step_size = 1/(double)num_steps;
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        double sum_height = 0;
        int num_threads = omp_get_num_threads();
        int id = omp_get_thread_num();
        for(int i = id;i<num_steps;i+=num_threads){
            double x_coor = (i+0.5)*step_size;
            double height = f(x_coor);
            sum_height += height;
        }
        
        #pragma omp critical
        {
            pi += sum_height*step_size;
        }
    }
    cout<<pi<<endl;
    return 0;
}