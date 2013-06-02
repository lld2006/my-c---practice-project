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
void pell_negative(int num, vector<int>& vroot)
{
    i64 p0 = vroot[0], q0 = 1;
    i64 p1 = (vroot[0]*vroot[1]+1);
    i64 q1 = vroot[1];
    i64 p2 = 1, q2 = 1;

    vroot.erase(vroot.begin());
    int vsize = vroot.size();
    int r = vsize - 1;
    int s = 1;
    //int final = (r & 1)? r: 2*r+1;
    //for(int s = start; s <= final; ++s){
    while(true){
        int idx = (s-1)%vsize;
        int value = vroot[idx];
        p2 = p1 * value + p0;
        q2 = q1*value + q0;
        p0 = p1; q0 = q1; 
        p1 = p2; q1 = q2;
        ++s;
        //if(s% r == 0)
        if((p1 % 2 == 1) &&( q1 % 2== 1))
            printf("%lld %lld\n", (p1+1)/2, (q1+1)/2 );
        if(p1 > 1e12)
            break;
    }
    return;
}
//max_dig_pell was destroyed accidentally. 
//check wolfram page if necessary
int main()
{
    vector<int> vroot;
    check_period(2, 1, vroot);
    pell_negative(2, vroot);
}

