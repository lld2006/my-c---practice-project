#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
#include <cassert>
#include <cstdlib>
//lesson, problem solved, but not very efficient
//fn return the value of f(n) in terms of g(n) index, so 
//this index can be used for next f(n) calculation
i64 nmax = 1000000;
struct golomb
{
    golomb(i64 ns1, i64 fn1, i64 sum1):ns(ns1), fn(fn1), sum(sum1){}
    i64 ns;//started number
    i64 fn;//gn difference
    i64 sum; //g(final) // g will be incremented evenly
};
i64 fn(i64 n, vector<golomb>& vg)
{
    assert(n <= vg.back().sum);
    int head = 0;
    int tail = vg.size()-1;
    int mid = 0;
    while(head + 1 < tail){
       mid = (head + tail)/2; 
       if(vg[mid].sum == n){
           tail = mid;
           head = mid-1;
           break;
       }
       if(vg[mid].sum < n){
           head = mid;
       }else{
           tail = mid;
       }
    }
    assert(vg[head].sum < n && vg[tail].sum >= n);
    i64 nstart = vg[tail].ns;
    i64 dn = (n - vg[head].sum)/(head+1);
    if( n == vg[head].sum + dn * (head+1)){
        nstart += dn-1 ;
    }else{
        nstart += dn;
    }
    return nstart;
}
void get_next_elem(vector<golomb>& vg)
{
    int n = vg.size();
    i64 nf = fn(n, vg); 
    i64 nstart = vg.back().ns + vg.back().fn;
    i64 nsum = vg.back().sum + nf * n;
    vg.push_back(golomb(nstart, nf, nsum));
}
int main()
{
    //nmax = 1000;
    i64 nmax2 = nmax*nmax;
    i64 nmax3 = nmax*nmax2;
    vector<golomb> vg;
    vg.push_back(golomb(0,0,0));
    vg.push_back(golomb(1,1,1));
    vg.push_back(golomb(2,2,5));
    while(vg.back().sum < nmax3){
        get_next_elem(vg);
    }
    printf("%zu\n", vg.size());
    int pos = 0;
    i64 total = 0;
    for(i64 i = 1; i < nmax; ++i){
        i64 n3 = i * i * i;
        while(vg[pos].sum < n3){
            ++pos;
        }
        i64 nstart = vg[pos].ns;
        i64 dn = (n3 - vg[pos-1].sum)/(pos);
        if(n3 == pos*dn + vg[pos-1].sum){
            //printf("%lld %lld\n", i, nstart + dn-1);
            total += nstart + dn-1;
        }else{
            //printf("%lld %lld\n", i, nstart + dn);
            total += nstart + dn;
        }
    } 
    printf("%lld\n", total);
}
