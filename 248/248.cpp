#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cassert>
#include <vector>
#include <cstdio>
#include <algorithm>
//find all prime candidates which are greater than 13
void search_all_prime_cand(vector<i64>& vcands, i64 prod, int level)
{
    vector<int> vp={2,3,5,7,11, 13};
    vector<int> vpow={10,5,2,1,1,1};
    if(level == 6) {
        //if(prod < 15) return;
        if(strong_pseudo_test(prod+1))
            vcands.push_back(prod+1);
        return;
    }
    i64 pm = vp[level];
    i64 tp = 1;
    for( int i = 0; i <= vpow[level]; ++i){
       search_all_prime_cand(vcands, prod*tp, level+1);
       tp *= pm;
    }
}
//2, 3, 5 need some special handling, that is, level <= 2;
//for the rest of primes, since the only possibility is p^1.
//handling is easy
void search2(int clevel, i64 prod, i64 phi, const vector<i64>& vcands, vector<i64>& vresults)
{
    if(phi==1){
        if(clevel >= 0)
            vresults.push_back(2*prod);
        
        vresults.push_back(prod);
        return;
    }
    if(clevel < 0) return;
    for(int level = clevel; level >= 0; --level){
        i64 px = vcands[level];
        if(phi > 13 && vcands[level] > phi+1) continue;
        i64 phix = px-1;
        i64 prod1 = prod;
        for(unsigned int i = 1; i; ++i ){
            if(phi % phix != 0) break;
            i64 phi1 = phi/phix;
            prod1 *= px;
            search2(level-1, prod1, phi1, vcands, vresults);
            phix *= px;
        }
    }
}
int main()
{
    i64 n13 = 6227020800LL;
    vector<int> vfac;
    vector<int> primes;
    vector<i64> vcands, vresults;
    struct timer mytime;

    search_all_prime_cand(vcands, 1, 0);
    sort(vcands.begin(), vcands.end());
    printf("%zu\n", vcands.size());

    search2(vcands.size()-1, 1, n13, vcands, vresults);
    sort(vresults.begin(), vresults.end());
    printf("%lld\n", vresults[149999]);
}
