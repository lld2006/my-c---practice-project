#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <cmath>
int main(){
    u64 sum = 0; 
    double ne = 2.718281828459;
    for(int i = 5; i<= 10000; ++i){
        int rmax = floor((double)i/ne);
        if(pow((double) i/rmax, rmax) < pow((double) i/(rmax+1), rmax+1))
            ++rmax;
        int gi = gcd(i, rmax);
        int rp = rmax/gi;
        if(rp == 1){
            sum -= i;
            continue;
        }
        while(rp  % 2 == 0){
                rp/= 2;
            }
        while(rp % 5 == 0){
            rp /= 5;
        }
        if(rp ==1)
            printf("%d %d %d\n", i, rmax, rp);
        if( rp == 1 )
            sum -= i;
        else 
            sum += i;
    }
    printf("%lld\n", sum);
}
