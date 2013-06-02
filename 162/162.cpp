#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
int main()
{
    i64 result = 4;
    i64 f12 = 0;
    for(i64 i = 4; i<=16; ++i){
        f12+= (power(15LL, i-2)-2*power(14LL,i-2)+power(13LL,i-2));
        result = 16*result +2*(power(15LL, i-1)-2*power(14LL, i-1)+power(13LL, i-1))
            +15*f12;
        printf("%lld %llX\n", result, result);
    }
}
