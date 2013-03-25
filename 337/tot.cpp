#include <cstdio>
#include "../lib/tools.h"
int limit = 20000000;
int nmod = 100000000;
int totient_with_table(int num, const vector<int>& vfac)
{
   int n1 = num;
   int result = 1;
   while(n1 > 1){
        int curr = vfac[n1];
        int pow = 0;
        int tp = 1;
        while(vfac[n1] == curr){
            ++pow;
            tp *= curr;
            n1 /= curr;
        }
        if(pow == 1)
            result *= (curr-1);
        else{
            tp /= curr;
            tp *= curr - 1;
            result *= tp;
        }
   } 
   return result;
}
int cumulative_bit(int idx, const vector<int>& tree)
{
    i64 sum = 0;
    while(idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum%nmod;
}
void update(int idx, int val,  vector<int>& tree)
{
    while(idx <= limit){
        tree[idx] += val;
        tree[idx] %= nmod;
        idx += (idx & -idx);
    }
}
int main()
{
    vector<int> vfac;
    factor_table_min(limit, vfac);
    vector<int> vtotient;
    vtotient.resize(limit+1, 0);
    for(unsigned int num = 6; num < vtotient.size(); ++num){
        vtotient[num] = totient_with_table(num, vfac);
        //printf("%d %d\n", num, vtotient[num]);
    }
    vector<int> tree;
    tree.resize(limit+1, 0);
    vector<int> vsum;
    vsum.resize(limit+1, 0);

    update(2, 1, tree);
    vsum[6] = 1;
    for(int num = 7; num < vtotient.size(); ++num){
        int ntot = vtotient[num];
        if(ntot == num-1){
            vsum[num] = vsum[num-1];
        }else{
            int n1 = cumulative_bit(ntot-1, tree);
            n1 -= vsum[ntot];
            if(n1 < 0)
                n1 += nmod;
            assert(n1 >= 0);
            update(ntot, n1, tree);
            vsum[num] = vsum[num-1] + n1;
            vsum[num] %= nmod;
        }
    }
    printf("%d %d\n", limit, vsum[limit]);
}
