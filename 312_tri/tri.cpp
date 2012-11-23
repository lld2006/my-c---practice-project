#include <cstdio>
#include <set>
#include <cassert>
#include "../lib/tools.h"
using namespace std;
vector<int> primes{2,3,5,7,11,13};
i64 nmod = 815730721LL;
//2^(3^(n-2)) mod 13^8
int f2(int n, int mod)
{
    i64 mod1 = totient(mod, primes);
    assert(mod1 %3 == 0);
    mod1 /= 3;
    i64 mod2 = totient(mod1, primes);
    int na = n -3;
    na %= mod2;
    int result = powermodule(3, na, mod1);
    result *= 3;
    return powermodule(2, result, mod);
}
//3^((3^(n-2)-3)/2)
int f3(int n, int mod)
{
    i64 mod1 = totient(mod, primes)*2;
    i64 mod2 = totient(mod1, primes);
    int nb = n -2;
    nb %= mod2;
    int result = powermodule(3, nb, mod1);
    assert(result % 2 == 1);
    result = (result - 3)/2;
    return powermodule(3, result,mod); 
}
int c1(i64 n, i64 mod)
{
   i64 a1 = f2(n, mod); 
   i64 b1 = f3(n, mod); 
   i64 c1 = a1 * b1;
   c1 %= mod;
   return c1;
}
int c2(i64 n, i64 mod)
{
    int mod1 = totient(mod, primes);
    int nexp = c1(n, mod1);
    return c1(nexp, mod);

}
int c3(i64 n, i64 mod)
{
    int mod1 = totient(mod, primes);
    i64 nexp = c2(n, mod1);
    return c1(nexp, mod);
}

int main()
{
    i64 result =  c3(10000, nmod);
   printf("%lld\n", result % nmod);
}
