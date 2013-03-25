#include <cstdio>
#include "../lib/tools.h"

i64 algser(i64 low, i64 high, i64 diff){
    i64 lp, hp;
    if(low %diff == 0) 
        lp = low/diff;
    else
        lp = low/diff+1;
    hp = high/diff;
    if( hp < lp ) 
        return 0;
    else
        return (hp-lp+1)*(hp+lp)*diff/2;
}

int main(){
    i64 sum = 0;
    int limit = 1000000;
    i64 thresh = 999966663333LL;
    //i64 thresh = 1000;
    vector<int> primes;
    primeWithin(primes, limit);
    for(unsigned int i = 0; i < primes.size() - 1; ++i){
        i64 low = (i64)primes[i]*primes[i]+1;
        i64 high = (i64)primes[i+1]*primes[i+1]-1;
        if(low > thresh) break;
        if(high > thresh) high = thresh;
        sum += algser(low, high, primes[i]);
        sum += algser(low, high, primes[i+1]);
        sum -= algser(low, high, (i64)primes[i+1]*primes[i])*2;
    }
    printf("%lld\n", sum);
}
