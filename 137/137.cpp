#include "../lib/typedef.h"
#include "../lib/int.h"
#include <cassert>
#include <cstdio>
#include <cmath>
#include <numeric>
#include <set>
using namespace std;
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
void max_dig_pell(int num, vector<int>& vroot, vector<I64Pair>& result)
{
    result.clear();
    i64 p0(vroot[0]);
    i64 q0(1);
    i64 p1(vroot[0]*vroot[1]+1);
    i64 q1(vroot[1]);
    i64 p2(1);
    i64 q2(1);
    result.push_back(I64Pair(p0,q0));
    result.push_back(I64Pair(p1,q1));

    vroot.erase(vroot.begin());
    int vsize = vroot.size();
    int start = 2;
    for(int s = start; true; ++s){
        int idx = (s-1)%vsize;
        int value = vroot[idx];
        p2 = p1*value + p0;
        q2 = q1*(value) + q0;
        p0 = p1; q0 = q1; 
        p1 = p2; q1 = q2;
        if(p1 > 1e13) break;
        result.push_back(I64Pair(p1,q1));
    }
    return ;
}
//max_dig_pell was destroyed accidentally. 
//check wolfram page if necessary
int main()
{
    vector<int> vroot;
    vector<I64Pair> result;
    int root = 2;
    check_period(5, root, vroot);
    max_dig_pell(5, vroot, result);
    set<i64> nset;
    for( int i = 1; i<= 100; ++i){
        for( int j = 1; j<= 100; ++j){
            int value = i*i-5*j*j; 
            if(value<-4) break;
            if(value == -4) 
                printf("%d %d\n", i, j);
            else
                continue;
            for(unsigned int k = 0; k < result.size(); ++k){
                i64 u = result[k].first; 
                i64 v = result[k].second;
                i64 p = i; i64 q = j;
                i64 x = p*u*u+10*u*v*q+5*p*v*v;
                i64 y = q*u*u+2*p*u*v+5*q*v*v;
                //assert(x*x -5*y*y== -4);
                if(x % 5 == 1) {
                    printf("%lld %lld\n", (x-1)/5, y);
                    assert(x != 6);
                    nset.insert(x);
                }
                p = -p;
                x = p*u*u+10*u*v*q+5*p*v*v;
                y = q*u*u+2*p*u*v+5*q*v*v;
                //assert(x*x -5*y*y== -4);
                if(x < 0) x = -x;
                if(x % 5 == 1) {
                    printf("%lld %lld\n", (x-1)/5, y);
                    assert(x != 6);
                    nset.insert(x);
                }
                
            }
        }
    }
    printf("%d\n", result.size());
    int cnt = 0;
    for(auto iter = nset.begin(); iter != nset.end(); ++iter){
        ++cnt;
        printf("set %d %lld\n", cnt, *iter/5);
    }
    return 0;
}


