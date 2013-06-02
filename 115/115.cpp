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
i64 calc_tot(int ntot, int rmin)
{
    i64 sum = 1;
    for( int i = 1; i<= (ntot+1)/(rmin+1); ++i){
        int nleft = ntot - (rmin+1)*i+1;
        int slot = 2*i+1;
        sum += nchoosek(slot+ nleft - 1, nleft);
    }
    return sum;
    //printf("%lld\n", sum);
}
int main()
{
    for(unsigned int i = 1; i; ++i){
        i64 result = calc_tot(i, 50);
        printf("%d %lld\n", i, result);
        if(result > 1000000)
            return 0;
    }
}
