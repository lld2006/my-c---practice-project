#include <cstdio>
#include <cassert>
#include <cmath>
#include "../lib/typedef.h"
//accuracy is the key point here
int main()
{
    i64 r =  250000000;
    i64 na = r*r*24;
    r/=2;
    i64 r2 = r*r*2;
    i64 ymax = sqrt(r*r*2);
    i64 cnt = 0;
    i64 y = r;
    i64 y2 = y*y, x2 = (r-1)*(r-1);
    for(i64 x = r-1; x > 0; --x){
        while(x2 + y2 < r2){
            y2 += 2*y +1;
            ++y;
        }
        cnt +=(y-x-1);
        x2 += 1-2*x;
    }
    cnt *= 8;
    cnt += 4*ymax+2*r-2;
    printf("%lld\n", cnt+na);
}
