#include <cmath>
#include <cstdio>
#include "../lib/typedef.h"
int main()
{
    int cnt = 9;
    i64 prod = 10;
    for(unsigned int i = 1; i<30; ++i){
        int vmin = pow(10., i/(i+1.))+1;
        cnt += 10 - vmin;
        printf("pow=%d min=%d cnt=%d\n",i+1, vmin, 10-vmin);
        prod *= 10;
    }
    printf("%d\n", cnt);
}
