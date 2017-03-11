//4999 is 669th prime number
#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cstdio>
int main(){
    int limit = 5000;
    int limit2 = 1548136;
    i64 mbase = 10000000000000000LL;
    vector<int> prime1, prime2;
    primeWithin(prime1, limit);
    primeWithin(prime2, limit2);
    vector<i64> dpvec;
    dpvec.resize(limit2+1, 0);
    dpvec[0] = 1;
    int max_val = 0;
    for(unsigned int i = 0; i < prime1.size(); ++i){
        int px = prime1[i];
        max_val += px;
        for( int j = max_val; j >= px; --j){
            dpvec[j] += dpvec[j-px];
            if(dpvec[j] >= mbase )dpvec[j] -= mbase; //be careful
        }
    }
    i64 sum = 0; 
    i64 nmod = mbase * 500;
    for(unsigned int i = 0; i < prime2.size(); ++i){
            sum += dpvec[prime2[i]];
            if(sum > nmod)
                sum %= mbase;
    }
    printf("%lld\n", sum%mbase);
}
