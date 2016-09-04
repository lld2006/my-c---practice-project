#include "../lib/tools.h"
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <numeric>
//lesson, this is a stupid way of doing it. the correct approach 
//should consider how the set may
//evolve when we use inclusion-exclusion priniciple!!!! use combinatorial factors!
vector<int> nples; //gives a pair of value first is the product of 4 pairs, 
//second gives position of next prime number
vector<int> primes;
i64 limit = 9999999999999999LL;
//i64 limit = 999;

//nples just remember index
void search_all_nps(unsigned int ntotal, int currp, unsigned int cnt, vector<int> v4){
    if(cnt == ntotal){
        assert(v4.size()==ntotal);
        for(unsigned int i = 0; i < v4.size();++i)
        nples.push_back(v4[i]);
        return;
    }
    vector<int> vp1(v4);
    vp1.push_back(0);
    for(unsigned int i = currp; i < primes.size()-ntotal+1+cnt; ++i){
        vp1.back() = i;
        int cp1 = i+1;
        search_all_nps(ntotal, cp1, cnt+1, vp1);
    }
}
//how many numbers are divisible up to nupper 
i64 inc_ex_search(int pos, i64 nupper, i64 product, vector<int>& ndiv )
{
    i64 sum = 0;
    if(product >= nupper) return 0;
    for(unsigned int i = pos; i< ndiv.size(); ++i){
        if(!ndiv[i]) continue;
        i64 prod1 = product * primes[i];
        sum += nupper/prod1;
        i64 tsum = inc_ex_search(i+1, nupper, prod1, ndiv);
        sum -= tsum;
    }
    return sum;
}
//debug code
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
    primeWithin(primes, 100);
    nples.reserve(6900);
    vector<int> v4, vall, vt;
    vall.resize(25, 1); //primes less than 100
    vt = vall;
    struct timer mytimer;
    i64 n100 = inc_ex_search(0,limit, 1, vall);//non divisible
    printf("%.4f\n", mytimer.getTime());
    i64 sum = 0;
    for(unsigned int ni = 1; ni <4; ++ni){
        nples.clear();
        search_all_nps(ni, 0, 0, v4);
        printf("ni %d %d\n", ni, static_cast<int>(nples.size()));
        for(unsigned int i = 0; i < nples.size()/ni; ++i){
            vt = vall; 
            i64 prod = 1;
            for(unsigned int ix = ni * i; ix < ni*(i+1); ++ix){
                prod *=  primes[nples[ix]];
                vt[nples[ix]] = 0;
            }

            i64 nlimit = limit/prod;
            i64 tp = (nlimit - inc_ex_search(0, nlimit, 1, vt));
            //printf("%lld %lld %lld\n", prod, tp, nlimit);
            sum += tp;
        }
    }
    printf("%lld %lld %lld\n", n100, sum, n100-sum);
}
