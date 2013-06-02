#include "../lib/tools.h"
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    int target = 100000000;
    //int root = sqrt(target);
    vector<int> primes;
    primeWithin(primes, target);
    vector<int> vtot;
    vtot.resize(target+1);
    for(unsigned int i = 0; i < vtot.size(); ++i){
        vtot[i] = i;
    }
    for(unsigned int i = 0; i < primes.size(); ++i){
        unsigned int px = primes[i];
        for(unsigned int j = px*2; j < vtot.size(); j +=px){
            vtot[j] /= px;
            vtot[j] *= (px-1);
        }
    }

    int nmin = 0;
    double dmin = 10000;
    for(unsigned int i = 2; i < vtot.size(); ++i){
        if(vtot[i] == i) continue;
        double dr = static_cast<double>(i)/vtot[i];
        if(dr > dmin) continue;

        if(!isPermutation(i, vtot[i])) continue;
        dmin = dr;
        nmin = i;
    }
    printf("%d %f\n", nmin, dmin);
}
