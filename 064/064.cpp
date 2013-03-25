#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;

i64 check_period(i64 num, i64 root)
{
    //initialization nt
    i64 nt = root;//nt is the number in the numerator
    //negative sign is not included
    i64 stop = root * 2;
    i64 q = root; // the integer part for each step
    i64 period = 0;
    i64 den = 1; //initialization of denominator 
    while(q != stop){
        assert((num - nt * nt) % den == 0);
        den = (num - nt * nt)/den;
        q = (root + nt)/ den;
        nt =  q * den - nt;
        ++period;
    }
    return period;
}
int main()
{
    i64 count = 0;
    i64 max = 0;
    for( i64 i = 1; i < 1000; ++i)
        for(i64 j = i*i+1; j < (i+1)*(i+1); ++j){
            i64 period = check_period(j, i);
            if(max < period) 
                max = period;
            //printf("%lld %lld\n", j, period);
            if(period %2 ==1) 
                ++count;
        }
    printf("%lld %lld\n", count, max);
}
