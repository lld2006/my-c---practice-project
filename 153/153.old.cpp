#include "../lib/tools.h"
#include <cassert>
#include <cstdio>
#include <cmath>
int limit  = 100;
unsigned int sql = sqrt(limit);

int main(){
    i64 sum = 0;
    vector<int> primes;
    primeWithin(primes, sql);

    vector<i64> factors, factorsum;
    factors.resize(limit+1,0);
    factorsum.resize(limit+1, 1);
    factorsum[0] = 0;
    for(unsigned int i = 1; i<factors.size(); ++i)
        factors[i] = i;

    for(unsigned int pi=0; pi <primes.size();++pi){
        i64 px = primes[pi];
        for(unsigned int index = px; index < factors.size(); index += px){
            int pn = 0; 
            int va = factors[index];
            assert(va % px == 0);
            do{
                va /= px;
                ++pn;
            }while(va % px == 0);
            factorsum[index] *= (power(px, (i64)pn+1)-1)/(px - 1);
            factors[index] = va;
        }
    }

    vector<i64> facacc;
    facacc.resize(limit+1, 0);
    for(unsigned int i = 1; i< factors.size(); ++i){
        if(factors[i] != 1)
            factorsum[i] *= (factors[i]+1);
        facacc[i] = facacc[i-1] + factorsum[i];
    }
    sum += facacc[limit];// all real factors;
    
    sum += facacc[limit/2] *2;

    for(unsigned int ia = 1; ia <= sql; ++ia){
        int incb = 1;
        if(ia%2 == 0)
            incb = 2;
        for(unsigned int ib = ia+1; ib <=sql; ib+=incb){
            if(gcd(ia, ib)> 1) 
                continue;
            int square = ia * ia + ib*ib;
            if(square > limit) continue;
            int nl = limit/square;
            if(ia != ib)
                sum += facacc[nl]*(ia+ib)*2;
            else
                sum += facacc[nl]*(ia+ib);
        }
    }
    printf("%lld\n", sum);
}
