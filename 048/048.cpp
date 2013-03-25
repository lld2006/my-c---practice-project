#include <cstdio>
#include "../lib/tools.h"
int main()
{
    i64 mod = 10000000000LL;
    i64 total = 0;
    for(i64 i = 1; i <= 1000; ++i){
        total += powermodule(i, i, mod);
    }
    total %= mod;
    printf("%lld\n", total);
}
