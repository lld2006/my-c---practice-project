#include <set>
#include <cstdio>
#include "../lib/rational.h"
void dbgset(set<rational>& cset)
{
    for(auto iter = cset.begin(); iter!=cset.end(); ++iter){
        printf("%lld, %lld\n", iter->pnum(),iter->pden());
    }
}
void find_all(set<IntPair>& cset, set<IntPair>& s1, set<IntPair>& s2)
{
    for(auto iter = s1.begin(); iter != s1.end(); ++iter){
        rational r1 = rational(iter->first, iter->second, 1, 0);
        for(auto iter2 = s2.begin(); iter2 !=s2.end(); ++iter2){
            rational r2 = rational(iter2->first, iter2->second, 1, 0);
            rational result = r1 + r2; 
            if(result > 1) 
                cset.insert(IntPair(result.pden(), result.pnum()));
            else
                cset.insert(IntPair(result.pnum(), result.pden()));
            result = rational(iter->first*(iter2->first), iter->second*(iter2->first ) + iter->first*(iter2->second));
            cset.insert(IntPair(result.pnum(), result.pden()));
            result = rational(iter->first*(iter2->second), iter->second*(iter2->second ) + iter->first*(iter2->first));
            cset.insert(IntPair(result.pnum(), result.pden()));
            result = rational(iter2->first*(iter->second), iter->second*(iter2->second) + iter->first*(iter2->first));
            cset.insert(IntPair(result.pnum(), result.pden()));
        }
    }
}
int main()
{
    int target = 18;
    vector<set<IntPair>> vset;
    vset.resize(target+1);
    vset[1].insert(IntPair(1,1));
    for(int n=2; n<=target; ++n){
        set<IntPair>& cset=vset[n-1];
        printf("%d %zu\n", n-1, cset.size());
        for(int n1 = 1; n1 <= n/2; ++n1)
            find_all(vset[n], vset[n1], vset[n-n1]);
    }
    for( int i = 3; i<=target-1; ++i){
        for(auto iter = vset[i].begin(); iter != vset[i].end(); ++iter){
            vset[18].insert(*iter);
        }
    }
    printf("%d %zu\n", target, vset[target].size()*2-1);
}
