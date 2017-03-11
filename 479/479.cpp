#include "../lib/tools.h"
int main()
{
    i64 nmax = 1000000; 
    i64 sum = 0;
    i64 nmod = 1000000007LL;
    for(i64 k=2; k<=nmax; ++k){
        i64 base = k*k - 1;
        // base could be huge
        base %= nmod;
        i64 tmp = powermodule(base, nmax+1, nmod);
        if(!(nmax & 1) ) tmp = -tmp; 
        i64 x =0, y = 0, gcd = 0;
        extended_euclid(base+1, nmod, x,y, gcd );
        base = -base - tmp;
        base *= x;
        base %= nmod;
        if(base < 0) base += nmod;
        //assert(base %(k*k) ==0);
        sum += base;
        sum %= nmod;
    }
    printf("%lld\n", sum);
}
