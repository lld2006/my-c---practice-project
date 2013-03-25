#include "../lib/int.h"
#include <cstdio>
#include <cmath>

int main(){
    GeneralInteger gsum (0);
    for(int ib = 1; ib<=3500; ++ib){
        double xb = sqrt((double)3 * ib*ib+1);
        int ixb = round(xb);
        if(fabs(xb-ixb) < 1e-6){
            int ia = ixb;
            int in2 = ((ia*ia+ib*ib)-1);
            int peri = 3*in2+4;
            if(peri > 1000000000)continue;
            printf("peri = %d, %d\n", peri, ib);
            gsum += peri;
            ia = 2* ib+ ixb;
            in2 = 4*ia*ib;
            peri =3 * in2+2;
            if(peri > 1000000000)continue;
            printf("peri = %d %d\n", peri, ib);
            gsum += peri;
        }
    }
    gsum.print();
    printf("\n");
}
