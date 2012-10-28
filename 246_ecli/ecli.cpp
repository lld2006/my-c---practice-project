#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/typedef.h"
int main()
{
    i64 a = 7500;
    i64 c = 5000;
    i64 a2 = a * a;
    i64 c2 = c * c;
    i64 b2 = a2 - c2;
    i64 b4 = b2 * b2;
    i64 ab2 = a2 * b2;
    i64 total = 0;
    int fac = 1;
    for(i64 yp = 0; yp < 10000000LL; ++yp){
        if( yp > 0) fac = 2;
        i64 yp2 = yp * yp;
        i64 eb =  a2 + 3 * b2 - yp2;
        i64 delta = 2 * b4  + yp2 * (a2 - b2);
        double dd = sqrt(delta);
        dd *= 2;
        if(eb + dd >= 0) {//one or 2 solutions for xp 45 or 135
            i64 xp1 = sqrt(eb + dd);
            if( yp2 <= b2){
                double t = a2*(1.0 - (double) yp2/b2);
                i64 xlim = sqrt(t); // the number xlim is the one 
                // on or inside the eclipse
                i64 x2 = (xlim + 1)*(xlim + 1);
                if(x2 * b2 + yp2 * a2 == ab2)
                    ++xlim;
                assert((xlim + 1)*(xlim+1)*b2+a2*yp2 > ab2);
                if(xp1 > xlim)
                    total += 2  * (xp1 - xlim)*fac;
            }else{
                total += (2 * xp1 + 1)*fac;
            }
        }else{//no solution at all
            break;
        }
    }
    printf("%lld\n", total);
}
