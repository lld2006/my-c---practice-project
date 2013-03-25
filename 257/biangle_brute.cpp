#include <cstdio>
#include <cmath>
#include <cstdlib>
#include "../lib/typedef.h"
#include "../lib/tools.h"
int plimit = 100;
//special version for this problem only
int main()
{
    i64 cnt = plimit/3;
    //brute force method
    int amax = plimit/3;
    for(int a = 1; a<= amax; ++a){
        int bmax = (plimit-a)/2;
        for(int b = a; b<= bmax; ++b){
            int cstart = (a==b)? b+1:b;
            int cmax = plimit+1-a-b < a+b? plimit+1-a-b:a+b;
            for(int c = cstart; c< cmax;++c){
                i64 num = (i64)a*(a+b+c);
                i64 den = (i64)b*c;
                if(num == den || num == 2*den){
                    printf("%d %d %d %lld\n",a, b, c, num/den);
                    ++cnt;
                }
            }
        }
    }
    printf("%lld\n", cnt);
}
