#include <bits/stdc++.h>
using namespace std;

const int num_steps = 1000000000;
const double lower_limit = -M_PI_2;
const double upper_limit = M_PI_2;

int main(int argc,char* argv[]){

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <num_iterations>" << endl;
        return 1;
    }
    const int num_steps = atoi(argv[1]);

    double integral_cosx = 0;
    double step_size = (upper_limit-lower_limit)/num_steps;
    double step_sum = 0.0;
    for(int i = 0;i<num_steps-1;i++){
        step_sum+=(cos(lower_limit+(i*step_size))+cos(lower_limit+((i+1)*step_size)));
    }
    integral_cosx = step_sum*step_size*0.5;
    cout<<integral_cosx<<endl;
}