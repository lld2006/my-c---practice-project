#include <cstdio>
#include <cmath>
#include "../lib/typedef.h"

u64 isqrt(u64 num){
    u64 vsq = round(sqrt((double)num));
    if( vsq * vsq == num)
        return vsq;
    else
        return 0;
}

int main(){
    int count = 0;
    u64 sum = 0;
    int i;
    for( i = 1; i; ++i){
        if(i % 2 == 1 ){
            u64 value = 5LL * i *i -1;
            u64 vsq = isqrt( value );
            if(vsq){
                ++count;
                u64 a = 2*i+ vsq;
                u64 b = i;
                u64 c = a*a+b*b;
                printf("%lld %lld %lld\n", a, b, c);
                sum += c;
            }
        }

        u64 v1 = 5LL*i*i+1;
        u64 vsq1 = isqrt( v1 );
        if(vsq1){
            ++count;
            u64 a = 2 * i + vsq1;
            u64 b = i;
            u64 c = a * a +b * b;
            printf("%lld %lld %lld\n", a, b, c);
            sum += c;
        }
        if(count == 12) break;
    }
    printf("%d\n", i);
    printf("%lld\n", sum);
}
