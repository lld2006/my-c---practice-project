#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
i64 stot = 0;
i64 sroot, smax;
void check_period(i64 num, vector<i64>& vn)
{
    vn.clear();
    i64 root = sqrt(num);
    if(root * root == num) 
        return;
    //initialization nt
    i64 nt = root;//nt is the number in the numerator
    //negative sign is not included
    i64 stop = root * 2;
    i64 q = root; // the integer part for each step
    i64 den = 1; //initialization of denominator 
    vn.push_back(q);
    while(q != stop){
        assert((num - nt * nt) % den == 0);
        den = (num - nt * nt)/den;
        q = (root + nt)/ den;
        nt =  q * den - nt;
        vn.push_back(q);
    }
}
void find_solutions(i64 num, vector<i64>& vn)
{
    i64 u1=1, v1=0;
    i64 u2=vn[0], v2 = 1;
    i64 u=0, v=0;
    int pos = 1;
    int nsize = vn.size();
    i64 n2 = num * num;
    while(u <= smax){
        assert(pos < nsize);
        u = vn[pos]*u2+u1;
        v = vn[pos]*v2+v1;
        u1 = u2;
        v1 = v2;
        u2 = u;
        v2 = v;
        if((u & 1) == 0 && v > num){
            i64 m = num * v;
            i64 m1 = u + m;
            i64 m2 = u - m;
            i64 result = m1*m2-v*v;
            if(result == n2)
                stot += u;
        }
        ++pos;
        if(pos == nsize)
            pos = 1;
    } 
}

int main()
{
    sroot = 1000;
    smax = sroot * sroot;
    i64 bmax = sqrt(2.0)*sroot;
    vector<i64> vn;
    for(i64 b = 2; b<=bmax; b+=2){
        check_period(b*b+1, vn);     
        find_solutions(b, vn);
    }
    printf("%lld\n", stot);
}

//    i64 limit = 1000000;
//    i64 pmax = limit/(sqrt(2.0));
//    i64 sum = 0;
//    int inc = 0;
//    for(i64 p = 1; p <= pmax; ++p){
//        if(p %2 == 1) 
//            inc = 2;
//        else
//            inc = 1;
//        for(i64 q=p+1; q<= limit; q+=inc){
//            i64 result = p*p+q*q+(p*q)*(p*q)*4;
//            i64 root = round(sqrt(result));
//            if(root > 1e6) break;
//            if(result == root*root){
//                //printf("%lld %lld %lld\n", 2*p, 2*q, root-2*p*q);
//                sum += root;
//            }
//        }
//    }
//    printf("%lld\n", sum);
