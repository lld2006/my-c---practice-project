#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;
int main()
{
    int target = 10000000;
    vector<int> ftable;
    IntPairVec vpairs;
    factor_table_min(target, ftable);
    double max = 1000;
    int nmax = 0;
    for(unsigned int i = 2; i < ftable.size(); ++i){
        factor_using_table(i, vpairs, ftable);
        i64 nt = totient_with_factor(vpairs);
        if(!isPermutation(nt, i)) continue;
        double nr = static_cast<double>(i)/(nt);
        if(nr < max){
            nmax = i;
            max = nr;
        }
    }
    printf("%d\n", nmax);
}
