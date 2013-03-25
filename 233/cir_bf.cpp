#include <cstdio>
#include <cassert>
#include <cmath>
#include "../lib/typedef.h"
#include "../lib/tools.h"
int main()
{
    for(i64 n = 359125*2; n < 359125*2+2; n+=2){
        i64 limit = sqrt(2.0)*n;
        i64 cnt = 0;
        for(i64 x = 1; x <= limit; ++x){
            i64 y = sqrt(2*n*n-x*x);
            assert(x*x+y*y<=2*n*n);
            while(x*x+y*y<2*n*n){
                ++y;
            }
            if(x*x+y*y==2*n*n){
                ++cnt;
                printf("%lld %lld %lld %lld\n",cnt, n, x, y);
            }
        }
    }
}
