#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "../lib/tools.h"
//this problem is boring and doesnot create too much pleasure !
int main()
{
    int n = 3675787; //1009*3643
    int phi = 3671136; //2 3 7 607
    i64 sum = 0;
    int p = 1009;
    int q = 3643;
    for( int i = 5; i < phi; i+=2){
        if(i%3==0 || i%7==0 ||i%607 == 0) continue;
        if(gcd(i-1, p-1)!=2) continue;
        if(gcd(i-1, q-1)!=2) continue;
        sum += i;
    }
    printf("%d %lld\n", n,sum);
}
