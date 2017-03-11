#include <cstdio>
#include "../lib/typedef.h"
int limit = 100000;
i64 stern_tree(int b, int d)
{
    if(b+d > limit) return 0;
    return stern_tree( b, b+d) + stern_tree( b+d, d)+1;
}
int main()
{
    i64 result = stern_tree( 3, 2);
    printf("%lld\n", result);
}
