#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <set>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cassert>
//lesson in some if clause, some of the action need to be done in if
//but some others are common action, need to be done for all. be careful.
int limit = 1000000;

int amicableTo(int num, IntVec& primes, IntVec& amicto)
{
    I64PairVec ifac;
    if(amicto[num] != 0) return amicto[num];
    //not solved yet, need to calc
    factor(num, ifac, primes);
    int product = 1;
    for(unsigned int i =0; i < ifac.size(); ++i){
        int denom = 0;
        if(ifac[i].first < 10000){
            denom = (power(ifac[i].first, (i64)ifac[i].second+1)-1);
            assert( denom % (ifac[i].first - 1) == 0);
            denom /= (ifac[i].first - 1);
        }else{
            assert(ifac[i].second == 1);
            denom = ifac[i].first + 1;
        }
        product *= denom;
        if(product > 2 *limit) break;
    }
    assert(product > 0);
    if(product - num  > limit) 
        amicto[num] = -1;
    else
        amicto[num]= product - num;
    return amicto[num];
}
int main()
{
    unsigned int maxlength = 0;
    vector<int> primes;
    vector<int> amicto;
    amicto.resize(limit, 0);
    amicto[1] = 1;
    primeWithin(primes, limit);
    for( int i = 2; i < limit; ++i){
        set<int> chain;
        chain.clear();
        chain.insert(i);
        int from = i;
        while(true){
            int to = amicableTo(from, primes, amicto);
            if(to < 0)break;
            if(chain.insert(to).second){
                ;
            }else if(to == i){ //form an amicable chain
                if(maxlength < chain.size() ){
                    maxlength = chain.size();
                    printf("%d %d\n", i, maxlength);
                }
                break;
            }else{ // cycle but not an amicable chain
                break;
            }
            from = to;
        }
    }
}
