#include <cmath>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <set>
#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <unordered_map>
using namespace std;
typedef unordered_map<int, set<int>> hashmap;

void intersection(set<int>& s1, set<int>& s2, set<int>& s)
{
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(s, s.end()));
}

void hashmap_insert(int a, int b, hashmap& hmap)
{
    auto iter = hmap.find(a);
    if(iter == hmap.end()){
        iter = hmap.insert(make_pair(a, set<int>())).first;
    }
    (iter->second).insert(b);
    //iter = hmap.find(b);
    //if(iter == hmap.end()){
    //    iter = hmap.insert(make_pair(b, set<int>())).first;
    //}
    //(iter->second).insert(a);
    
}
void dbgset( set<int>& nset)
{
    for(auto iter = nset.begin(); iter != nset.end(); ++iter)
        printf("%d\n", *iter);
}
int main()
{
    hashmap hmap;
    set<int> valueset;
    int limit = 120000;
    //limit = 10000000;
    int l3 = limit/3;
    i64 sum = 0;
    int sql = sqrt((double)limit);
    //u>v
    for(i64 v = 1; v < sql; ++v){
        for(i64 u = v+1; u< limit; ++u){
            i64 pf = u*u -v*v;
            i64 qf = v*v+2*u*v;
            if(pf > qf)swap(pf, qf);
            if(pf + qf > limit) break;
            assert(pf > 0 && qf > 0 && pf < qf);
            
            for( int i = 1, nv = qf; nv <= limit; ++i, nv+= qf){
                hashmap_insert(pf*i, qf*i, hmap);
            }
        }
    }
    //search triples
    for(auto iter = hmap.begin(); iter!=hmap.end(); ++iter){
        int vp = iter->first;
        if(vp > l3 ) continue;
        set<int>& pset = iter->second;
        for(auto iter2 = pset.begin(); iter2 != pset.end(); ++iter2){
            int vq = *iter2;
            auto hiter2 = hmap.find(vq);
            if(hiter2 == hmap.end()) continue;
            set<int>& qset = hiter2->second;
            set<int> section;
            intersection(pset, qset, section);
            for(auto iter3 = section.begin(); iter3 != section.end(); ++iter3){
                int vr = *iter3;
                int sum  = vp + vq + vr;
                if(sum <= limit)
                    valueset.insert(sum);
            }
        }
    }
    for(set<int>::iterator iter = valueset.begin(); iter != valueset.end(); ++iter){
        i64 value = *iter;
        sum += value;
    }
    printf("%lld\n", sum);
}
