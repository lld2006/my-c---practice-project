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
    double x0 = 1.01;
    double res = f(x0);
    while (fabs(res) > 0.1){
        double delta =-(res)/df(x0);
        if( delta > 1e-4) 
            delta = 1e-4;
        else if ( delta < -1e-4)
            delta = - 1e-4;
        x0= x0+delta;
        printf("%d %25.15f %25.15f\n",++iter, x0, res);
        res = f(x0);
    }
}
