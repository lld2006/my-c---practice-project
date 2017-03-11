// the underlying rule
// for a given m and a given k, k-s must be a factor of k, the factor should be less than k!
// the fix point f is  f +s = m + 1, m+k-s...
// the jobs left is to write an efficient code to compute
// all values, it looks like sieve method is very promising
#include <cstdio>
#include "../lib/tools.h"
#include "../lib/typedef.h"
int main()
{
    i64 nmax = 1000000;
    unsigned int n2 = nmax/2;
    i64 total = 0;
    for(i64 nx = 1; nx <=n2; ++nx){ //all the numbers must be a
// multiple of nx
        //for(unsigned int k = 2*nx; k<= nmax; k+=nx){
        i64 t = nmax/nx;
        i64 tp = (2*(nmax+nx)+nx+1)*nx/2*(t-1)-(t+2)*(t-1)*nx*nx/2;
        //printf("%lld\n", tp);
        total += tp;
        //}
    }
    printf("%lld\n", total);
}
