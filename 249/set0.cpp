//4999 is 669th prime number
#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cstdio>
// this problem is easy when problem 250 is solved, dynamic programming
int main(){
    int limit = 5000;
    int limit2 = 1548136;
    i64 mbase = 10000000000000000LL;
    vector<int> prime1, prime2;
    primeWithin(prime1, limit);
    primeWithin(prime2, limit2);
    vector<i64> dpvec;
    dpvec.resize(limit2+1);
    dpvec[0] = 1;
    unsigned int max_val = 0;
    for(unsigned int i = 0; i < prime1.size(); ++i){
        unsigned int max0 = max_val;
        max_val += prime1[i];
        vector<i64> tvec;
        tvec.resize(max_val+1,0); //0--max_val
        for(unsigned int j = 0; j <=max0; ++j){
            tvec[j+prime1[i]] = dpvec[j];
        }
        for(unsigned int j = 0; j <= max_val; ++j){
            dpvec[j] += tvec[j];
            if(dpvec[j] >= mbase )dpvec[j] -= mbase; //be careful
        }
    }
    i64 sum = 1; // 2 is a subset which is a prime, the rest sum should always
    // be odd
    vector<int> flags;
    flags.resize(limit2+1, 0);
    for(unsigned int i = 0; i < prime2.size(); ++i)
        flags[prime2[i]] = 1;
    for(unsigned int i = 3; i< dpvec.size(); i+=2)
        if(flags[i] == 1){
            sum += dpvec[i];
            sum %= mbase;
        }
    printf("%lld\n", sum);
}
