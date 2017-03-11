//the pattern is amazing, why this is related to the fibonaici series?
//need to read the forum.
#include <cstdio>
#include "../lib/tools.h"
int main()
{
    i64 nmax = 1000000000000000000;
    //nmax = 100;
    i64 nmod = 100000000LL;
    vector<i64> vfibo;
    vfibo.resize(60, 0);
    vfibo[1] = 1;
    for(unsigned int i = 2; i; ++i){
        vfibo[i] = vfibo[i-1]+vfibo[i-2];
        if(vfibo[i]>nmax) break;
    }
    i64 sum = 0;
    int i ;
    for(i = 1; vfibo[i+1]<nmax; ++i){
        i64 val = (vfibo[i]-1)/2;
        val %= nmod;
        sum += val*(val+1)/2;
        sum %= nmod;
    }
    --i; // i is the maximum number that has whole segment
    //i should not be modified!
    for(int k=i-2;vfibo[k]>2;k-=2){
        i64 val = (vfibo[k]-1)/2;
        val %= nmod;
        sum += val*(val+1)/2;
        sum %= nmod;
    }
    //first part;
    i64 len = (vfibo[i+1]-1)/2;
    i64 remainder = nmax - vfibo[i+1];
    if(remainder>=len){
        len %= nmod;
        sum += len*(len+1)/2;
        remainder -= len;
    }else{
        remainder %= nmod;
        sum += remainder*(remainder+1)/2;
        sum %= nmod;
        printf("result=%lld\n", sum);
        return 0;
    }
    int k = i;
    while(remainder > 0){
        i64 upper = (vfibo[k-2]-1)/2;
        i64 lower = (vfibo[k-3]+1)/2;
        i64 len = upper-lower;
        if(remainder > len){
            len %= nmod;
            sum += len*(len+1)/2;
            remainder -= len;
        }else{
            remainder %= nmod;
            sum += remainder*(remainder+1)/2;
            sum %= nmod;
            printf("result=%lld\n", sum);
            return 0;
        }
        k-=2;
    }
}
