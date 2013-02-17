#include <cstdio>
#include "../lib/tools.h"
int main()
{
    //n^2-m^2
    //2*m*n
    int  sum = 1000;
    int limit = 23;
    for( int m = 1; m <= limit; ++m){
        for( int n = m+1; n<=limit; n+=2){
            if(gcd(m,n)>1)
                continue;
            int a = n*n-m*m;
            int b = 2 *m *n;
            int c = n*n+m*m;
            //if(a+b+c <= sum)
            //    printf("%d %d %d %d\n",a, b, c, a+b+c );
            int value = 2*n*(m+n);
            if(sum % value ==0){
                int mult = sum / value;
                a *= mult;
                c *= mult;
                b *= mult;
                printf("%d\n",a*b*c);
            }
        }
    }
}
