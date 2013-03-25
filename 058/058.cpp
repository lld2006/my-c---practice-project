#include "../lib/tools.h"
#include <cstdio>
int main()
{
    int target = 50000;
    vector<int> primes;
    primeWithin(primes, target);
    int total = 1;
    int np = 0;
    for(unsigned int i = 3; i; i+=2 ){
        total += 4;
        int n0 = i*i;
        int inc = i-1;
        //if(isPrime(n0-inc, primes))++np;
        //if(isPrime(n0-inc*2, primes))++np;
        //if(isPrime(n0-inc*3, primes))++np;
        if(strong_pseudo_test(n0-inc)) ++np;
        if(strong_pseudo_test(n0-2*inc)) ++np;
        if(strong_pseudo_test(n0-3*inc)) ++np;
        if((double)np/total < 0.1){
            printf("%d \n", i);
            break;
        }
    }
}
