#include <cstdio>
#include <cassert>
#include <cmath>
#include "../lib/typedef.h"
//accuracy is the key point here
int main()
{
    i64 r =  250000000;
    //r=125000000;
    i64 r2 = 2*r; 
    i64 dim = 4*r;
    i64 na = (dim)*r2*3;
    i64 rsq = r * r;
    double coeff=sqrt((long double)0.5d);
    i64 ymax = coeff*r;
    i64 cnt = 0;
    for(i64 yt = 0; yt<=ymax; ++yt){
        double xmax = sqrt(static_cast<double>(rsq/2.0-yt*yt));
        i64 ixmax = round(xmax);
        assert(xmax >0);
        if(2*(ixmax*ixmax+yt*yt)==rsq) 
            --ixmax;
        else if(2*(ixmax*ixmax+yt*yt)-rsq<0 && 2*((ixmax+1)*(ixmax+1)+yt*yt)-rsq<0){
            while(2*((ixmax+1)*(ixmax+1)+yt*yt)-rsq<0)
                ++ixmax;
        }
        else if(2*((ixmax)*(ixmax)+yt*yt)-rsq>=0){
            --ixmax;
        }
        assert(2*(ixmax*ixmax+yt*yt)-rsq<0);
        assert(2*((ixmax+1)*(ixmax+1)+yt*yt)-rsq>=0);
        i64 cff = yt==0?1:2;
        cnt +=cff*(ixmax *2+1);
    }
    printf("%lld\n", cnt+na-r+1);
}
