#include "../lib/tools.h"
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <numeric>
//lesson, this is a stupid way of doing it. the correct approach 
//should consider how the set may
//evolve when we use inclusion-exclusion priniciple!!!! use combinatorial factors!
//second gives position of next prime number
vector<int> primes;
i64 sum = 0;
i64 limit = 9999999999999999LL;
i64 inc_ex_search(int pos, i64 nupper, i64 product, vector<int>& ndiv );

void search_all_nps(unsigned int ntotal, int cpos, unsigned int cnt, int prod, vector<int>& vall){
    if(cnt == ntotal){
        //it is time to find all numbers that can be divided 
        //by any number in allowed vall
        sum += (limit/prod -inc_ex_search( 0, limit/prod, 1, vall));
        return;
    }
    for(unsigned int i = cpos; i < primes.size(); ++i){
        int prod1 = prod * primes[i];
        vall[i] = 1;
        search_all_nps(ntotal, i+1, cnt+1, prod1, vall);
        vall[i] = 0;
    }
}
//
//how many numbers are divisible by primes up to nupper 
i64 inc_ex_search(int pos, i64 nupper, i64 product, vector<int>& ndiv )
{
    i64 sum = 0;
    if(product >= nupper) return 0;
    for(unsigned int i = pos; i< ndiv.size(); ++i){
        if(ndiv[i] == 1) continue;
        i64 prod1 = product * primes[i];
        sum += nupper/prod1;
        i64 tsum = inc_ex_search(i+1, nupper, prod1, ndiv);
        sum -= tsum;
    }
    return sum;
}
//debug code, non divisible numbers by primes in ndiv
//i64 verify(int nupper, vector<int>& ndiv)
//{
//    vector<int> flags;
//    flags.resize(nupper+1, 1);
//    flags[0] = 0;
//    for(unsigned int i = 0; i<ndiv.size(); ++i){
//        int xd =ndiv[i];
//        for(int xi = xd; xi <= nupper; xi+=xd)
//            flags[xi]=0;
//    }
//    return accumulate(flags.begin(), flags.end(), 0);
//}
int main()
{
    //limit = 999;
    primeWithin(primes, 100);
    vector<int> vall;
    vall.resize(25, 0); //primes less than 100
    struct timer mytimer;
    i64 n100 = inc_ex_search(0,limit, 1, vall);// divisible
    printf("%.4f\n", mytimer.getTime());
    for(unsigned int ni = 1; ni <4; ++ni)
        search_all_nps(ni, 0, 0, 1, vall);
    
    printf("%lld %lld %lld\n", n100, sum, n100-sum);
}
