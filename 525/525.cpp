#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstdlib>
//this is an easy problem, if one can do some derivatives on paper
//actually this is d s/d theta
double s(double theta, double a, double b, double& cp, double& sp)
{
    double a2 = a * a;
    double b2 = b * b;
    double ct = cos(theta);
    double st = sin(theta);
    double ct2 = ct * ct;
    double st2 = st * st;
    double rad2 = (a2*ct2 + b2*st2);
    double r = sqrt(rad2);
    double r2 = sqrt(a2*st2 + b2*ct2);
    double s2th = sin(2*theta);
    double cphi = (a2-b2)*s2th/2;
    double sphi = a*b;
    double den = sqrt(sphi*sphi + cphi*cphi);
    cphi/=den; sphi/=den;
    double dphidtheta = -(a2- b2)*a*b*cos(2*theta)/(den*den);
    double drdtheta = (b2 - a2)*s2th/(2*r);
    double dx = drdtheta* cphi-r* sphi*dphidtheta + r2;
    double dy = r* cphi*dphidtheta+drdtheta*sphi;
    cp = dx;
    sp = dy;
    return sqrt(dx*dx + dy*dy);
}
int main(int argc, char* argv[])
{
    double pi = atan(1)*4;
    int seg = 1000000;
    double dtheta = 2* pi / seg;
    double a = 3, b = 1;
    if(argc == 3){
        a=atof(argv[1]);
        b=atof(argv[2]);
    }
    double sum = 0;
    double x=0, y=0;
    for( int i = 0; i <= seg; ++i){
        double t = i * dtheta;
        double cp, sp;
        double ds = s(t, a, b, cp, sp);
        x+= cp*dtheta;
        y+= sp*dtheta;
        //printf("%f %f %f\n", t, x, y);
        if(i == 0||i==seg)
            ds /= 2;
        sum += ds;
    }
    sum *= dtheta;
    printf("%20.15f\n", sum);
}
