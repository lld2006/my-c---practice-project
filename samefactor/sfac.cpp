#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <vector>
#include <cstdio>

int main()
{
    int limit=3200;
    vector<int> primes, nfac;
    primeWithin(primes, limit);
    I64PairVec ifac;
    int prevdiv = 1;
    int count = 0;
    for(int i = 2; i<= 100; ++i){
        if(i%1000000==0)printf("%d\n", i);
        factor(i, ifac, primes);
        int div = 1;
        for(unsigned int j = 0; j < ifac.size(); ++j)
                div *= (ifac[j].second+1);
        if(div == prevdiv){
            printf("%d\n", i);
            ++count;
        }
        prevdiv = div;
    }
    printf("%d\n", count);
}
