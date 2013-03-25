#include "../lib/tools.h"
#include <cassert>
#include <cstdio>

void find_2prime_product_max(int pa, int pb, int max_th, i64 prod, bool small_only, i64& max_prod)
{
    assert(pb > pa);
    if(!small_only){ //large is OK
        i64 p2 = prod * pb;
        if(p2 <= max_th){
            if(p2 > max_prod) max_prod = p2;
            find_2prime_product_max(pa, pb, max_th, p2, small_only, max_prod);
        }
    }
    i64 p1 = prod * pa;
    if(p1 <= max_th){
        if(max_prod < p1) max_prod = p1;
        find_2prime_product_max(pa, pb, max_th, p1, true, max_prod); 
    }
}

int main()
{
    int thresh = 10000000;
    i64 sum = 0;
    vector<int> primes;
    primeWithin(primes, thresh/2);
    for(unsigned int i = 0; i< primes.size(); ++i){
        int limit = thresh/primes[i];
        for(unsigned int j = i+1; j< primes.size();++j){
            if(primes[j] > limit) break;
            i64 prod = 1;
            i64 max_prod=1;
            find_2prime_product_max(primes[i], primes[j], thresh/(primes[i]*primes[j]), prod, false, max_prod);
            i64 sum1= primes[i]*primes[j]*max_prod;
            assert(sum1 <= thresh);
            sum += sum1;
        }
    }
    printf("%lld\n", sum);
}
