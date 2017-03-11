#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <cassert>
//first for a square, find the prime factors of square+1
//then find all factor pairs of square + 1
//lesson, the limit for p, assume p is the smallest number of all 3, should be less than 150000
i64 sum = 0;
int pmax = 75000000;
void special_factor(int limit, vector<vector<i64>>& factors){
    factors.clear();
    factors.resize(limit+1);
    vector<i64> sieves;
    sieves.resize(limit+1);
    for(i64 i = 0; i < static_cast<i64>(sieves.size()); ++i){
        sieves[i] = i*i+1;
    }
    i64 jstart  =0;
    // we do not need all numbers factor
    for( i64 i = 1; i < static_cast<i64>(sieves.size()); ++i){
        if(sieves[i] == 1) continue;
        i64 px = sieves[i];
        if(i & 1) jstart = i + px;
        for(i64 j = i; j < static_cast<i64>(sieves.size()); j += px){
            factors[j].push_back(px);
            assert(sieves[j] % px == 0);
            do {
                sieves[j] /= px;
            }while(sieves[j]%px==0);
        }
    }
}

void dfs(i64 n, unsigned int facidx, i64 div1, i64 div2, const vector<i64>& ifac){
    //div2 = c+ b div1 = c-b
    if(div1 > n|| div1 > div2) return;
    if(facidx == ifac.size()) {
        if((div1 ^ div2) & 1 ){ 
            return;
        }else{
            assert(div1 * div2 == n*n+1);
            i64 b = (div2 - div1)/2;
            i64 c = (div2 + div1)/2;
            if( b < n ) return;
            if(n+b + c > pmax) return;
            //printf("%lld %lld %lld\n", n, b, c);
            ++sum;
        }
        return;
    }
    dfs(n, facidx+1, div1, div2, ifac);
    i64 px = ifac[facidx];
    while(div2%px ==0){
        div1*=px;
        div2/=px;
        dfs(n, facidx+1, div1, div2, ifac);
    }
}

int main()
{
    int limit = pmax/(2+sqrt(2.0));
    vector<vector<i64>> factors;
    special_factor(limit, factors);
    for( i64 i = 2; i<=limit; i+=2){
        dfs(i, 0, 1LL, i*i+1, factors[i]);
    }
    printf("%lld\n", sum);
}
