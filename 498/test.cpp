#include "../lib/tools.h"
int main()
{
    i64 n = 100; 
    i64 m = 10;
    i64 p = 4;
    i64 px = 999999937LL;
    i64 sum = 0;
    i64 sign = 1;
    for(i64 k = p; k< m; ++k){
        sum += sign * combination(n, k) * combination(k, p);
        sign = - sign;
        printf("%lld %lld\n", k, sum%px+px);
    }
    return 0;
}
