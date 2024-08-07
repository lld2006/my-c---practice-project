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
int max_dig_pell(int num, vector<int>& vroot)
{
    GeneralInteger p0(vroot[0]);
    GeneralInteger q0(1);
    GeneralInteger p1(vroot[0]*vroot[1]+1);
    GeneralInteger q1(vroot[1]);
    GeneralInteger p2(1);
    GeneralInteger q2(1);

    vroot.erase(vroot.begin());
    int vsize = vroot.size();
    int r = vsize - 1;
    int start = 2;
    int final = (r & 1)? r: 2*r+1;
    for(int s = start; s <= final; ++s){
        int idx = (s-1)%vsize;
        int value = vroot[idx];
        p2 = p1.multiply(value) + p0;
        q2 = q1.multiply(value) + q0;
        p0 = p1; q0 = q1; 
        p1 = p2; q1 = q2;
    }
    return p1.numberDigit();
}
//max_dig_pell was destroyed accidentally. 
//check wolfram page if necessary
int main()
{
    vector<int> vroot;
    int nmax = 0;
    int n = 0;
    for( int i = 2; i<= 100000; ++i){
        int root = sqrt(i);
        if(root * root == i) continue;
        check_period(i, root, vroot);
        int ndig =  max_dig_pell(i, vroot);
        if(ndig > nmax){
            nmax = ndig;
            n = i;
        }
    }
    printf("%d %d\n", nmax, n);
}

