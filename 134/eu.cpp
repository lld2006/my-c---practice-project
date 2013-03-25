#include "../lib/tools.h"
#include <cstdio>
#include <cmath>
#include <cassert>
typedef long long int i64;
//lesson, read problem carefully, the problem asks p1 less than limit, p2 might be greater
//than limit!
int main(){
    vector<int> primes;
    int limit = 1000000;
    unsigned long long int sum = 0;
    primeWithin(primes, limit+200);
    for(unsigned int i = 3; i < primes.size(); ++i){
        int a = primes[i-1]; 
        int b = primes[i];
        assert(a < b);
        if(a > limit) break;
        int digits = log((double)a)/log(10.)+1;
        int tens = power(10, digits);
        int x=0, y=0, gcd =0;
        extended_euclid(b, tens, x, y, gcd);
        i64 xa = x;
        i64 ya = y;
        xa *= a;
        ya *= -a;
        assert(fabs(x )< 1e10);
        assert(fabs(y )< 1e10);
        if(ya < 0){
            i64 inc = -ya/b+1;
            ya += (i64)inc*b;
            xa += (i64)tens * inc;
        }else if(ya > b){
            i64 inc = ya/b;
            ya -= (i64)inc*b;
            xa -= (i64)tens *inc;
        }
        i64 value = (i64)tens *ya +a;
        assert(value % b == 0);
        sum += (i64) tens * ya +a;
    }
    printf("%I64d\n", sum);
}
