#include <cstdio>
#include "../lib/tools.h"
int main(){
    vector<int> primes;
    int limit = 400000;
    double max = 10;
    int number = 0;
    primeWithin(primes, limit);
    IntPairVec ifac;
    unsigned long long int prod = 1;
    unsigned long long int prod2 = 1;
    long double ratio = 1;
    long double ratio2 = 1;
    for(unsigned int i = 0; i < 9; ++i){
        printf("%d\n", primes[i]);
        prod *= primes[i];
        prod2 *= (primes[i]-1);
        ratio = (long double) prod2 / prod;
        ratio2 = ratio *(long double) prod/(prod-1);
        printf("%30.20f %I64d\n", (double)ratio2, prod);
        if(ratio2 <(long double)15499/94744){
            //printf("%20.10f %I64d\n", ratio, prod);
            break;
        }
    }
    for(int i =2; i< 29; ++i){
       long double x = i * prod;
       if(ratio * x /(x-1) < (long double)15499/94744){
            prod  *=  i;
            printf("%I64d\n", prod);
            break;
       }
    }
}
