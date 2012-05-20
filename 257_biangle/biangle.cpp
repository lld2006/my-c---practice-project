#include <cstdio>
#include <cassert>
#include "../lib/tools.h"
int main()
{
    int limit = 10000;
    int amax = limit/3;
    i64 sum = 0;
    for(i64 gab = 1; gab<=amax; ++gab){
            printf("%lld\n", gab);
        i64 acmax = amax/gab; // since a = ra* gab*gac
        for(i64 gac = 1; gac <= acmax; ++gac){
            if(gcd(gac, gab) != 1) continue;
            i64 ramax = amax/(gac*gab);
            for(i64 ra = 1; ra < ramax; ++ra){
                i64 a = ra*(gac*gab);
                i64 rbmin = 1;
                if(gac > 1 || ra > 1) 
                    rbmin = gac * ra + 1;
                i64 bmax = (limit-a)/2;
                i64 rbmax = bmax/gab;
                for(i64 rb = rbmin; rb <= rbmax; ++rb){
                   if(gcd(rb, ra*gac) != 1) 
                       continue; //a b can not be reduced further
                   i64 b = rb* gab;
                   i64 rcmin = gac==1? b: b/gac + 1;
                   i64 rcmax = (a+b)/gac;
                   for(i64 rc = rcmin; rc <=  rcmax; ++rc){
                        if(gcd(gab*ra, rc)!=1)
                            continue;
                        i64 c = rc * gac;
                        if(a +b <= c) continue;
                        assert(a <= b);
                        assert(b <= c);
                        i64 prod1 = gac*ra+rb;
                        if((prod1/rc) * rc != prod1) 
                                continue;
                        i64 prod2 = gab*ra+rc;
                        if( (prod2/rb)*rb != prod2)
                            continue;
                        i64 peri = a + b +c;
                        assert(peri <= limit);
                        sum += limit/peri;
                   }
                }
            }
        }
    }
    printf("%lld\n", sum);
}
