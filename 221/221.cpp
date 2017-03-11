#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <set>
#include <cassert>
//first for a square, find the prime factors of square+1
//then find all factor pairs of square + 1
//lesson, the limit for p, assume p is the smallest number of all 3, should be less than 150000
void special_factor(int limit, vector<vector<i64>>& factors){
    factors.clear();
    factors.resize(limit+1);
    vector<i64> sieves;
    sieves.resize(limit+1);
    for(i64 i = 0; i < static_cast<i64>(sieves.size()); ++i){
        sieves[i] = i*i+1;
    }
    for( i64 i = 1; i < static_cast<i64>(sieves.size()); ++i){
        if(sieves[i] == 1) continue;
        i64 px = sieves[i];
        for(i64 j = i; j < static_cast<i64>(sieves.size()); j += px){
            factors[j].push_back(px);
            assert(sieves[j] % px == 0);
            do {
                sieves[j] /= px;
            }while(sieves[j]%px==0);
        }
    }
}

void dfs(i64 n, unsigned int facidx, i64 div1, i64 div2, const vector<i64>& ifac, set<i64>& nset){
    if(div1 > div2) return;
    if(facidx == ifac.size()) {
        double val = (double)(n)*(n+div1)*(n+div2);
        if(val < 5e16){
            i64 value = n*(n+div1)*(n+div2);
            assert(value > 0);
            nset.insert(value);
        }
        return;
    }
    dfs(n, facidx+1, div1, div2, ifac, nset);
    i64 px = ifac[facidx];
    while(div2%px ==0){
        div1*=px;
        div2/=px;
        dfs(n, facidx+1, div1, div2, ifac, nset);
    }
}

int main()
{
    int limit = 150000;
    set<i64> vset;
    vector<vector<i64>> factors;
    special_factor(limit, factors);
    for( i64 i = 1; i<=limit; ++i){
        dfs(i, 0, 1LL, i*i+1, factors[i], vset);
    }
    set<i64>::iterator iter;
    int cnt = 0;
    printf("set size %zu\n", vset.size());
    for(iter = vset.begin(); iter != vset.end(); ++iter){
        ++cnt;
        if(cnt == 150000)
            printf("%lld\n", *iter);
    }
}
