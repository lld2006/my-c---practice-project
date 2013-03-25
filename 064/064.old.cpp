#include "../lib/typedef.h"
#include <set>
#include <cassert>
#include "../lib/typedef.h"
#include <cstdio>
int main()
{
    i64 limit = 100000000;
    i64 count = 0;
    i64 num, den;
    set<pair<int, int> > pairset;
    for(i64 n = 1; n< 1000; ++n)// n^2---> (n+1)^2
        for(i64 j = n*n+1; j < (n+1)*(n+1); ++j){
            pairset.clear();
            bool flag = true;
            i64 period = 0;
            num = n; // (sqrt(j) - num)/ den
            den = 1;
            while(flag){
                flag = pairset.insert(IntPair(num, den)).second;
                if(flag) ++period;
                assert(( j- num *num)%den==0);
                den = (j - num * num)/den;
                i64 intg = (n+num)/den;
                assert(intg > 0);
                num = den * intg - num;
            }
            if(period%2 )++count;
        }
    printf("%lld\n",count);
}
