#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <map>
//lesson learned a method to do modular arithmetics
vector<int> primes;
map<u64, u64> fibmap;
u64 nmod = 1234567891011LL;
u64 mask = (1<<20)-1;
u64 mult_mod(u64 na, u64 nb)
{
    if(na >= nmod)
        na %=  nmod;
    u64 mult = 0;
    vector<u64> vb;
    while(nb){
        u64 low = nb & mask;
        vb.push_back(low);
        nb >>= 20;
    }
    for(int i = vb.size() - 1; i >= 0; --i){
        mult <<= 20;
        if(mult >= nmod)
            mult %= nmod;
        mult += vb[i] * na;
        if(mult >= nmod)
            mult %= nmod;
    }
    return mult;
}
u64 fib_mod(u64 nfib)
{
   if(nfib == 1|| nfib == 2) 
       return 1;
   map<u64,u64>::iterator iter =fibmap.find(nfib);
   if(iter != fibmap.end())
       return iter->second;
   u64 sum = 0;
   if(nfib & 1){
        u64 half = (nfib +1)>>1;
        u64 fn1 = fib_mod(half-1);
        u64 fn = fib_mod(half);
        sum += mult_mod(fn1, fn1);
        sum += mult_mod(fn, fn);
   }else{//even
        u64 half = nfib >> 1;
        u64 fn1 = fib_mod(half-1);
        u64 fn = fib_mod(half);
        sum += mult_mod(fn, fn);
        sum += mult_mod(fn1*2, fn);
   }
   if(sum > nmod)
       sum -= nmod;
   fibmap[nfib] = sum;
   return sum;
}
int main()
{
    //u64 ix = fib_mod(12345678901LL);
    //printf("%lld\n", ix);
    //exit(1);
    i64 nstart = 1e14;
    primeWithin(primes, 10100000);
    vector<int> vnums;
    vnums.resize(4000000, 1);
    for(unsigned int ip = 0; ip < primes.size(); ++ip){
        i64 nfirst = nstart/primes[ip] *primes[ip]-nstart;
        if(nfirst < 0)
            nfirst += primes[ip];
        for(unsigned int i = nfirst; i < vnums.size(); i+=primes[ip]){
            assert(i < vnums.size());
            vnums[i] = 0;
        }
    }
    printf("prime number sifting done %lld\n", nstart);
    u64 sum = 0;
    int cnt = 0;
    unsigned int i = 0;
    while(cnt < 100000){
    //while(cnt < 1){
        if(vnums[i]==0){
            ++i;
        }else{
            sum += fib_mod(i+nstart);
            if(sum >= nmod) 
                sum -= nmod;
            ++i;
            ++cnt;
        }
        if(i==vnums.size())
            break;
    }
    if(vnums.size() == i)
        printf("error out %d\n", cnt);
    printf("%lld\n", sum);
}
