#include "../lib/tools.h"
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
    int target = 100000000;
    vector<int> vtot = totient_sieve(target);

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
