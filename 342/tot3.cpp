#include "../lib/tools.h"
#include <map>
#include <cstdio>
#include <cmath>
vector<int> primes;
vector<I64PairVec> primeFactors;
i64 limit = 10000000000LL;
i64 limit2 = 1;
//add factors for totient of p^np
void debug_map(const map<int, int>& fmap)
{
    for(auto iter = fmap.begin(); iter != fmap.end(); ++iter){
        printf("%d %d\n", iter->first, iter->second);
    }
}
int binary_search_prime_le(int px)
{
    if(px == 1)
        return -1;
    if(px > primes.back())
        return primes.size()-1;

    int low = 0;
    int high = primes.size()-1;
    int mid;
    assert(primes[low] <= px && primes[high] >= px);
    while(low < high){
        mid = (low + high)/2;
        if(primes[mid] == px)
            break;
        else if(primes[mid] < px){
            low = mid +1 ;
        }else{
            high = mid-1;
        }
        if(primes[high] <= px){
            mid = high;
            break;
        }
        if(primes[low] > px){
            mid = low-1;
            break;
        }
    } 
    assert(primes[mid] <= px && primes[mid+1] > px);
    return mid;
}
void addFactors(map<int, int>& facmap, int pindex, int np)
{
    if( np == 0) return;
    //process p-1
    int pin = primes[pindex];
    I64PairVec& vpairs = primeFactors[pindex];
    for(unsigned int i = 0; i < vpairs.size(); ++i){
        int px = vpairs[i].first;
        if(px ==1){
            assert(vpairs.size()==1);
            continue;
        }
        int npow = vpairs[i].second;
        auto iter = facmap.lower_bound(px);
        if(iter != facmap.end() && iter->first == px)
            iter->second += npow;
        else
            facmap.insert(iter, IntPair(px, npow));
    }
    if(np > 1){
        auto iter = facmap.lower_bound(pin);
        if(iter != facmap.end() && iter->first == pin)
            iter->second += np-1;
        else
            facmap.insert(iter, IntPair(pin, np-1));
    }
}
i64 search23(int cpos, i64 prod, const map<int, int>& facmap)
{
    assert(prod <= limit);
    if(cpos < 0) {// check answer
        for(auto iter = facmap.begin(); iter != facmap.end(); ++iter){
            if(iter->second %3 != 0) 
                return 0;
        }       
        //printf("%lld\n", prod);
        return prod;
    }
    i64 total = 0;
    i64 np = primes[cpos];
    i64 tp=1, p1 = prod;
    for(unsigned int i = 0; ;++i){
        p1 = prod * tp;
        if(p1 > limit) break;//exceed limit, 
        map<int, int> f1map(facmap);
        addFactors(f1map, cpos, i*2); 
        if(i != 0){
            //now check if the current prime factor is cube
            //if not continue, no need to proceed;
            if( f1map[np] %3 != 0){
                tp *= np;
                continue;
            }
        }
        i64 py = limit/p1;
        int newpos = binary_search_prime_le(py);
        if(newpos >= cpos)
            newpos = cpos - 1;
        total += search23(newpos, p1, f1map);
        tp *= np;
    }
    return total;
}
i64 search_cube(int npower)
{
    i64 total = 0;
    i64 nmax = exp(log(limit)/npower);
    if(nmax == 1) return 0;

    int mid = binary_search_prime_le(nmax);
    for(int j = mid; j >=0; --j){
        map<int, int> facmap;
        i64 prod = power((i64)primes[j] , (i64)npower);
        assert((npower*2) % 3 == 1);
        addFactors(facmap, j, npower*2);
        //first initialize the largest one
        total += search23(j-1, prod,  facmap);
    }
    return total;
}
int main()
{
    --limit;
    //limit = 100;
    i64 limit2 = sqrt(limit);
    //assert(limit2*limit2 == limit);
    //vector<int> ftable;
    vector<int> primeIndex;
    primeIndex.resize(limit2+1, 0);
    primeWithin(primes, limit2);
    //create prime indices
    for(unsigned int i = 0; i < primes.size(); ++i){
        int np = primes[i];
        primeIndex[np] = i;
    }
    //create a factor table to ease the process of factor a number
    //factor_table_min(limit2, ftable);
    //now factor all prime - 1;
    primeFactors.resize(primes.size());
    //lazy, use a inefficient way to factor numbers, not too many cost;
    for(unsigned int i = 0; i < primes.size(); ++i)
        factor(primes[i]-1, primeFactors[i], primes);
    
    i64 total = 0;
    for(unsigned int pn = 2; pn <= 33; pn+=3)
        total += search_cube(pn) ;   
    
    printf("%lld\n", total);
}
