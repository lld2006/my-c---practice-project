#include <cstdio>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cassert>
#include <algorithm>
#include <set>
void generate_pseudo_fortunate_numbers(int pos, i64 product, 
                                       const vector<int>& primes, 
                                       vector<int>& vpftn)
{
    if(product > 1000000000) return;
    vpftn.push_back(product);
    i64 p1 = product * primes[pos];
    generate_pseudo_fortunate_numbers(pos, p1, primes, vpftn);
    i64 p2 = product*primes[pos+1];
    generate_pseudo_fortunate_numbers(pos+1, p2, primes, vpftn);
}

int search_pseudo_fortune(int np, int search_pos, int& value, const vector<int>& primes){
    assert(np %2 ==0);
    int isearch = search_pos;
    do{
        assert(isearch > 0 && isearch < static_cast<int>(primes.size()));
        if(primes[isearch] > np){
            if(primes[isearch] == np+1){
                value = primes[++isearch] - np;
                return isearch;
            }else if(primes[isearch] >np+1){
                if(primes[isearch - 1] <= np +1 ){
                    value = primes[isearch] - np;
                    return isearch;
                }else{
                    --isearch;
                }
            }
        }else{
            ++isearch;
        }
    }while(true);
    assert(0);
    return isearch;
}
int main()
{
    int limit = 1000000000;
    vector<int> primes;
    set<int> vset;
    primeWithin(primes, limit);
    printf("primes generated successfully\n");
    vector<int> vpftn;
    generate_pseudo_fortunate_numbers(0, 2, primes, vpftn);
    sort(vpftn.begin(), vpftn.end());
    int search_pos = 1;
    i64 nsum = 0;
    int value = 0;
    for(unsigned int i = 0; i < vpftn.size(); ++i){
        search_pos = search_pseudo_fortune(vpftn[i], search_pos, value, primes);
        assert (value > 1);
        vset.insert(value);
    }
    set<int>::iterator iter;
    for(iter = vset.begin(); iter != vset.end(); ++iter){
        nsum += *iter;
    }
    printf("%lld\n", nsum);
}
