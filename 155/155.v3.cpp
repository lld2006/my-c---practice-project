#include <set>
#include <cstdio>
#include <bitset>
#include "../lib/rational.h"
const int msize = 5000;
vector<bool> vmap;
void dbgset(set<rational>& cset)
{
    for(auto iter = cset.begin(); iter!=cset.end(); ++iter){
        printf("%lld, %lld\n", iter->pnum(),iter->pden());
    }
}
void insert(const IntPair& pr, vector<IntPair>& vp)
{
    int pos = pr.first*msize+pr.second;
    assert(pr.first < msize && pr.second < msize);
    if(vmap[pos]) return;
    vmap[pos]= true;
    vp.push_back(pr);
}
void find_all(vector<IntPair>& cset, vector<IntPair>& s1, vector<IntPair>& s2)
{
    for(auto iter = s1.begin(); iter != s1.end(); ++iter){
        rational r1 = rational(iter->first, iter->second, 1, 0);
        for(auto iter2 = s2.begin(); iter2 !=s2.end(); ++iter2){
            rational r2 = rational(iter2->first, iter2->second, 1, 0);
            rational result = r1 + r2; 
            if(result > 1) 
                insert(IntPair(result.pden(), result.pnum()), cset );
            else
                insert(IntPair(result.pnum(), result.pden()), cset);
            result = rational(iter->first*(iter2->first), iter->second*(iter2->first ) + iter->first*(iter2->second));
            insert(IntPair(result.pnum(), result.pden()), cset);
            result = rational(iter->first*(iter2->second), iter->second*(iter2->second ) + iter->first*(iter2->first));
            insert(IntPair(result.pnum(), result.pden()), cset);
            result = rational(iter2->first*(iter->second), iter->second*(iter2->second) + iter->first*(iter2->first));
            insert(IntPair(result.pnum(), result.pden()), cset);
        }
    }
}
int main()
{
    int target = 20;
    vector<vector<IntPair>> vset;
    vset.resize(target+1);
    vset[1].push_back(IntPair(1,1));

    //for each level
    for(int n=2; n<=target; ++n){
        vmap.clear();
        vmap.resize(msize*msize, false);
        vector<IntPair>& cset=vset[n-1];
        printf("%d %zu\n", n-1, cset.size());
        for(int n1 = 1; n1 <= n/2; ++n1)
            find_all(vset[n], vset[n1], vset[n-n1]);
    }

    vmap.clear();
    vmap.resize(msize*msize, false);
    
    int cnt = 0;
    for( int i = 3; i<=target; ++i){
        for(auto iter = vset[i].begin(); iter != vset[i].end(); ++iter){
            if(!vmap[iter->first*msize+iter->second]){
                vmap[iter->first*msize+iter->second]= true;
                ++cnt;
            }
        }
    }
    printf("%d %d\n", target, cnt*2-1);
}
