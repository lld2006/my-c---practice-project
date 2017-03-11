#include "../lib/tools.h"
int main()
{
    i64 sum = 0;
    i64 p = 101;
    i64 r = 10;
    i64 x, y, g;
    for(i64 k=1; k<p; ++k){
        extended_euclid(k,p, x, y, g);
        i64 c = combination(p-2+r-k, r-1, p);
        printf("k=%lld inv=%lld, c=%lld\n", k, x, c);
        sum += product_mod(c, x, p);
    }
    printf("%lld\n", sum%p);
}
/* 
int main()
{
    i64 a = 1000000000LL;
    a = 1000;
    i64 b = 100000;
    b = 100;
    i64 k = 100;
    i64 sum = 0;
    for(i64 p = a+1; p < a+b; p+=2){
        if(p%3 ==0 || p%5==0||p%7==0)continue;
        if(!strong_pseudo_test(p))continue;
        i64 xx, y, g;
        extended_euclid(k, p, xx, y, g );
        if(xx < 0) xx += p;
        assert(0< xx && xx< p);
        if(k & 1) xx = -xx;
        if(xx < 0) xx += p;
        printf("%lld %lld\n", p , xx);
        sum += xx;
    }
    printf("%lld\n", sum);
}
*/
