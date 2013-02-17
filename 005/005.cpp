#include <cstdio>
#include <cstdlib>
#include "../lib/tools.h"
int main(int argc, char** argv)
{
    if(argc < 2)
        printf("need nmax\n");
    int nmax=atoi(argv[1]);
    vector<int> primes;
    primeWithin(primes, nmax);
    double l20 = log(nmax);
    i64 prod = 1;
    for(unsigned int i = 0; i < primes.size(); ++i){
        
        int np = l20/log(primes[i]);
        prod *= power(primes[i], np);
    }
    printf("%lld\n", prod);
}
