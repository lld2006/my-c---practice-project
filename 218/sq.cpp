#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cmath>
#include <cstdio>

int main(){
    i64 cnt = 0;
    i64 limit = 100000000;
    i64 ll = limit*limit;
    int l2 = 7072;
    for(i64 ia = 1; ia <= l2; ++ia)
        for(i64 ib = ia+1; ib <= l2; ++ib){
            i64 ic = ia*ia +ib*ib;
            if(gcd(ia, ib) != 1) continue;
            i64 iz0 = ia*ia+ib*ib;
            i64 d = round(sqrt(sqrt(iz0)));
            if(d*d*d*d == iz0 && ((ia*ib)%84!=0) )
                printf("%lld %lld %lld\n", ia, ib, iz0);
            //i64 ix0 = ib*ib - ia *ia;
            //i64 iy0 = 2*ia*ib;
            //i64 ix = ix0> iy0?ix0:iy0;//ix > iy
            //i64 iy = ix0+iy0-ix;
            //i64 ix1= ix*ix -iy*iy;
            //i64 iy1= 2*ix*iy;
            //i64 iz1 = ix*ix+iy*iy;
            //if(iz1 > ll) continue;
            //if((ix1%7&&iy1%7)){
            //    ++cnt;
            //}else if(ix1%3 && iy1%3){
            //    ++cnt;
            //}else if(!(ix1 %4==0||iy1%4==0 ||(ix1%2==0 &&iy1%2==0))){
            //    ++cnt;
            //}
        }
    printf("%lld\n", cnt);
}