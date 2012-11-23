#include "../lib/typedef.h"
#include <cassert>
#include <cmath>
#include <cstdio>
i64 limit = 1000000000000000LL;
i64 nmod = 1000000000LL;
i64 sumsquare(i64 n)
{
    i64 n1 =n;
    vector<i64> va{n1, n1+1, 2*n1+1};
    bool flag = false;
    for(unsigned int i = 0 ; i < 3; ++i){
        if(va[i] % 2 ==0){
            va[i]/= 2;
            flag = true;
            break;
        }
    }
    assert(flag);
    flag = false;
    for(unsigned int i = 0; i < 3; ++i){
        if(va[i] % 3 ==0){
            va[i]/= 3;
            flag = true;
            break;
        }
    }
    assert(flag);
    for(unsigned int i = 0; i < 3; ++i){
        va[i] %= nmod;
    }
    i64 result = va[0] * va[1];
    result %= nmod;
    result *= va[2];
    result %= nmod;
    return result;
}
int main()
{
    //limit = 6;
    i64 result = 0;
    i64 root = sqrt(limit);
    for(i64 i = 1; i <= root; ++i){
        i64 sumto = limit/i;
        result += sumsquare(sumto);
        if(result > nmod)
            result %= nmod;
    }
    i64 last = limit;
    for(i64 i = 2; i <= root+1; ++i){
        i64 next = limit/i;
        i64 cnt = last - next;
        last = next;
        i64 tp = sumsquare(i-1);
        tp %= nmod;
        cnt %= nmod;
        tp *= cnt;
        result+= tp;
        result %= nmod;
    }
    printf("%lld\n", result);

}
