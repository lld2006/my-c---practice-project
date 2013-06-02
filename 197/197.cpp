#include <cmath>
#include <cstdio>
int f(double x)
{
    double val = 30.403243784;
    val -= x*x;
    int val1 = pow(2.0, val);
    return val1 ;
}
int main()
{
    int u0 = -1000000000;
    int old;
    for(unsigned int i = 0; i < 1000; ++i){
        old = u0;
        u0 = f(u0*1e-9); 
        printf("%d\n", u0+old);
    }
}
