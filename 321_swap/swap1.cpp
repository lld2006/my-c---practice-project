#include "../lib/typedef.h"
#include <cmath>
#include <cstdio>
bool isTriangleNumber(i64 nswap)
{
    i64 fswap = nswap*(nswap+2);
    i64 mvalue = (sqrt((double)1+8*fswap)-1)/2;
    i64 trinumber = mvalue*(mvalue+1)/2;
    bool is_less = true;
    if(trinumber == fswap)
        return true;
    else if(trinumber > fswap)
        is_less = false;
    while(true){
       if(is_less)
            ++mvalue; 
       else
            --mvalue;

        trinumber = mvalue*(mvalue+1)/2;
        if(trinumber == fswap)
            return true;
        if((trinumber < fswap) != is_less)
            return false;
    }
}
int main()
{
    i64 nswap = 1;
    int cnt = 0;
    i64 sum = 0;
    i64 oswap = 0;
    while(cnt < 40){
        if(isTriangleNumber(nswap)){
            ++cnt;
            sum += nswap;
            printf("%d %lld", cnt, nswap);
            if(oswap != 0)
                printf("ratio %30.20f\n", (double)(nswap-1)/oswap);
            else
                printf("\n");

            oswap = nswap;
            if(cnt %2){
                if(cnt < 10)
                    nswap *=2;
                else
                    nswap *= 2.093836;
            }
            else 
                nswap *= 2.78361d;
        }
        ++nswap;
    }
    printf("%lld\n", sum);
}
