#include <cstdio>
#include "../lib/tools.h"
int main()
{
    i64 total = 0;
    i64 nmax = 100000;
    nmax = 100;
    i64 kmax = 2*nmax;
    i64 rhsmax = 4*nmax*nmax;
    //k t should be odd
    //I assume r2 >= r1
    for(i64 k=1; k<kmax; k+=2){// k is the slope for the second circle center
        i64 k2 = k*k+1;
        //i64 tmax = sqrt(rhsmax/k2);
        for(i64 t= k; ; t+=2){
            i64 r1sq= k2 * (t*t+1); // r1*r1;
            if(r1sq > rhsmax)
                break;
            i64 u=0, v=0;
            
            v = (k+t)/2;
            u = (k*t -1)/2;
            i64 x = (2*u+1);
            i64 y = 2*v-k;
            //x y is the first possible center 
            assert(x >= y );
            i64 deltax = k;
            i64 deltay = 1;
            double dist = sqrt(deltax*deltax + deltay*deltay);
            double shift = (2*u+1)/2.0/k;
            i64 nstart = (2*u+1)/k;
            i64 n1 = (nmax)/dist+shift;
            if(n1 > 0){
                total += (n1+1-(2*u+1)/k);
                if(true){
                    for(i64 n = nstart; n <= n1; ++n){
                        i64 tx = (n-nstart)* deltax+x;
                        i64 ty = (n-nstart) * deltay+y;
                        i64 r2 = (tx-u)*(tx-u) + (ty-v)*(ty-v);
                        printf("r1s %lld r2s %lld t=%lld k=%lld u=%lld v=%lld x=%lld y=%lld\n", 
                                r1sq/4, r2, t, k, u, v, tx, ty);
                    }
                }
            }
        }
    } 
    printf("%lld\n", total);
}
