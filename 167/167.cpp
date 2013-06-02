#include <cstdio>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <bitset>
#include "../lib/typedef.h"
//the even number of sequence (2, v) is 2, 2*v+2, where v is odd
//and v >= 5
bitset<50> ulambit;
i64 ulam(const int v, const i64 target)
{
    //the first fact is that the second even number is 2v+2
    ulambit.reset();
    //create v+1 bit for 2v+3,..., 4v+3; 
    int n1 = v/2;
    for(unsigned int i = 0; i<= v;++i){
        ulambit.set(i);
    }
    i64 period = 0;
    i64 span = 0;
    do{
        int lastbit = ulambit[0];
        int firstbit = ulambit[v];
        int result = lastbit^firstbit;
        ulambit <<= 1;
        ulambit.set(0, result);
        ulambit[v+1] = 0;
        if(result) 
            ++period;
        span += 2;
    }while(ulambit.count()<v+1);
    //printf("%d %lld %lld\n", v, period, span);
    i64 nres = (target-3)%period;
    i64 mult = (target-3)/period;
    ulambit.reset();
    ulambit.set(0);
    i64 span0 = span;
    span = v;
    period = 0;
    do{
        if(period == nres) break;
        int lastbit = ulambit[0];
        int firstbit = ulambit[v];
        int result = lastbit^firstbit;
        ulambit <<= 1;
        ulambit.set(0, result);
        ulambit[v+1] = 0;
        if(result) 
            ++period;
        span += 2;
    }while(true);
    return mult*span0+span;
}

int main()
{
    i64 nt = 100000000000LL;
    //nt = 100;
    i64 sum = 0;
    for(unsigned int a = 5; a<= 21; a +=2) {
        i64 vx= ulam(a,nt);
        //printf("%d %lld\n",a, vx);
        sum += vx;
    }
    
    printf("%lld\n", sum);
}
