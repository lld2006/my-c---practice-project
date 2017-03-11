#include <cstdio>
#include "../lib/tools.h"
i64 find_root_n(const IntPairVec& vpairs)
{
    i64 prod = 1;
    for(unsigned int  i = 0; i < vpairs.size(); ++i){
        int base = vpairs[i].first;
        int pwr = vpairs[i].second;
        if(pwr == 1) continue;
        pwr >>= 1;
        prod *= power(base, pwr);
    } 
    return prod;
}
int main()
{
    int limit = 100000000;
    vector<int> primes;
    primeWithin(primes, limit);
    vector<bool> vflags;
    vflags.resize(limit+1, false);
    for(unsigned int i = 0; i < primes.size(); ++i ){
        int index = primes[i];
        vflags[index] = true;
    }
    vector<int> ftable;
    factor_table_min(limit, ftable);
    i64 sum = 0;
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        //consider each prime number
        int g0 = px + 1;
        IntPairVec vpairs;
        factor_using_table(g0, vpairs, ftable);
        i64 nroot= find_root_n(vpairs);
        i64 nsquare = nroot * nroot;
        bool notDone = true;
        g0/=nsquare;
        int mult = nroot + 1;
        while(notDone){
            int g1 = g0 * mult * nroot;
            int g2 = g0 * mult * mult;
            if(g2 >= limit) break;
            if(vflags[g1-1] && vflags[g2-1]){
                sum += px + g1-2 + g2;
                //printf("%d %d %d\n", px, g1-1, g2-1);
            }
            ++mult;
        }
    }
    printf("%lld\n", sum);
}
