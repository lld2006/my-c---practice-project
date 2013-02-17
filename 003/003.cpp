#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <cmath>

int main(int argc, const char *argv[])
{
    i64 num = 600851475143LL;
    int root = sqrt(static_cast<double>(num));
    vector<int> primes;
    primeWithin(primes, root);
    I64PairVec vfac;
    factor(num, vfac, primes);
    printf("%lld\n", vfac.back().first);
    return 0;
}
