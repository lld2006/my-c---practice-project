#include <cstdio>
#include "../lib/tools.h"
int main()
{
    vector<int> primes;
    primeWithin(primes, 1000000);
    for(unsigned int i = 2; i; i+=2){
        i64 np = primes[i];
        i64 p2 = np * np;
        i64 res = 2*np*(i+1);
        res %= p2;
        if(res > 1e10){
            printf("%d\n", i+1);
            break;
        }
    }
}
