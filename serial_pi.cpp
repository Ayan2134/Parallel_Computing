#include <bits/stdc++.h>
using namespace std;

const int num_steps = 1000000000;

double f (double x){
    double ans = 4.0/(1 + x*x);
    return ans;
}

int main(){
    double pi = 0;
    double step_size = 1/(double)num_steps;
    int count = 0;
    double sum_height = 0;
    for(int i = 0;i<num_steps;i++){
        double x_coor = (i+0.5)*step_size;
        double height = f(x_coor);
        sum_height += height;
    }
    pi = sum_height*step_size;
    cout<<pi<<endl;
    return 0;
}