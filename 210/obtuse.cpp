#include <cstdio>
#include <cassert>
#include <cmath>
#include "../lib/typedef.h"
//accuracy is the key point here
int main()
{
    i64 r =  250000000;
    i64 na = 1e18*3/2;
    i64 rsq = r * r/2;
    i64 ymax = sqrt((double)rsq);
    i64 cnt = 0;
    for(i64 yt = 1; yt<=ymax; ++yt){
        i64 yt2 = yt * yt;
        i64 ixmax = sqrt(static_cast<long double>(rsq-yt2));
        if((ixmax*ixmax+yt2)==rsq) 
            --ixmax;
        //assert((ixmax*ixmax+yt2)-rsq<0 && ((ixmax+1)*(ixmax+1)+yt2)-rsq>=0);
        cnt +=(ixmax);
    }
    cnt *= 2;
    cnt += ymax;
    cnt *= 2;
    cnt += (ymax*2+1);
    printf("%lld\n", cnt+na-r+1);
}
