#include <bits/stdc++.h>
using namespace std;

const double lower_limit = -M_PI_2;
const double upper_limit = M_PI_2;
const double y_min = 0;
const double y_max = 1;

int main(int argc,char* argv[]){

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <num_iterations>" << endl;
        return 1;
    }
    const int iter = atoi(argv[1]);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution dis_x(lower_limit,upper_limit);
    uniform_real_distribution dis_y(y_min,y_max);
    int inside_func = 0;
    int outside_func = 0;
    for(int i=0;i<iter;i++){
        double random_x = dis_x(gen);
        double random_y = dis_y(gen);
        if(random_y<=cos(random_x)){
            inside_func++;
        }
        else{
            outside_func++;
        }
    }
    double area_of_rect = abs((upper_limit - lower_limit) * (y_max - y_min));
    double integral_cosx = ((double)inside_func/(double)iter)*area_of_rect;
    cout<<integral_cosx<<endl;
}
