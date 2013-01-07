#include <cmath>
#include <cstdio>
#include "../lib/typedef.h"
int main()
{
    i64 limit = 1000000;
    i64 pmax = limit/(sqrt(2.0));
    i64 sum = 0;
    int inc = 0;
    for(i64 p = 1; p <= pmax; ++p){
        if(p %2 == 1) 
            inc = 2;
        else
            inc = 1;
        for(i64 q=p+1; q<= limit; q+=inc){
            i64 result = p*p+q*q+(p*q)*(p*q)*4;
            i64 root = round(sqrt(result));
            if(root > 1e6) break;
            if(result == root*root){
                //printf("%lld %lld %lld\n", 2*p, 2*q, root-2*p*q);
                sum += root;
            }
        }
    }
    printf("%lld\n", sum);
}
