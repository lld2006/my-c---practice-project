// factor a^2-1  then find all divisors and find qualified b and c 
// with in the limit
#include <cstdio>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdlib>

int main()
{
   i64 value = 600851475143LL/71/839/1471; 
   i64 seed = rand() % value;
   i64 fac = pollard_rho(value, seed, 0); 
   printf("%lld\n", fac);
}
