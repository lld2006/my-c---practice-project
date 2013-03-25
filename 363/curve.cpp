#include <cstdio>
#include <cmath>
double tangent(double t, double v)
{
    double dx=(6*t-9*t*t)*v+6*t*(t-1);
    double dy=6*t*(1-t)+3*(3*t-1)*(t-1)*v;
    double dl=sqrt(dx*dx+dy*dy);
    return dl;
}
int main()
{
    double length = 0;
    double limit = 1000000;
    double pi = atan(1.0)*4;
    double v=2.0-sqrt((22-5*pi)/3);
    for(double xi = 0; xi < limit; xi += 1.0){
        double x = xi +0.5;
        x/=limit;
        length += tangent(x, v);
    } 
    length /= limit;
    double result = 100.0*(length-pi/2)/(pi/2);
    printf("%30.20f\n",result);
}
