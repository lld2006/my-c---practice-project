#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cmath>
#include <cstdio>
//the answwer is zero! haha
int main(){
    i64 cnt = 0;
    i64 limit = 100000000;
    int l2 = 7072;
    for(i64 ia = 1; ia <= l2; ++ia)
        for(i64 ib = ia+1; ib <= l2; ++ib){
            if(gcd(ia, ib) != 1) continue;
            i64 iz0 = ia*ia+ib*ib;
            i64 d = round(sqrt(sqrt(iz0)));
            if(d*d*d*d == iz0 && ((ia*ib)%84!=0) )
                printf("%lld %lld %lld\n", ia, ib, iz0);
        }
    printf("%lld\n", cnt);
}
