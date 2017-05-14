#include <cstdio>
#include <vector>
#include <cstdlib>
#include "../lib/typedef.h"
using namespace std;
// I am revisiting this problem 4 years later. the brute force code does
// not make any sense at all, because even if I figured out how to get the value 
// of f(5), still has no hope to figure out larger numbers. needless to say 1e7
// I acutally need to find some patterns before really attacking this problem
// no clue now
void printb(int n)
{
    for(int k = 3; k>= 0; --k){
        bool is1 = ((n>>k) & 1);
        printf("%d", is1?1:0);
    }
    printf("\n");
}
int main()
{
    //number of ways that will create a '1111' configration
    int pile = 5;
    int nmax = (1<<pile)-1;
    printf("%d\n", nmax);
    int cnt = 0;
    for( int i = 1; i<=nmax; ++i){
       for(int j = 1; j<=nmax; ++j){
           if(j == i) continue;
           for(int k = 1; k<=nmax; ++k){
               if(k==j || k==i) continue;
                for(int l = 1; l<=nmax; ++l){
                    if(l==i || l==j || l==k) continue;
                    for(int m = 1; m<=nmax; ++m){
                        if(m==i||m ==j ||m==k||m==l) continue;
                    if((i^j^k^l^m) != 0){
                        ++cnt;
                        //printb(i); printb(j);printb(k);printb(l);
                        //printf("\n");
                    }
                    }//m
                }
           }
       } 
    }
    printf("total=%d \n",cnt);
}
