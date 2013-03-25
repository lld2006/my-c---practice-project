#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cmath>
#include <cstdio>

double maxmult(int m ){
    double x1 = (double) 2/ ( m+1);
    double xp = pow(x1, m*(m+1)/2);
    for(i64 i = 2; i <= m; ++i)
        xp *= power(i, i);
    printf("%d %f\n", m, xp);
    return xp;
}
int main(){
    i64 sum = 0;
    for(int i =2; i<= 15; ++i){
        sum += maxmult(i);
    }
    printf("%lld\n", sum);
}
