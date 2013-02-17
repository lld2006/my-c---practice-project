#include <cstdio>
#include "../lib/tools.h"
int main()
{
    int nlimit = 150000;
    int target = 10001;
    vector<int> primes;
    primeWithin(primes, nlimit);
    printf("%d\n", primes[target-1]);
}
