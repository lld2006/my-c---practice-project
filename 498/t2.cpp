#include "../lib/tools.h"
#include <cstdio>
i64 pmod( i64 n, i64 k, i64 nmod)
{
    if(2*k > n) k = n-k;
    i64 nn=1, dd=1;
    for(i64 i = 1; i<=k; ++i){
        nn = product_mod(nn, (n+1-i), nmod);
        dd = product_mod(dd, (i), nmod);
    }
    i64 x,y, g;
    extended_euclid(dd, nmod, x, y, g);
    i64 t = product_mod(nn, x, nmod);
    printf("mod choose %lld %lld %lld\n", n, k, t);
    return t;
}
int main()
{
    i64 n = 10000000000000LL;
    i64 nmod = 999999937LL;
    i64 m = 1000000000000LL;
    i64 p = 10000;
    i64 prod1 = pmod(n/nmod, m/nmod, nmod);
    i64 prod2 = pmod(n%nmod, m%nmod, nmod);
    prod1 = product_mod(prod1, prod2, nmod);
    prod2 = pmod(m%nmod, p, nmod);
    prod1 = product_mod(prod1, prod2, nmod);
    prod1 = product_mod(prod1, (m-p), nmod);
    i64 x, y, g;
    extended_euclid(n-p, nmod, x,y, g);
    prod1 = product_mod(prod1, x, nmod);
    i64 t = pmod(26, 13, nmod);
    printf("%lld\n", t);
    printf("%lld\n", prod1);
}
