#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>
//this problem is relatively simple and straight forward
vector<i64> nfac;
int max_v = 12;//12
int ntotal = 20;//20
int ntop = 10;//10
int nsum = 70;//70
//looks like I made a correct decision, since consider large number first
//can significantly restrict the search space.
//another possible optimization is to introduce another variable minimum_in_top_10,
//once the curr value is less than it, we can immdiately stop the search. 
i64 dice_top_sum(int v_curr,int n_curr, int sum_curr, vector<int>& vstat){
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
        for( int i = v_curr; i >= 1; --i){
           int new_sum = sum_curr + i;
           int new_n = n_curr + 1;
           if( (ntop - new_n) * 1 + new_sum > nsum || (ntop-new_n)*i+new_sum < nsum)
               continue;
           ++vstat[i];
           nr += dice_top_sum(i, n_curr+1, new_sum, vstat);
           --vstat[i];
        }
    }else{//no sum constrain only value constrain, ntop is the top n numbers
        for(unsigned int i = v_curr; i >=1; --i){
            int new_v = i;
            int new_n = n_curr+1;
            ++vstat[new_v];
            nr += dice_top_sum(new_v, new_n,sum_curr, vstat);
            --vstat[new_v];
        }
    }
    return nr;
}
int main(){
    vector<int> stat;
    nfac.resize(ntotal+1, 0);
    nfac[0]=1;
    for(int i = 1; i<=ntotal; ++i)
        nfac[i] = nfac[i-1]*i;
    stat.resize(max_v+1, 0);
    i64 nf = dice_top_sum(max_v, 0, 0, stat);
    printf("%lld\n", nf);
}
