#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <set>
#include <cassert>
//first for a square, find the prime factors of square+1
//then find all factor pairs of square + 1
//lesson, the limit for p, assume p is the smallest number of all 3, should be less than 150000
void prime_factor_to_factor_pairs(unsigned int pos, i64 product, const I64PairVec& ifac, vector<i64>& factors){
    if(pos == ifac.size()){
        assert(product > 0);
        factors.push_back(product);
        return;
    }
    i64 base = ifac[pos].first;
    i64 pwr = ifac[pos].second; 
    for(int i = 0; i <= pwr; ++i){
        i64 x1 = power(base, (i64)i);
        assert(x1 > 0);
        prime_factor_to_factor_pairs(pos+1, product*x1, ifac, factors);
    }
}
int main()
{
    int limit = 100000;
    set<i64> vset;
    vector<int> primes;
    vector<i64> factors;
    primeWithin(primes, limit);
    I64PairVec ifac;
    for( i64 i = 1; i<=limit; ++i){
        i64 n_mult = i * i + 1;
        factor(n_mult, ifac, primes);
        int product = 1;
        factors.clear();
        prime_factor_to_factor_pairs(0, product, ifac, factors);
        int root = i;
        i64 minimum = 1e15;
        for(unsigned int j = 0; j < factors.size(); ++j){
           if(factors[j] <= root){
               i64 value = i;
               double vx = i;
               vx *= (factors[j]+i);
               vx *= (n_mult/factors[j]+i);
               if(vx <=100000000000000000LL ){
                   assert(value >0);
                    value *= (factors[j]+i);
                    value *= (n_mult/factors[j]+i);
                    vset.insert(value); 
                    if(value < minimum) minimum = value;
               }
               assert(value >= 0);
               if(i% 100000==0)
                printf("%5lld %5lld %5lld %6zu %lld\n", i,factors[j]+i, n_mult/factors[j]+i,vset.size(), value);
               //if(vset.size() == 150001) break;
           }
        }
        //printf("i = %d min is %lld\n", i, minimum);
        //if(vset.size() == 150001) break;
    }
    set<i64>::iterator iter;
    int cnt = 0;
    for(iter = vset.begin(); iter != vset.end(); ++iter){
        ++cnt;
        if(cnt == 150000)
            printf("%lld\n", *iter);
    }
}
