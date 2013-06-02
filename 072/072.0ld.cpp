#include <cstdio>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdlib>
#include <cassert>

int relprime(int num, I64PairVec& ifac)
{
    if(ifac.empty()|| (ifac.size()==1 && ifac[0].first==num)){
        return num-1;
    }
    int size = ifac.size();
    //total number of reducible
    int totalfac = 0;
    int sign = 1;
    //i number of factors
    for(int i =1; i <= size; ++i){
        IntVec comb;
        comb.resize(i);
        for(int j = 0; j < i; ++j)
            comb[j] = j;
        bool flag = true;
        while(flag){
            int facnum = 1;
            for(int ix = 0; ix < i; ++ ix)
            {
                assert(ix < comb.size());
                assert(comb[ix]<size);
                facnum *= ifac[comb[ix]].first;
            }
            totalfac += sign*(num/facnum-1);
            flag = next_combination(comb, size, i);
        }
        sign *= -1;
    }
    return num - totalfac - 1;
}

int main()
{
    int limit = 1000000;
    int limit2 = 1000;
    IntVec primes;
    I64PairVec ifac;
    primeWithin(primes, limit2);
    i64 total = 0;
    for(int i =2; i<= limit; ++i){
        factor(i, ifac, primes);
        int irreducible = relprime(i, ifac);
        total += irreducible;
    }
    printf("%lld\n", total);
}
