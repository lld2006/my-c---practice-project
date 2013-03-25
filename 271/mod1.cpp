#include <cassert>
#include <cstdio>
#include "../lib/tools.h"
#include "../lib/int2.h"
int main()
{
    vector<int> primes;
    vector<i64> candidates, newcand;
    candidates.push_back(1);
    primeWithin(primes, 45);
    i64 prod = 2, newprod = 1 ;
    for(unsigned int i = 1; i < primes.size(); ++i){
        newprod = prod * primes[i];
        newcand.clear();
        if(false){
            for(int j = 0; j < primes[i]; ++j)
                for(unsigned int k = 0; k < candidates.size(); ++k){
                    i64 num = candidates[k]+j*prod;
                    assert(num < 1e17);
                    i64 n2 = num * num;
                    n2 %= newprod;
                    i64 n3 = (n2 * num) % newprod;
                    if(n3 == 1)
                        newcand.push_back(num);
                } 
            prod = newprod;
            swap(candidates, newcand);
        }else{
            GeneralInteger pden(newprod);
            for(int j = 0; j < primes[i]; ++j){
                for( unsigned int k = 0; k < candidates.size(); ++k){
                    i64 num = candidates[k]+j*prod;
                    GeneralInteger g1(num);
                    GeneralInteger g3 = g1*g1*g1;
                    GeneralInteger remainder(1);
                    g3.divide(pden, remainder);
                    if(remainder.to_i64() == 1)
                        newcand.push_back(num);
                }
            }
            swap(candidates, newcand);
            prod = newprod;
            printf("%d %lld %d\n", primes[i], prod, candidates.size());
        }
    }
    long long int sum(0);
    for(unsigned int i = 0; i < candidates.size(); ++i)
        sum += candidates[i];
    printf("%lld\n", sum);
}
