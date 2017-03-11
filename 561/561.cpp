//some finding
//[(n+1)*(n+2)/2]^m-(n+1)^m
//for example n = 1 m = 2; 3^2 -2^2 =5, i.e., result of 6
//53233*17=904961
//if n is even, n+1 is odd, so [(n+2)/2]^m-1 determines the power
//of two, n/2 determines it
//if n is odd then [(n+1)/2]^m determines the power of two
//
//till now, everything is straight forward.
#include <cstdio>
#include "../lib/typedef.h"
int main()
{
    i64 nmax = 1000000000000LL;
    i64 m = 904961; 
//  first let us consider even numbers
    i64 n1 = nmax/2; 
    i64 total =0;
    i64 p = 2;
    while(n1){
        n1 /= p;
        total += n1;
    }
    i64 t2 = 0;
    i64 n2 = (nmax+1)/2;
    while(n2){
        n2/=p;
        t2 += n2;
    }
    total += t2 * m;
    printf("%lld\n", total);
}
