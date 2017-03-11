// a = m^2 - n^2 b = 2 m n  c = m^2 +n^2
// m n must have different parity, m can be splitted to two parts, if m
// is less than mx, than n can be anything less than m. If m >= mx, 
// n <= nmax and I need to find all the odd or even n that is coprime 
// to n, using PIE ?
// 3141592653589793
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstdlib>
using namespace std;
i64 find_common_numbers(i64 m, i64 nmax, const IntPairVec& vpairs, int index, i64 prod)
{
    i64 count = 0;
    for(int i = index; i < (int)vpairs.size(); ++i){
        int p = vpairs[i].first;
        i64 prod1 = prod * p;
        if(m & 1) // need even numbers that can divide 
            count += nmax/prod1;
        else //even m need odd n
            count += (nmax+prod1/2)/prod1;
        count -= find_common_numbers(m, nmax, vpairs, i+1, prod1); 
    }
    return count;
}
int main(int argc, char** argv)
{
    i64 n = atoll(argv[1]);//159139, did not get it
    printf("%s n=%lld\n", argv[1], n);
    i64 mx = (sqrt(2*n-1)+1)/2;
    i64 mmax = sqrt(n-1);

    vector<int> vtotient, vfac;
    totient_using_table(vtotient, mx);
    factor_table_min(mmax, vfac);
    //m=2 is considered separately 1 primitive sol
    i64 total = 1; 
    for(i64 m = 3; m <= mx; ++m){
        assert(vtotient[m] % 2 == 0);
        if(m & 1)
            total += vtotient[m]/2;
        else
            total += vtotient[m];
    }
    for(i64 m =mx+1; m <=mmax; ++m){
        i64 nmax = sqrt(n - m*m);
        //assert
        //odd and even of m has diff effect
        IntPairVec vpairs;
        factor_using_table(m, vpairs, vfac);
        i64 n1 = 0;
        if (m & 1) //n should be even
            n1 = nmax/2;
        else
            n1 = (nmax+1)/2;
        int start = 0;
        if(vpairs[0].first ==2) start = 1;
        i64 tp = find_common_numbers(m, nmax, vpairs, start, 2LL);
        //printf("m=%lld nmax=%lld n1=%lld common=%lld\n", m, nmax,n1, tp);
        total +=  n1-tp;
    }
    printf("%lld\n", total);
}
