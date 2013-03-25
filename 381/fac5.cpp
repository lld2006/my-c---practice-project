#include <cstdio>
#include <cassert>
#include "../lib/tools.h"
//this is a relative easy problem. wilson theorem is the key;
int main()
{
    int limit = 100000000;
    vector<int> primes;
    primeWithin(primes, limit);
    printf("number p %d\n", primes.size());
    i64 sum = 4;
    for(unsigned int i = 3; i<primes.size(); ++i){//start from 7 is easier
        int p = primes[i];
        i64 tsum = 0;//p-1 + 1 p-1 from p-1 and 1 from p-2 mod p = 0
        i64 prod = 1;
        i64 x =0, y = 0, gcd = 0;
        //here no need to add since it is considered in initialization
        extended_euclid(p-2, p,x, y,  gcd );
        if(x < 0 ) x+= p;
        assert( gcd == 1);
        prod *= x;
        if(prod > p ) 
            prod %= p;
        tsum += prod;
        extended_euclid(p-3, p,x, y,  gcd );
        if(x < 0 ) x+= p;
        assert( gcd == 1);
        prod *= x;
        if(prod > p ) 
            prod %= p;
        tsum += prod;
        extended_euclid(p-4, p,x, y,  gcd );
        if(x < 0 ) x+= p;
        assert( gcd == 1);
        prod *= x;
        if(prod > p ) 
            prod %= p;
        tsum += prod;
        sum += (tsum%p);
    }
    printf("%lld\n", sum);
}
