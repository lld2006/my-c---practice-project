#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>
//this problem is relatively simple and straight forward
vector<i64> nfac;
int max_v = 12;//12
int ntotal = 20;//20
int ntop = 10;//10
int nsum = 70;//70
//int max_v = 6;//12
//int ntotal = 5;//20
//int ntop = 3;//10
//int nsum = 15;//70
i64 dice_top_sum(int v_curr,int n_curr, int sum_curr, vector<int> vstat){
    i64 nr = 0;
    if(n_curr == ntotal){
        nr = nfac[ntotal];
        for(unsigned int i = 1; i< vstat.size(); ++i){
            if(vstat[i] > 1){
                assert(vstat[i] < static_cast<int>(nfac.size()));
                nr /= nfac[vstat[i]];
            }
        }
        return nr;
    }
    if(n_curr == ntop && sum_curr != nsum) return 0;
    if(n_curr < ntop){
        for(unsigned int i = v_curr; i >= 1; --i){
           int new_sum = sum_curr + i;
           int new_v = i;
           int new_n = n_curr + 1;
           if( (ntop - new_n) * 1 + new_sum > nsum || (ntop-new_n)*new_v+new_sum < nsum)
               continue;
           vector<int> newstat(vstat);
           ++newstat[new_v];
           nr += dice_top_sum(new_v, new_n, new_sum, newstat);
        }
    }else{//no sum constrain only value constrain
        for(unsigned int i = v_curr; i >=1; --i){
            int new_v = i;
            int new_n = n_curr+1;
            vector<int> newstat(vstat);
            ++newstat[new_v];
            nr += dice_top_sum(new_v, new_n,sum_curr, newstat);
        }
    }
    return nr;
}
int main(){
//recursive? 
    vector<int> stat;
    nfac.resize(ntotal+1, 0);
    nfac[0]=1;
    for(int i = 1; i<=ntotal; ++i)
        nfac[i] = nfac[i-1]*i;
    stat.resize(max_v+1, 0);
    i64 nf = dice_top_sum(max_v, 0, 0, stat);
    printf("%lld\n", nf);
}
