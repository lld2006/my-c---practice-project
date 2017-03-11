#include "../lib/tools.h"
i64 t = 1000000000000LL;
i64 pk0 = 10000;
i64 sumpow(i64 nmax, i64 pk, i64 prime );
i64 test()
{
    vector<i64> vn;
    vn.resize(t+1, 0);
    for(unsigned int i = 1; i < vn.size(); ++i){
        i64 val = power((i64)i, pk0);
        vn[i] = val;
    }
    for(unsigned int i = 1; i < vn.size(); ++i){
        vn[i] += vn[i-1];
    }
    i64 sum = 0;
    for(unsigned int i = 0; i < vn.size(); ++i)
        sum += vn[i];
    return sum;
}
int main()
{
    //bool test = true;
    //printf("%lld\n", test());
    int nmax = 2000000000;
    int pmax = sqrt(nmax+2000);
    i64 pk = pk0;
    vector<int> primes;
    primeWithin(primes, pmax);
    vector<int> vflags;
    vflags.resize(2000, 1);
    for(unsigned int i = 0; i< primes.size(); ++i){
        int px = primes[i];
        int res = nmax%px;
        int start = (res == 0)? 0 : px - res;
        for(unsigned int j = start ; j < vflags.size(); j+= px){
            vflags[j] = 0;
        }
    }
    vector<int> v2;
    for(unsigned int i = 0; i < vflags.size(); ++i){
        if(vflags[i]){
            v2.push_back(nmax + i);
            //printf("%d\n", v2.back());
        }
    }
    i64 sum = 0;
    //TODO
    //for(unsigned int i = 0; i < 1; ++i ){
    for(unsigned int i = 0; i < v2.size(); ++i ){
        sum += sumpow(t, pk, v2[i]);
        //printf("i=%d %lld\n", i, sum);
    }
    printf("%lld\n", sum);
}
//pk is the max power, 
//nmax is maximum n in the summation
i64 sumpow(i64 nmax, i64 pk, i64 prime ){
    vector<i64> vpsum; 
    vpsum.push_back(0);
    vpsum.push_back(1);
    for(unsigned int i = 2; i <= pk+2; ++i){
        i64 val = powermodule((i64)i, pk, prime);
        vpsum.push_back(addmod(val, vpsum.back(), prime));
    }
    for(unsigned int i = 1; i < vpsum.size(); ++i){
        vpsum[i] = addmod(vpsum[i], vpsum[i-1], prime);
    }
    //get a factorial table to reduce effort
    vector<i64> vprod;
    vprod.resize(pk+3, 1);
    i64 prod = 1;
    for(i64 i =2; i<=pk+2; ++i){
        prod = multmod(prod, i, prime);
        vprod[i] =prod;
    }
    prod = 1;
    i64 tp = nmax % prime;
    for(i64 m = 0; m<= pk+2; ++m){
        prod = multmod(prod, tp-m, prime);
    }
    //now prod is the numerator part
    i64 sum = 0;
    for(unsigned int i = 1; i<= pk+2; ++i){
        i64 pn = multmod(prod, vpsum[i], prime);
        i64 pd = multmod(vprod[i], vprod[pk+2-i], prime);
        pd = multmod(pd, (t-i), prime);
        i64 x, y, gcd;
        extended_euclid(pd, prime, x, y, gcd); 
        assert(pd * x + prime * y == 1LL);
        i64 result = multmod(x, pn, prime);
        //printf("x %lld pn %lld prime %lld result %lld\n", x, pn, prime, result);
        if(i & 1)
            sum -= result;
        else
            sum += result;
        //printf("k=%d %lld final %lld\n",i, result, sum);
    }
    i64 val = sum%prime;
    if(val < 0) val += prime;
    return val;
}
