#include "../lib/typedef.h"
#include <cstdio>
int main()
{
    int nmod = 29;
    for(i64 i = 2; i<=nmod-1; ++i){
        i64 prod = i;
        for(i64 npow = 2; npow <= nmod-1; ++npow){
            prod *= i;
            prod %= nmod;
            if(prod == 1){
                printf("%lld %lld\n", i, npow);
                break;
            }
        }
    }
}
