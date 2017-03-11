#include <cstdio>
#include <cstdlib>
#include "../lib/tools.h"
int main(int argc, char* argv[]){
    i64 prod = 1;
    for(i64 p =2; p<=20; ++p){
        prod *= p;
    }
    i64 f20=prod;
    i64 p5=0;
    while(prod){
        prod/=2LL;
        p5 += prod;
    }
    printf("factor of 2 =%lld 20!=%lld\n", p5, f20);
    prod = f20;
    int n12 = 24;//should be 48
    i64 nmax = 1LL<<n12;
    i64 nmod = nmax;
    prod = 1LL;
    i64 thresh = 2LL;
    i64 power = 1;
    for(i64 n = 1; n<nmax; n+=2){
       prod *= n; 
       prod %= nmod;
       if(n+1 == thresh){
           printf("power=%lld prod = %lld %lld\n", power, prod, prod-nmod);
           thresh *= 2;
           ++power;
       }
    }
    printf("need to compute %lld %lld\n", prod, (1LL<<48));
#if 0
    int pow2 = 10;
    if(argc==2)
        pow2=atol(argv[1]);
    i64 n2 = 1<<pow2; 
    for(i64 nx = 2; nx<=15;++nx){
        i64 pd = 1LL;
        i64 nmod = 1LL<<nx;
        for(i64 m = 1; m<=31; m+=2 ){
            pd *= m;
            pd %= nmod;
        }
        printf("%lld %lld\n", nmod, pd);
    }
#endif
}
