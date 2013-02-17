#include <cstdio>
#include "../lib/tools.h"
int main()
{
    int nmax = 0;
    for(int i = 101; i< 1000; ++i){
        if(i%10 ==0) continue;
        for(int j = i; j< 1000; ++j) {
            if((i %2 == 0 && j % 5 == 0) || (i%5==0 && j % 2 ==0)) continue;
            int num = i * j;
            if(nmax < num && isPalindromic(num, 10) )
                nmax = num;
            
        }
    }
    printf("%d\n", nmax);
}
