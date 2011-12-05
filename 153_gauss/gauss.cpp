#include "../lib/tools.h"
#include <cstdio>

int limit  = 100000;
int sql = 317;

i64 gaussNum(int nth, int product){ // rational part
    i64 sum = 0;
    for(int i = nth; i < primes.size(); ++i){
        int value  = product *primes[i];
        if(value > limit) break;
        int nx = limit / value;
        sum += nx*(nx + 1)*(nx+2)/6 * product;
        sum -= gaussNum(i+1, value);
    }
    return sum;
}

int main(){
    i64 sum = 0;
    vector<int> primes;
    primeWithin(primes, limit);
    sum = limit; //all 1 contribution
    //inclusion exclusion principle 
    sum += gaussNum(0, 1);
    /*
    for(unsigned int i = 0; i<primes.size(); ++i){
        if(primes[i] > limit) 
            break;
        i64 nx = limit/ primes[i];
        sum += nx*(nx+1LL)*(nx+2LL)/6LL*primes[i];
    }
    */
    for(int ia = 1; ia <= sql; ++ia){
        const int a2 = ia * ia;
        for(int ib = 1; ib <= sql; ++ib){
            int tsum = a2 + ib*ib;
            if(tsum > limit)
                break;
            if(gcd(ia, ib) > 1)
                continue;
            sum += gaussNum();
        }
    }
    printf("%lld\n", sum);
}
