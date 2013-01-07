#include <cstdio>
#include "../lib/tools.h"
int main()
{
    int limit = 5000;
    vector<int> primes;
    primeWithin(primes, limit);
    i64 total = 0;
    for(unsigned int i = 0; i < primes.size(); ++i){
        for(unsigned int j = i +1; j < primes.size(); ++j){
            for(unsigned int k = j+1; k < primes.size(); ++k){
                i64 p = primes[i];
                i64 q = primes[j];
                i64 r = primes[k];
                i64 tp = 2*p*q*r-p*q-p*r-q*r;
                total += tp;
            }
        }
    }
    printf("%lld\n", total);
}
