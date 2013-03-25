#include "../lib/typedef.h"
#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/tools.h"
int main(){
    i64 limit = 100000000;
    int sq = 10000;
    int sum = 0;
    for(i64 a = 1; a <=sq; ++a)
        for(i64 b= a +1; b<= sq; ++b){
            i64 sidea = b*b-a*a;
            i64 sideb = 2*a*b;
            i64 max = sidea > sideb? sidea:sideb;
            i64 min = sidea > sideb? sideb:sidea;
            if(gcd(max, min) > 1) continue;
            i64 sidec = a*a+b*b;
            i64 peri = sidea +sideb+sidec;
            if( sidec% (max-min) !=0) continue;
            if( peri >= limit ) break;
            //printf("%lld %lld %lld\n", sidea, sideb, sidec);
            i64 ncfg = (limit-1) / peri;
            sum += ncfg;
            //for(i64 i = peri; i <= peri * ncfg; i+=peri){
            //    assert(i < limit);
            //}
        }
    printf("%d\n", sum);
}
