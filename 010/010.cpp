#include <cstdio>
#include "../lib/tools.h"
#include <numeric>
int main()
{
   int limit = 2000000; 
   vector<int> primes;
   primeWithin(primes, limit);
   i64 sum = accumulate(primes.begin(), primes.end(), 0LL);
   printf("%lld\n", sum);
}
