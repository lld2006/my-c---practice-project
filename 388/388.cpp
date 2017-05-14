//TODO learn mobius function, I have been wasted too many opportunities to learn it!
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include "./primecount.hpp"
#include "../lib/tools.h"
//looks like for nmax = 1e10, for n/10000, it is not worthwile to calculate all
//the numbers one by one, since they are equivalent in this problem. so I will collect all the numbers 
//that should be computed to save time.
class absLess{
    public: 
        bool operator()(const i64& a, const i64& b)
        {
            return abs(a) < abs(b);
        }
};
i64 nmod = 1000000000L;
i64 nmax = 1000000;
vector<int> pitable;
unordered_map<i64, i64> countHash;
//i64 internalCnt(int pIndex, i64 prod, vector<int>& primes,vector<int>& pitable );
i64 myprimecount(i64 n)
{
    if(n<=(int)pitable.size()-1)
        return pitable[n];
    auto iter = countHash.find(n);
    if(iter == countHash.end()){
        i64 ncnt = primecount::pi(n);
        countHash[n] = ncnt;
        return ncnt;
    }
    return iter->second;
}
//ok, now pass back a double value for first 9
i64 ncube(i64 n, double& dval)
{
    if(n==0) {
        dval = 0;
        return 0L;
    }
    dval = (double)(n+1)*(n+1)*(n+1)-1;
    i64 t = multmod(n+1, n+1, nmod);
    t = multmod(t, n+1, nmod)-1;
    return t;
}
//for prime product <= root
/*
i64 recCount(int pIndex, i64 prod, vector<int>& primes,vector<int>& pitable )
{
    if(prod * primes[pIndex] > nmax) return 0;
    //printf("search prime=%d prod=%ld\n", primes[pIndex], prod);
    if(prod > nmax) return 0;
    i64 sum = 0;
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
i64 internalCnt(int pIndex, i64 prod, vector<int>& primes,vector<int>& pitable )
{
    if(prod * primes[pIndex] > nmax) return 0;
    assert(prod % primes[pIndex] != 0);
    i64 k, sum = 0;
    i64 n = nmax/prod;
    i64 root = sqrt(n);
    //root has been considered here!!!!
    for( k = pIndex; k<(int)primes.size() && primes[k] <= root; ++k){
        sum = addmod(sum ,ncube(n/primes[k]), nmod);
    }
    //now for numbers bigger than root
    i64 nprev = myprimecount(n);
    //i64 nc= 0;
    for(i64 i = 2; i<=n/root; ++i){
        i64 t = n/i;
        if(pIndex > 0)
            t = max(t, (i64)primes[pIndex-1]);
        i64 nc = myprimecount(t); //i-1 to i
        if(nc> nprev) break;
        sum =addmod(sum,  (nprev - nc)*ncube(i-1), nmod);
        nprev = nc;
    }
    return sum;
}
i64 ndcount(i64 nx, vector<int>& primes, vector<int>& pitable)
{
    i64 n0 = internalCnt(0, 1LL, primes, pitable);
    i64 root = sqrt(nmax);
    for(unsigned i = 0; i < primes.size() && primes[i]<=root; ++i){
        n0 -=  recCount(i, primes[i], primes, pitable);
    }
    return n0;
}
*/
//I will use a recursive function to compute all numbers
//nn is maximum allowed
void pmult(i64 prod, int index, vector<int>& primes, vector<i64>& vp, int nn)
{
    //BUG find the last bug here! even if I only need to calculate to 1e5
    //but still 1e5*1e5 overflows!
    if(abs(prod) > nn) return;
    if(prod == 1){
        vp.clear();
        vp.reserve(100000);
        vp.push_back(1);
    }
    for(int k = index; k<(int)primes.size(); ++k){
        i64 pt =  -primes[k] * prod;
        if(abs(pt) > nn) break;
        vp.push_back(pt);
        pmult(pt, k+1, primes, vp, nn);
    }
}
i64 cntSmall(i64 prod, int index, vector<int>& primes, int nn, double& dsum)
{
    if(prod > nmax) return 0;
    i64 sum = 0;
    double dt;
    dsum = 0;
    for(int k = index; k <(int) primes.size(); ++k){
        i64 pt = prod * primes[k];
        if(pt > nmax) break;
        sum += ncube(nmax/pt, dt);
        dsum += dt;
        sum -= cntSmall(pt, k+1, primes, nn, dt);
        dsum -= dt;
        sum %= nmod;
    }
    return sum;
}
int main(int argc, char* argv[])
{
    i64 nn;
    if(argc==2){
        nmax = atol(argv[1]);
    }
    //I do not need too large an prime list
    //let us restrict it to sqrt(nmax);
    nn = sqrt(nmax);
    //if(false)
    //{
    //    nmax = 10000000000L;
    //    i64 nc = myprimecount(nmax/1);
    //    for(int i = 2; i<= 10000; ++i)
    //        i64 np = myprimecount(nmax/i);
    //        printf("number of primes for i=%d is %ld left %ld\n", i, nc - np, nc);
    //        nc = np;
    //    }
    //    return 0;
    //}
    //prime list
    vector<int> primes;
    sievePrimes(nn, primes);
    printf("number of primes is %zu\n", primes.size());//9592

    //prepare a list for calculating large numbers'
    //contribution
    //nn = 10000;
    //pitable.resize(100000000+1);
    //int index = 0;
    //int cnt = 0;
    //int psize = primes.size();
    //for(int i = 0; i < (int)pitable.size(); ++i){
    //    if(index < psize && i == primes[index]){
    //        ++cnt;
    //        pitable[i] = cnt;
    //        ++index;
    //    }else{
    //        pitable[i] = cnt;
    //    }
    //}

    //primes.resize(9592);
    vector<i64> vp;
    pmult(1LL, 0, primes, vp, nn);
    //BUG, not fully thought about my plan, I want to use the negative 
    //sign for inclusion and exclusion, but forgot to sort in abs order
    sort(vp.begin(), vp.end(), absLess());
    assert(abs(vp.back()) <= nn);
    
    //large primes contribution
    //so this will include all primes from nmax/10000 to nmax
    //since there is still a large prime not counted, need to 
    //get a negative sign outside.
    i64 nc = myprimecount(nmax);
    i64 slarge = 0;
    double  dt, dlarge = 0;
    printf("large start\n");
    for(i64 i = 1; i*(i+1)<=nmax; ++i){//this is not easy to figure out
        if(i% 1000 == 0)
            printf("large %lld\n", i);
        i64 num = nmax/(i+1);
        i64 np = myprimecount(num);
        i64 cnt = (nc - np);
        if(np == nc) continue;
        for(int k = 0; k < (int)vp.size(); ++k){
            int v = vp[k];
            v=abs(v);
            if(v > i)break;
            i64 n3 = ncube(i/v, dt);
            n3 = multmod(n3, cnt, nmod);
            dt *= cnt;
            if(vp[k] > 0){
                slarge += n3;
                dlarge += dt;
            }else{
                slarge -= n3;
                dlarge -= dt;
            }
            slarge %= nmod;
        }
        //BUG, why I missed to assign this value back to nc
        nc = np;
    }
    printf("large end\n");
    dt = 0;
    i64 sum = ncube(nmax, dt) - slarge;
    double dsum = dt - dlarge;
    sum -= cntSmall(1L, 0, primes, nn, dt);
    dsum -= dt;
    sum %= nmod;
    if(sum < 0) sum += nmod;
    printf("%lld %lld %15.10f\n",nmax, sum, dsum);
}
