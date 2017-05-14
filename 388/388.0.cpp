#include <cstdio>
#include <unordered_map>
#include "./primecount.hpp"
#include "../lib/tools.h"
int64_t nmod = 1000000000L;
int64_t nmax = 1000000;
int64_t root = 0;
vector<int> pitable;
unordered_map<int64_t, int64_t> countHash;
int64_t internalCnt(int pIndex, int64_t prod, vector<int>& primes,vector<int>& pitable );
int64_t myprimecount(int64_t n)
{
    if(n<=(int)pitable.size()-1)
        return pitable[n];
    auto iter = countHash.find(n);
    if(iter == countHash.end()){
        int64_t ncnt = primecount::pi(n);
        countHash[n] = ncnt;
        return ncnt;
    }
    return iter->second;
}
int64_t ncube(int64_t n)
{
    if(n==0) return 0L;
    int64_t t = multmod(n+1, n+1, nmod);
    t = multmod(t, n+1, nmod)-1;
    return t;
}
//for prime product <= root
int64_t recCount(int pIndex, int64_t prod, vector<int>& primes,vector<int>& pitable )
{
    if(prod * primes[pIndex] > nmax) return 0;
    //printf("search prime=%d prod=%ld\n", primes[pIndex], prod);
    if(prod > nmax) return 0;
    int64_t sum = 0;
    for(unsigned int i = pIndex+1; i < primes.size(); ++i){
        if(primes[i] * prod > nmax) break;
        sum += internalCnt(i, prod, primes, pitable);
        sum -= recCount(i, prod, primes, pitable);
    }
    return sum;
}
//cnt the number^3 from pIndex to n
//assume only need the last factor
//
//this is the counting function for each product like pi * pj * {pk, pk+1, pk+2...}
//pi pj is already saved in prod, and pIndex is the index of next prime
int64_t internalCnt(int pIndex, int64_t prod, vector<int>& primes,vector<int>& pitable )
{
    if(prod * primes[pIndex] > nmax) return 0;
    assert(prod % primes[pIndex] != 0);
    int64_t k, sum = 0;
    int64_t n = nmax/prod;
    int64_t root = sqrt(n);
    //root has been considered here!!!!
    for( k = pIndex; k<(int)primes.size() && primes[k] <= root; ++k){
        sum = addmod(sum ,ncube(n/primes[k]), nmod);
    }
    //now for numbers bigger than root
    int64_t nprev = myprimecount(n);
    //int64_t nc= 0;
    for(int64_t i = 2; i<=n/root; ++i){
        int64_t t = n/i;
        if(pIndex > 0)
            t = max(t, (int64_t)primes[pIndex-1]);
        int64_t nc = myprimecount(t); //i-1 to i
        if(nc> nprev) break;
        sum =addmod(sum,  (nprev - nc)*ncube(i-1), nmod);
        nprev = nc;
    }
    return sum;
}
int64_t ndcount(int64_t nx, vector<int>& primes, vector<int>& pitable)
{
    int64_t n0 = internalCnt(0, 1LL, primes, pitable);
    int64_t root = sqrt(nmax);
    for(unsigned i = 0; i < primes.size() && primes[i]<=root; ++i){
        n0 -=  recCount(i, primes[i], primes, pitable);
    }
    return n0;
}
int main(int argc, char* argv[])
{
    if(argc==2){
        nmax = atol(argv[1]);
    }
    int nprime = 100000000;
    if(nmax <= nprime){
        nprime = nmax/100;
        if(nprime < 10) nprime = 10;
    }
    vector<int> primes;
    pitable.resize(nprime+1);
    sievePrimes(nprime, primes);
    int index = 0;
    int cnt = 0;
    int psize = primes.size();
    for(int i = 0; i < (int)pitable.size(); ++i){
        if(index < psize && i == primes[index]){
            ++cnt;
            pitable[i] = cnt;
            ++index;
        }else{
            pitable[i] = cnt;
        }
    }
    //initialize root value
    root = sqrt(nmax);
    //preparation done
    int64_t result = ncube(nmax);
    result -= ndcount(nmax, primes ,pitable);
    printf("%ld\n", result);
}
