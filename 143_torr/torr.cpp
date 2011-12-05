#include <map>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <set>
#include "../lib/typedef.h"
using namespace std;
typedef multimap<int, int>::iterator miter;
typedef pair<miter, miter> miterpair;
int main(){
    set<int> valueset;
    int limit = 120000;
    i64 sum = 0;
    vector<pair<int, int> > mvec;
    mvec.reserve(4000000);
    int sql = sqrt((double)limit);
    //u>v
    for(i64 v = 1; v < sql; ++v){
        for(i64 u = v+1; u< limit; ++u){
            i64 pf = u*u -v *v;
            i64 qf = v*v+2*u*v;
            if(pf > limit) continue;
            if(qf > limit) continue;
            assert(pf > 0);
            assert(qf > 0);
            unsigned int mx = pf > qf? limit/qf : limit/pf;
            for(unsigned int i = 1; i < mx ; ++i){
                mvec.push_back(make_pair<int, int>(pf*i, qf*i));
                mvec.push_back(make_pair<int, int>(qf*i, pf*i));
            }
        }
    }
    sort(mvec.begin(), mvec.end());
    vector<pair<int, int> >::iterator vi = unique(mvec.begin(), mvec.end());
    mvec.resize(vi-mvec.begin());
    multimap<int, int> mtorr(mvec.begin(), mvec.end());
    printf("%u\n", mtorr.size());
    //search triples
    for(miter iter = mtorr.begin(); iter!=mtorr.end(); ++iter){
        int vp = iter->first;
        int vq = iter->second;
        if(vp >= vq) continue;
        miterpair mp = mtorr.equal_range(vq);
        miter iter1 = mp.first;
        miter iter2 = mp.second;
        for( ; iter1!= iter2; ++iter1){
            int vr = iter1->second;
            if( vq >= vr) continue;
            miterpair mp2 = mtorr.equal_range(vr);
            miter itera = mp2.first;
            miter iterb = mp2.second;
            for( ; itera != iterb; ++itera){
                if(itera->second == vp && vp + vq + vr <= limit){
                    assert(vp < vq && vq < vr);
                    valueset.insert(vp+vq+vr);
                    printf("%d %d %d \n", vp, vq, vr);
                    break;
                }
            }
        }
    }
    for(set<int>::iterator iter = valueset.begin(); iter != valueset.end(); ++iter)
        sum += *iter;
    printf("%lld\n", sum);
}
