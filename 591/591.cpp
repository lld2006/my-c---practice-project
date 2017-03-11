#include <cmath>
#include <cstdio>
#include "../lib/tools.h"
//no idea!!!!!!!!!!!!
int main()
{
    i64 nmax = 100000000000000LL;
    long double pir = atan(1.0)*4-3;
    long double r2 = sqrt(2.0);
    long double min = 1;
    //long double min2 = 1;
    //for(i64 a = nmax; a >= 0; --a){
    for(i64 a = 0; a <= nmax; ++a){
        long double vd= a*r2;
        i64 n = vd;
        long double res1 = vd-n-pir;
        long double res2 = n+1-vd-pir;
        if(res1 > 0 && res1 < min){
            min = res1;
            printf("t1 %lld %15.10Lg\n", a, res1);
        } 
        if( res2 > 0 && res2< min){
            min = res2;
            printf("t2 %lld %15.10Lg\n", a, res2);

        } 
    }
}
