#include <cstdio>
#include <cmath>
#include <cassert>
double f(double x){
    return (299 - 300*x+(4701-4700*x)*pow(x, 5000))/pow((x-1), 2)+2e11;
}
double df(double x){
    return (-298+300*x-(23505000-47000298*x+23495300*x*x)*pow(x, 4999))/pow(x-1, 3);
}
int main(){
    int iter = 0;
    double xl = 1.000695;
    double x0 = 1.000695;
    double xh = 1.05;
    double xm;
    while (iter < 5){
        //double vl = f(xl);
        //double vh = f(xh);
        //assert(vl * vh <0);
        //xm = (xl +xh)/2;
        //double vm = f(xm);
        //if(vm * vh > 0)
        //    xh = xm;
        //else 
        //    xl = xm;
        double res = f(x0);
        double delta =-(res)/df(x0);
        x0= x0+delta;
        printf("%25.15f %25.15f\n", x0, res);
        ++iter;
    }
}
