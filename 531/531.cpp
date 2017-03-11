//need to find out numbers between 1000000 and 1005000;
#include <vector>
#include "../lib/tools.h"
using namespace std;

//first determin has solution or not, second find pr and xr
bool m_n_has_solution(int m, int n, IntPair mPair, IntPair nPair, int mr, int nr, int& yp, int& yr)
{
    assert(mPair.first == nPair.first);
    //special handling 
    if(mPair.second == nPair.second){
        yp = power(mPair.first, mPair.second);
        int rm = mr % yp;
        int rn = nr % yp;
        if(rm != rn) return false;
        yr = rm; 
        return true;
    }
    if(mPair.second > nPair.second) {
        swap(m, n);
        swap(mPair, nPair);
        swap(mr, nr);
    }
    //now m has a smaller power Index;
    int xp = power(mPair.first, mPair.second);

    int tnr = nr;
    int tmr = mr;
    tnr %= xp;
    tmr %= xp;
    if(tnr != tmr) return false;
    yp = power(nPair.first, nPair.second);
    yr = nr % yp;
    return true;
}
//ignored that the remainder could be 0, need small modification
i64 find_remainder(int m, int n, const vector<int>& vtotients, const vector<IntPairVec>& vvpairs)
{
    IntPairVec vpr;
    i64 nmin = 1000000;
    int mIndex = 0; 
    int nIndex = 0;
    i64 common = 1;
    int msize = vvpairs[m].size();
    int nsize = vvpairs[n].size();
    int px, rx;
    while(mIndex < msize && nIndex < nsize){
        if(vvpairs[m][mIndex].first < vvpairs[n][nIndex].first){
            px = power(vvpairs[m][mIndex].first, vvpairs[m][mIndex].second);
            rx = vtotients[m] % px;
            ++mIndex;
        }else if(vvpairs[m][mIndex].first > vvpairs[n][nIndex].first){
            px = power(vvpairs[n][nIndex].first, vvpairs[n][nIndex].second);
            rx = vtotients[n] % px;
            ++nIndex;
        }else{
            int same = m_n_has_solution(m, n, vvpairs[m][mIndex], vvpairs[n][nIndex], vtotients[m], vtotients[n], px, rx);
            if(!same) return 0;
            ++mIndex;
            ++nIndex;
        }
        vpr.push_back(IntPair(px, rx));
        common *= px;
    }
    assert(mIndex == msize || nIndex == nsize);
    if(mIndex < msize)
        for(int k = mIndex; k < msize; ++k){
            px = power(vvpairs[m][k].first, vvpairs[m][k].second);
            rx = vtotients[m] % px;
            vpr.push_back(IntPair(px, rx));
            common *= px;
        }
    
    if(nIndex < nsize)
        for(int k = nIndex; k < nsize; ++k){
            px = power(vvpairs[n][k].first, vvpairs[n][k].second);
            rx = vtotients[n] % px;
            vpr.push_back(IntPair(px, rx));
            common *= px;
        }
    vector<i64> vp; 
    vector<i64> vr;
    for(unsigned int i = 0; i < vpr.size(); ++i){
        vp.push_back(vpr[i].first);
        vr.push_back(vpr[i].second);
    }
    i64 nx = chinese_remainder_theorem(vp, vr);
    nx %= common;
    assert(nx % (m+nmin) == vtotients[m]);
    assert(nx % (n+nmin) == vtotients[n]);
    return nx;
}
int main()
{
    struct timer te;
    int nmin = 1000000;
    int nmax = 1005000;
    vector<int> primes, ftable;
    primeWithin(primes, nmax);
    factor_table_min(nmax, ftable);
    vector<IntPairVec> vvpairs;
    vector<int> vtotients;
    vtotients.resize(nmax-nmin+1, 0);
    vvpairs.resize(nmax-nmin+1);
    for(unsigned int i = 0; i < vtotients.size(); ++i){
        i64 n = nmin + i;
        factor_using_table(n,vvpairs[i], ftable);
        vtotients[i] = totient_with_factor(vvpairs[i]);
    }
    printf("my time %f\n", te.getTime());   
    i64 sum = 0;
    //int cnt = 0;
    for(unsigned int i = 0; i < 5000; ++i){
        for(unsigned int j = i+1; j<5000; ++j){
            i64 val = find_remainder(i, j, vtotients, vvpairs);
            //printf("%d %d %d %d %lld\n", nmin+i, vtotients[i], nmin+j, vtotients[j], val);
            assert(val >= 0 && val < ((long)i+nmin)*((long)j+nmin));
            sum += val;
            //++cnt;
            //if(cnt == 100) return 0;
        }
    }
    printf("%lld\n", sum);
}
