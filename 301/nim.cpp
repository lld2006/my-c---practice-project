#include "../lib/typedef.h"
#include <cstdio>
#include <bitset>

int main(){
    int count = 0;
    i64 max = 1<<30;
    for(i64 i = 1; i <= max; ++i){
        i64 n1 = i;
        i64 n2 = 2*i;
        i64 n3 = 3*i;
        n1 = n1 ^ n2;
        n1 = n1 ^ n3;
        if(n1 == 0)
            ++count;
    }
    printf("%d\n", count);
}
