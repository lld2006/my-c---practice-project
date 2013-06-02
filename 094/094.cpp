#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/typedef.h"
// assume the two right-angled triangles sides are 
// m^2-n^2, 2mn, m^2+n^2
// there are two possibilities, side eq 2a+1 2a+1 2a where m^+n^=4mn+1
// 2a-1 2a-1 2a where m^=3^n^2+1 
// pythagorean triangle is assumed, and the other possibility is ruled out when 
// some simple math is derived

int main(){
    i64 gsum = 0;
    for(int ib = 1; ib<=9129; ++ib){//n value
        double xb = sqrt((double)3 * ib*ib+1);//m value
        int ixb = round(xb);
        if(fabs(xb-ixb) < 1e-6){ //area is integer
            int peri = 4*ixb*ixb;
            assert(peri > 0);
            if(peri > 1000000000)continue;
            printf("peri = %d, %d\n", peri, ib);
            gsum += peri;
            //in the following case ixb = m -2*n 
            // n = ib
            //perimeter = 2*(m+n)^2
            int tval = 3*ib+ixb;
            peri =2*tval*tval;
            assert(peri > 0);
            if(peri > 1000000000)continue;
            printf("peri = %d %d\n", peri, ib);
            gsum += peri;
        }
    }
    printf("%lld\n", gsum);
}
