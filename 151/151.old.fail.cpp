#include <cstdio>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <cassert>
#include <ctime>
using namespace std;
//this problem should be solved using recursion but not random number
//simulation

int single_paper(){
    int count_single = 0;
    int used = 0;
    vector<int> pvec;
    pvec.resize(4, 1); //2 3 4 5
    int n_inside = 4;
    while(used < 14){
        n_inside = accumulate(pvec.begin(), pvec.end(), 0);
        if(n_inside == 1)
            ++count_single;
        ++used;
        double picked = (double)rand()/(RAND_MAX)*n_inside;
        //printf("%d, %f\n", n_inside, picked);
        //find out which size is choosen
        int sum = 0;
        int i;
        for(i = 0; i < pvec.size() - 1; ++i){
            sum += pvec[i];
            if(picked <= sum) break;
        }
        assert( i <= 3 );
        --pvec[i];
        for(int k = i + 1; k < pvec.size(); ++k)
            ++pvec[k];
    }
    return count_single;
}
int main(){
    srand(time(NULL));
    int trials = 100000000;
    int sum = 0;
    for(int i = 0; i < trials; ++i){
        int tp = single_paper();
        sum += tp;
    }
    printf("%d %d %20.15f\n", sum, trials, static_cast<double>(sum)/trials);
}
