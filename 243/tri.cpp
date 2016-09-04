#include <cstdio>
#include "../lib/tools.h"
int main()
{
    vector<int> primes;
    int limit = 400;
    primeWithin(primes, limit);
    i64 prod = 1, prod2 = 1, prev_prod;
    long double prev_ratio = 1, curr_ratio = 1;
    //23 is still large, but 29 is less than the ratio. 
    //that is the reason why I quit at 8, but I made no comments
    //that is a bad habit. Now the code is better

    long double target_ratio = (long double) 15499/94744;
    for(unsigned int i = 0; i < 20; ++i){
        printf("%d ", primes[i]);
        prev_ratio = curr_ratio;
        prev_prod = prod;
        prod *= primes[i];
        prod2 *= (primes[i]-1);
        curr_ratio = (long double) prod2/(prod-1);
        printf("%30.20f %lld\n", (double)curr_ratio, prod);
        if(curr_ratio<target_ratio)
            break;
    }
    for(int i =2; i<= 29; ++i){
       long double newratio = prev_ratio * i * (prev_prod-1)/(i*prev_prod-1);
       if(newratio < target_ratio){
            prev_prod  *=  i;
            printf("%lld\n", prev_prod);
            break;
       }
    }
}
