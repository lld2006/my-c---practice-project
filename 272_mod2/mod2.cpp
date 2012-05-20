#include "../lib/tools.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cassert>
vector<int> cands;
i64 ntop=100000000000LL;
i64 search243(i64 prod, int cnt, int cpos)
{
    if(prod > ntop) return 0;
    if(cpos >= cands.size() && cnt < 5) 
        return 0;
    i64 sum = 0;
    i64 quote = ntop/prod;
    for(unsigned int i = cpos; i < cands.size() && cands[i] <= quote; ++i){
        i64 prod1 = prod * cands[i];
        if(prod1 > ntop) break;
        if(cnt >= 4){
            i64 nt = ntop/prod1;
            i64 tsum = nt*(nt+1)/2*prod1;
            sum -= search243(prod1, cnt+1, i+1);
            sum += tsum;
            printf("%d %lld %lld sum %lld\n",cnt, prod1, tsum, sum);
            assert(sum >= 0);
        }else{
            sum += search243(prod1, cnt+1, i+1);
        }
    }
    return sum;
}
void test(i64 np)
{
    int cnt = 0;
    for( i64 i = 1; i<np; ++i){
        if((i*i*i-1)%np==0)
            ++cnt;
    }
    printf("%lld %d\n", np, cnt);
}
int main()
{
    for(i64 i=1; i< 100; ++i){
        test(i);
    }
    exit(1);
    i64 limit = 6430000;
    ntop = 300000000;
    limit = ntop/(7*9*13*19);
    printf("%lld\n", limit);
    vector<int> primes;
    primeWithin(primes, limit);
    vector<int> pflags;
    pflags.resize(primes.size(), 0);
    for(unsigned int i = 2; i <primes.size(); ++i){
        i64 np = primes[i];
        i64 result = powermodule(np-3, (np-1)/2, np);
        pflags[i] = (result == 1);
    }
    cands.push_back(9);
    for(unsigned int i = 0; i < pflags.size(); ++i){
        if(pflags[i]) 
            cands.push_back(primes[i]);
    }
    sort(cands.begin(), cands.begin() +5);
    printf("number of primes is %zu\n", cands.size());

    printf("%d %d %d %d %d %d\n", cands[0], cands[1],cands[2],cands[3],cands[4], cands[5]);

    i64 prod = 1;
    i64 sum = 0;
    int cnt = 0, cpos = 0;
    sum = search243(prod, cnt, cpos);
    printf("%lld\n", sum);
}
