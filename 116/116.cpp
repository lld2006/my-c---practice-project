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
    i64 total = 0;
    for(int i = 1; 2*i<=50; ++i){
        int j = 50-2*i;
        total += nchoosek(i+j, i);
    }
    
    for(int i = 1; 3*i<=50; ++i){
        int j = 50-3*i;
        total += nchoosek(i+j, i);
    }
    for(int i = 1; 4*i<=50; ++i){
        int j = 50-4*i;
        total += nchoosek(i+j, i);
    }
    printf("%lld\n", total);
}
