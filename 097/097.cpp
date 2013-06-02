#include <cstdio>
#include "../lib/tools.h"
int main()
{
    i64 nmod = 10000000000LL;
    i64 value = powermodule(2LL, 7830457LL, nmod);
    value *= 28433LL;
    value += 1;
    value %= nmod;
    printf("%lld\n", value);
}
