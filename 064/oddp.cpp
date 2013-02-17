#include "../lib/typedef.h"
#include <set>
#include <cassert>
#include <cstdio>
int main()
{
    int count = 0;
    int num, den;
    set<pair<int, int> > pairset;
    for(int n = 1; n< 100; ++n)// n^2---> (n+1)^2
        for(int j = n*n+1; j < (n+1)*(n+1); ++j){
            pairset.clear();
            bool flag = true;
            int period = 0;
            num = n; // (sqrt(j) - num)/ den
            den = 1;
            while(flag){
                flag = pairset.insert(IntPair(num, den)).second;
                if(flag) ++period;
                assert(( j- num *num)%den==0);
                den = (j - num * num)/den;
                int intg = (n+num)/den;
                assert(intg > 0);
                num = den * intg - num;
            }
            if(period%2 )++count;
        }
    printf("%d\n",count);
}
