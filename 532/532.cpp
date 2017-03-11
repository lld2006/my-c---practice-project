#include <cmath>
#include <cstdio>
#include <cstdlib>
long double pi = atan(1.0)*4;
long double f(long double h, int n)
{
    long double s = sin(pi/n);
    long double h2 = h*h;
    return  sqrt(1-(1-h2)*s*s)/(sqrt(1-h2)*s*h);
}
int main(int argc, char* argv[])
{
    int nd = 3;
    if(argc == 2)
        nd = atol(argv[1]);
    long double h0 = sqrt(1-0.999*0.999);
    int nseg = 10000000;
    long double sum = 0;
    long double delta = (1.0-1e-8-h0)/nseg;
    for( int i = 0; i<=nseg; ++i){
        long double x = delta * i+h0;
        if(i==0 || i == nseg)
            sum += 0.5*f(x, nd);
        else
            sum += f(x, nd);
        //printf("%d %g\n", i, sum);
    } 
    printf("%Lf %Lf\n", sum*delta, sum*delta*nd);
}
