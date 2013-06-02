#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <cmath>
int main(){
    i64 sum = 0; 
    double ne = 2.718281828459;
    for(int i = 5; i<= 10000; ++i){
        int rmax = floor((double)i/ne);
        if(log((double) i/rmax)*rmax < log((double) i/(rmax+1))*(rmax+1))
            ++rmax;
        int gi = gcd(i, rmax);
        int rp = rmax/gi;
        while(rp  % 2 == 0){
                rp/= 2;
            }
        while(rp % 5 == 0){
            rp /= 5;
        }
        sum += (rp==1)? -i:i;
    }
    printf("%lld\n", sum);
}
