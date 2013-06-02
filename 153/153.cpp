#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cmath>
#include <cstdio>
vector<i64> facacc;
//the number needed is sum of n/i*i;
i64 tri(i64 n)
{
    return n*(n+1)/2;
}
i64 gsum(int target)
{
    if(facacc[target] > 0)
        return facacc[target];
    int root = sqrt(target);
    i64 total = 0;
    for( int i = 1; i<=target/(1+root);++i){
        total += target/i*i;
    }
    for(int i = 1; i<=root; ++i)
        total += i*(tri(target/i)-tri(target/(i+1)));
    total += target/((root+1)*(root+1));
    facacc[target] = total;
    return total;
}
int main()
{
    int target = 100000000;
    int root = sqrt(target);
    i64 sum = 0;

    //accumulate the values;
    facacc.resize(target +1, 0);
    sum += gsum(target);
    sum += gsum(target/2)*2;
    for( int ia = 1; ia <= root; ++ia){
        int incb = 1;
        if(ia%2 == 0)
            incb = 2;
        for( int ib = ia+1; ib <=root; ib+=incb){
            int square = ia * ia + ib*ib;
            if(square > target) break;
            if(gcd(ia, ib)> 1) 
                continue;
            int nl = target/square;
            sum += gsum(nl)*(ia+ib)*2;
        }
    }
    printf("%lld\n", sum);
}
