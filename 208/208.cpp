#include "../lib/typedef.h"
#include <cstdio>
#include <map>
#include <vector>
using namespace std;
struct penmove
{
    int np;
    int vp;
    penmove (int nx=0, int vb=20202020)
    {
        vp = vb;
        np = nx;
    }
    
};
bool operator< (const penmove& p1, const penmove& p2)
{
    return (p1.np < p2.np || (p1.np==p2.np && p1.vp < p2.vp));
}
penmove operator+ (const penmove& p1, const penmove& p2) //p1 + p2 != p2 + p1
{
    int nt = p2.np;
    int vx = p1.vp + p2.vp;
    return penmove(nt, vx);
}
bool operator==(const penmove& p1, const penmove& p2)
{
    return p1.np == p2.np && p1.vp==p2.vp;
}
bool hope(int num)
{
    int mod = 100;
    while(num){
        int res = num % mod;
        if(res < 6 || res > 34) return false;
        num /= 100;
    }
    return true;
}
void updateLevel(map<penmove, i64>& pmap, const vector<penmove>& p0)
{
    map<penmove, i64> npmap;
    for(auto iter = pmap.begin(); iter != pmap.end(); ++iter){
        if(!(hope(iter->first.vp))) continue;
        for(unsigned int i = iter->first.np; i < p0.size(); i+=5){
            penmove tp;
            tp = iter->first + p0[i];
            auto iter1 = npmap.lower_bound(tp);
            if(iter1->first==tp) 
                iter1->second += iter->second;
            else
                npmap.insert(make_pair(tp, iter->second));
        }
    }
    npmap.swap(pmap);
}
int main()
{
    vector<penmove> vp;
    vp.resize(10);
    //============left move============
    vp[0] = penmove(1, 1); 
    vp[1] = penmove(2, 100);
    vp[2] = penmove(3, 10000);
    vp[3] = penmove(4, 1000000);
    vp[4] = penmove(0,-1010101);
    //============right============ shift 5
    vp[5] = penmove(4,-1010101);
    vp[6] = penmove(0, 1);
    vp[7] = penmove(1, 100);
    vp[8] = penmove(2, 10000);
    vp[9] = penmove(3, 1000000);
    map<penmove, i64> pmap;
    penmove tp;
    pmap.insert(make_pair(tp, 1LL));
    for(int level = 1; level<=70; ++level){
        updateLevel(pmap, vp);
        //printf("%d %zu\n", level, pmap.size());
    }
    auto iter = pmap.find(tp);
    printf("%lld\n", iter->second);
}
