#include <cstdio>
#include <cmath>
#include "../lib/typedef.h"
int main()
{
    for(i64 i = 144; i ;++i){
        //if(i % 100000 == 0) 
        //    printf("%d\n", i);
        i64 t = i*(2*i-1);
        i64 u = round((1.0+sqrt(1+24.0*t))/6);
        if(u*(3*u-1)/2 != t) continue;
        i64 v = round((sqrt(1+8.*t)-1)/2);
        if(v*(v+1)/2 != t) continue;
        printf("%d %lld\n",i, t);
        break;
    }
}
