#include "../lib/tools.h"
#include <cstdio>
#include <cstdlib>
i64 cycle(i64 num)
{
    while((num & 1) == 0)
        num >>= 1;
    while(num% 5 == 0)
        num /= 5;
    if(num == 1) return 0;
    if(num==3 || num==9)
        return 1;
    i64 m = 1;
    int prod = 10;
    
    while(prod != 1){
        ++m;
        prod *= 10;
        prod %= num;
    }
    return m;
}

int find_multiplicative_order(int nbase, int px, const vector<int>& vfac)
{
    IntPairVec vpairs;
    factor_using_table(px-1, vpairs, vfac);
    i64 result = 1;
    for(unsigned int i = 0; i < vpairs.size(); ++i){
        int pi = vpairs[i].first;
        int powi= vpairs[i].second;
        int yi = (px-1)/ power(pi, powi);
        int xi = powermodule((i64)nbase, (i64)yi, (i64)px);
        if(xi == 1) continue;
        i64 t = powermodule((i64)xi, pi, px );
        if(t == 1){
            result *= pi;
            continue;
        }
        int k ;
        for( k = 2; k<= powi; ++k) {
            t = powermodule((i64)t, pi, px);
            if(t == 1) 
                break;
        }
        assert(t ==1);
        result *= power(pi, k);
    }
    return result;
}

int main()
{
    int target = 100000000;
    vector<int> primes;
    vector<int> vfac;
    factor_table_min(target, vfac);
    for(unsigned int i= 2; i<vfac.size(); ++i){
        if(vfac[i] == static_cast<int>(i)) primes.push_back(i) ;
    }
    //notice we start from 7, 3 should be set to 1; TODO
    for(unsigned int i = 3; i < primes.size(); ++i){
        //if(i % 10000 == 0)
        //    printf("%d\n", primes[i]);
        int order = find_multiplicative_order(10, primes[i], vfac);
        //assert(order == cycle(primes[i]));
    }
    exit(1);
    i64 total = 0;
    for( int i = 3; i < target; ++i){
        //if(i % 10000 == 0)
        //    printf("%d\n", i);
        total += cycle(i);
    }
    printf("%lld\n", total);
}
