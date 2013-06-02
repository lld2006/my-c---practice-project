#include "../lib/typedef.h"
#include "../lib/int.h"
#include <cstdio>
#include <cassert>
#include <cmath>
#include <numeric>
i64 check_period(i64 num, i64 root, vector<int>& vroot)
{
    vroot.clear();
    //initialization nt
    i64 nt = root;//nt is the number in the numerator
    assert(root*root < num);
    //negative sign is not included
    i64 stop = root * 2;
    i64 q = root; // the integer part for each step
    vroot.push_back(root);
    i64 period = 0;
    i64 den = 1; //initialization of denominator 
    while(q != stop){
        assert((num - nt * nt) % den == 0);
        den = (num - nt * nt)/den;
        q = (root + nt)/ den;
        vroot.push_back(q);
        nt =  q * den - nt;
        ++period;
    }
    assert(period + 1 == static_cast<int>(vroot.size()));
    return period;
}
//only for x^2 - 2y^2= -1;
void max_dig_pell(int num, vector<int>& vroot, vector<I64Pair>& results)
{
    results.clear();
    i64 p0(vroot[0]);
    i64 q0(1);
    i64 p1(vroot[0]*vroot[1]+1);
    i64 q1(vroot[1]);
    i64 p2(1);
    i64 q2(1);
    results.push_back(I64Pair(p0,q0));

    vroot.erase(vroot.begin());
    int vsize = vroot.size();
    //int r = vsize - 1;
    int start = 2;
    for(int s = start; true; ++s){
        int idx = (s-1)%vsize;
        int value = vroot[idx];
        p2 = p1*(value) + p0;
        q2 = q1*(value) + q0;
        p0 = p1; q0 = q1; 
        p1 = p2; q1 = q2;
        if(p2 > 1e18) break;
        if((s)%(2) == 0) {
            assert(p1*p1-5*q1*q1==-1);
            results.push_back(I64Pair(p1, q1));
        }
    }
}
//max_dig_pell was destroyed accidentally. 
//check wolfram page if necessary
int main()
{
    vector<int> vroot;
    vector<I64Pair> vp;
    i64 nmax = 0;
    check_period(5, 2, vroot);
    int cnt =0;
    max_dig_pell(5, vroot, vp);
    for(unsigned int i = 0; i < vp.size(); ++i){
        i64 np = vp[i].first;
        i64 nq = vp[i].second;
        if((np%5==2) || (np%5==3)){
            printf("%lld %lld\n", np, nq);
            nmax += nq;
            ++cnt;
            if(cnt ==13)break;
        }
    }
    printf("%lld\n", nmax-1);
}

