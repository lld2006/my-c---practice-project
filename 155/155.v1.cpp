#include <set>
#include <cstdio>
#include "../lib/rational.h"
void dbgset(set<rational>& cset)
{
    for(auto iter = cset.begin(); iter!=cset.end(); ++iter){
        printf("%lld, %lld\n", iter->pnum(),iter->pden());
    }
}
void find_all(set<rational>& cset, set<rational>& s1, set<rational>& s2)
{
    for(auto iter = s1.begin(); iter != s1.end(); ++iter){
        for(auto iter2 = s2.begin(); iter2 !=s2.end(); ++iter2){
            rational result = (*iter) + (*iter2);
            cset.insert(result);
            result = rational(iter->pnum()*(iter2->pnum()), iter->pden()*(iter2->pnum() ) + iter->pnum()*(iter2->pden()));
            cset.insert(result);
        }
    }
}
int main()
{
    int target = 18;
    vector<set<rational>> vset;
    vset.resize(target+1);
    vset[1].insert(rational(1,1));
    for(int n=2; n<=target; ++n){
        set<rational>& cset=vset[n-1];
        printf("%d %zu\n", n-1, cset.size());
        for(int n1 = 1; n1 <= n/2; ++n1)
            find_all(vset[n], vset[n1], vset[n-n1]);
    }
    for( int i = 3; i<=target-1; ++i){
        for(auto iter = vset[i].begin(); iter != vset[i].end(); ++iter){
            vset[target].insert(*iter);
        }
    }
        printf("%d %zu\n", target, vset[target].size());
}
