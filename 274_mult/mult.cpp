#include <cstdio>
#include <cassert>
#include "../lib/tools.h"
#include "../lib/typedef.h"
//this problem is extremely simple if some math is done on this problem.
//the problem is equivalently to say that find 10x==1(mod p)
int main()
{
    vector<int> primes;
    primeWithin(primes, 10000000);
    i64 x, y, gcd;
    i64 sum = 0;
    for(unsigned int i = 0; i < primes.size(); ++i){
        if(primes[i] == 2 || primes[i] == 5) continue;
        extended_euclid(10LL, primes[i], x, y, gcd);
        if(x < 0) x= primes[i]+x;
        assert( x> 0 && x< primes[i]);
        sum += x;
    }
    printf("%lld\n", sum);
}
