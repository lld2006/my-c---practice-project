#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>

int limit = 100000000;
vector<int> primes;
i64 inc_ex( i64 product, int cidx)
{
    i64 sum = 0;
    for(unsigned int j = cidx; j < primes.size(); ++j){
        i64 iprod = product * primes[j];
        if(iprod > limit)
            break;
        i64 mult = limit/iprod;
        sum += mult*(mult+1)/2;
        sum -= inc_ex(iprod, j+1);
    }
    return sum;
}
int main()
{
    primeWithin(primes, limit/2);
    printf("prime size %d\n", static_cast<int>(primes.size()));
    i64 sum = inc_ex(1, 0);
    printf("%lld\n", (sum)*6);
}
