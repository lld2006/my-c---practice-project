#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
vector<vector<i64>> vf;
using namespace std;
i64 partition(int number, int nmax)
{
    if( nmax > number){
        nmax = number;
    }
    if(number == 0) return 1;
    if(vf[number][nmax] >= 0)
        return vf[number][nmax];
    if(nmax == 1) 
        return 1;
    unsigned int q = number/nmax;
    i64 total = 0;
    for(unsigned int j = 0; j <= q; ++j ){
        //nmax can only be less
        total += partition(number - j * nmax, nmax-1 );
    }
    vf[number][nmax] = total;
    return total;
}
int main()
{
    int target = 1000;
    vf.resize(target+1);
    for(unsigned int i = 1; i < vf.size(); ++i ){
        vf[i].resize(i+1, -1);
    }
    i64 value = partition(target, target);
    printf("%lld\n", value);
}
