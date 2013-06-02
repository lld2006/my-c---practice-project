#include "../lib/typedef.h"
#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/tools.h"
int main(){
    i64 limit = 100000000;
    int sq = 5000;
    int sum = 0;
    
    for(i64 a = 1; a <sq; ++a){
        int inc = 1;
        if(a%2 ==0) inc = 2;
        for(i64 b= a +1; b; b+=inc){
            i64 sidea = b*b-a*a;
            i64 sideb = 2*a*b;
            i64 diff = sidea - sideb;
            if(diff < 0) diff = -diff;
            i64 sidec = a*a+b*b;
            i64 peri = sidea +sideb+sidec;
            if( peri >= limit ) break;
            if( sidec%diff != 0) continue;
            if(gcd(sidea, sideb) > 1) continue;
            i64 ncfg = (limit-1) / peri;
            sum += ncfg;
        }
    }
    printf("%d\n", sum);
}
