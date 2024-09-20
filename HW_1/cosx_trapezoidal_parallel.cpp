    #include <bits/stdc++.h>
    #include <omp.h>
    using namespace std;

    const int num_steps = 1000000000;
    const double lower_limit = -M_PI_2;
    const double upper_limit = M_PI_2;

    int main(){
        double integral_cosx = 0.0;
        double step_sum = 0.0;
        double step_size = (upper_limit-lower_limit)/num_steps;
        step_sum = cos(lower_limit) + cos(upper_limit); //added these 2 to the sum beforehand so that rest all terms can be doubled and added avoiding recomputation
        #pragma omp parallel
        {
            #pragma omp for reduction(+:step_sum)
                for(int i=1;i<num_steps-1;i++){
                    step_sum+=2*cos(lower_limit+(i*step_size));
                }
        }
        integral_cosx = step_sum*step_size*0.5;
        cout<<integral_cosx<<endl;
    }