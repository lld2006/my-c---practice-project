#include <cstdio>
#include <cmath>
#include "../lib/tools.h"
#include "../lib/typedef.h"

int main()
{
    i64 target = 1000000000000LL;
    //target = 100000;
    i64 sum = 0;
    for( i64 n = 1; n<1000; ++n){
        //the first as n^2
        i64 n1 = n*n;
        for(i64 m = n+1;m; ++m){
            if(gcd(m, n)!=1) continue;
            i64 n2 = n*m;
            i64 n3 = m*m;
            bool found = false;
            for(i64 k=1; k; ++k){
                i64 result = k*(k*n2*n3+n1);
                if(result > target ) break;
                found = true;
                i64 root = round(sqrt(result));
                if(root*root == result){
                    sum += result;
                    printf("%lld\n", result);
                }
            }
            if(!found) break;
        }
    }
    
    printf("%lld\n", sum);
}
