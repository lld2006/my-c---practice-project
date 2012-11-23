#include <cstdio>
#include <cmath>
#include "../lib/typedef.h"
using namespace std;
//still did not get it, the problem is 
double f(double x, int n)
{
    i64 b = 1<<n;
    return (x-b)*x*x+n;
}
double df(double x, int n)
{
    i64 b = 1<<(n+1); 
    return x*(3*x-b);
}
double newton_solve(int n)
{
    double x = 4, dx=4;
    while(fabs(dx) > 1e-12){
        double fx = f(x, n);
        double dfx = df(x, n);
        dx = fx/dfx;
        x -= dx;
        //printf("x=%30.20g, fx=%30.20g\n", x, fx);
    }
    return x;
}
int main()
{
   double result = newton_solve(2); 
   double prod = 1;
   for(unsigned int i = 1; i<= 30; ++i){
        prod *= result;
        printf("%d %30.20g\n", i, prod);
   }
}
