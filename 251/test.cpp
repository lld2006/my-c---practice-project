#include "../lib/tools.h"
#include <cassert>
#include <cmath>
int main()
{
    struct timer mytime;
    int limit = 100000000;
    for( int i = 1; i <= limit; ++i ){
        int value = sqrt(i);
        assert(value * value <= i && (value+1)* (value+1) > i);
    }
    printf("%.6f\n", mytime.getTime());
    for( int i = 1; i <= limit; ++i ){
        int value = sqrt((double)i);
        assert(value * value <= i && (value+1)* (value+1) > i);
    }
    
}
