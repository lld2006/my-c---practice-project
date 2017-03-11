#include <cstdio>
#include <cmath>
#include <cassert>
double radius(double r0, double r1, double r2){
    double k0 = 1.0/r0;
    double k1 = 1.0/r1;
    double k2 = 1.0/r2;
    double k = 0;
    double root = sqrt(k0*k1+k1*k2+k0*k2);
    double kra = k0+k1+k2+2*root;
    double krb = k0+k1+k2-2*root;
    if(kra*krb <0)
        k = kra> 0? kra : krb;
    else
        k = kra > krb? kra:krb;
    return 1.0/k;
}
double area(double r0, double r1, double r2, int iter) {
    ++iter;
    if(iter > 10) return 0.0;
    double xa = 0;
    double r = radius(r0, r1, r2);
    xa += r*r;
    xa += area(r0, r1, r,  iter);
    xa += area(r0, r2, r,  iter);
    xa += area(r1, r2, r,  iter);
    return  xa;
}
int main(){
    double r1 = (double) 3/ (3+2*sqrt((double)3));
    double xa = 0;
    xa +=3*r1*r1;
    xa += 3*area(-1.0, r1, r1, 0);
    xa += area(r1, r1, r1, 0);
    
    printf("%20.15f\n", 1-xa);
}
