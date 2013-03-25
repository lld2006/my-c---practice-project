#include <cstdio>
#include <cmath>
#include <cassert>

int main(){
    double yfinal = sqrt(100-0.01*0.01*4);
    bool notFound = true;
    double k0 = -(10.1+9.6)/(1.4);
    double x0 = 1.4;
    double y0 = -9.6;
    int count = 1;
    while(notFound){
        double kn = y0/x0/4;
        double k1 = ((2+kn*k0)*kn-k0)/(1+2*k0*kn-kn*kn);
        double x1 = (x0*(k1*k1-4)-2*y0*k1)/(k1*k1+4);
        double y1 = y0 - 2* (4*x0+y0*k1)*k1/(k1*k1+4);
        printf("%d %e %e %e\n", count, k1, x1, y1);
        assert(fabs((k1-kn)/(1+k1*kn)-(kn-k0)/(1+kn*k0))<1e-6);
        assert(fabs(x1*x1*4+y1*y1- 100) < 1e-4);
        if(y1 > yfinal) break;
        ++count;
        k0 = k1;
        x0 = x1;
        y0 = y1;
    }
    printf("%d\n",count);
}
