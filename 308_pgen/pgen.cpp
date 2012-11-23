#include "../lib/tools.h"
#include <vector>
#include <cstdio>
using namespace std;
int main()
{
    vector<int> primes;
    i64 result = 0;
    int nmax = 104743;
    //nmax=29;
    vector<int> ftable;
    primeWithin(primes, nmax);    
    factor_table_min(nmax, ftable);
    for(unsigned int i = 1; i < ftable.size(); ++i){
        ftable[i] = i/ftable[i];
    }
    //first process the easiest part 'n-2'
    result = 0;
    for( int i = 2; i<=nmax; ++i){
        i64 d = ftable[i];
       i64 tp = (i+d-2) +(6*i+2)*(i-d);
       i64 tsum = 0;
       assert(i % d == 0);
       int dmax = i/d;
       i64 last = i;
       for(i64 j = 2; j<= dmax; ++j){
           i64 next = i / (j);
           tsum += (last - next)*(j-1);
           last = next;
       }
       tsum += dmax;
        tp += tsum * 2 - 2;
        result += tp;
        //printf("%d %lld\n", i, result);
    }
    printf("%lld\n", result);
}
