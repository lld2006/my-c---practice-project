#include "../lib/typedef.h"
#include <cstdio>
int main(){
    int cnt = 0;
    i64 limit = 25000000;
    for(i64 p = 1; p <= 5000; ++p){
        i64 qu = limit/2/p;
        for(i64 q = 1; q <= qu; ++q){
            i64 a = p*p*q+p-q;
            i64 b = 2*p*q+1;
            i64 c = a+2*q;
            if(a+b+c <= limit)
                ++cnt;
        }
    }
    printf("%d\n", cnt);
}
