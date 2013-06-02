#include <cstdio>
#include "../lib/typedef.h"
#include <cassert>
i64 nchoosek(i64 n, i64 k)
{
    if(k==0) return 1;
    assert(n > 0 );
    if(2*k > n)
        k = n - k;
    i64 prod = 1;
    for(unsigned int i = 1, j=n; i <= k; ++i, --j){
        prod *= j;
        prod/= i;
    }
    return prod;
}
int main()
{
    int ntot = 50;
    i64 sum = 1;
    for( int i = 1; i<= (ntot+1)/4; ++i){
        int nleft = ntot - 4*i+1;
        int slot = 2*i+1;
        sum += nchoosek(slot+ nleft - 1, nleft);
    }
    printf("%lld\n", sum);
}
