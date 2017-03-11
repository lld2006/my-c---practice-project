#include <cstdio>
#include <cmath>
#include <cassert>
long double a = 3.0;
long double f(long double z)
{
    long double a2 = a * a ;
    long double x1 = a2*(1.0-z*z);
    long double s =  sqrt(x1 + a2*a2*z*z);

    long double ret = x1*(1+a2*a2/(s*s*s))*(1+1.0/s)*(1.0+1.0/s);
    return ret;
}
int main()
{
    long double pi = atan(1.0)*4.0;
    int nseg = 256000000; 
    long double v0 = f(0.0) + f(1.0);
    long double v1 = 0.0, d=0.0;
    long double delta = 1.0/nseg;
    for(int i = 1; i< nseg; ++i){
        d += delta;
        v1 += f(d);
        assert(d < 1.0 && d > 0);
    }
    v0 = (v0 +2.0*v1)/nseg-4.0/3*a*a;
    printf("%20.15f\n", (double)(pi*v0));
}
