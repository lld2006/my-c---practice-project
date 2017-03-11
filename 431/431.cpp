#include "../lib/typedef.h"
#include <cassert>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
double PI = 3.14;
double alpha = 0;
double talpha = 0;
double radius = 6.0;
double tol = 1e-14;
int tindex(int row, int col)
{
    assert(col <= row);
    return row * (row+1)/2+col;
}
double rho(double r, double theta, double x) 
{
    double dsin = sin(theta);
    return sqrt(r*r- x*x*dsin*dsin) - x* cos(theta);
}

//a factor of 0.5*tan(alpha) should be applied
double dvol(double r, double theta, double x)
{
    double drho = rho(r, theta, x);
    return drho*drho*drho/3.0*talpha;
}

double area(double r, double x)
{
    vector<double> R;
    int nmax = 20;
    R.resize(nmax*(nmax+1)/2, 0);
    double interval = 2*PI;
    int level;
    for( level = 0; level < nmax; ++level){
        if(level == 0){
            R[tindex(0, 0)] = PI * (dvol(r, 0, x) + dvol(r, 2*PI, x));
            interval /= 2.0;
            continue;
        }else{
            double val = R[tindex(level-1, 0)]/2.0;
            int bmax = 1<<level;
            double fsum = 0.0;
            for(int i = 1; i < bmax; i+=2){
                double t = i*interval;
                fsum += dvol(r, t, x);
            }
            val += fsum * interval;
            R[tindex(level, 0)] = val;
        }
        for(int j = 1; j <= level; ++j)
            R[tindex(level, j)] = ((1<<(2*j))*R[tindex(level, j-1)] - R[tindex(level-1, j-1)])/((1<<(2*j))-1);

        double diff = (R[tindex(level, level)] - R[tindex(level, level-1)]);
        if(diff < 0) diff = -diff;
        if(diff < tol && level >= 9) return(R[tindex(level, level)]);
        interval/=2.0;
    }
    return R[tindex(nmax, nmax)];
}
double bsearch(double low, double high, double value)
{
    double mid = (low + high)/2.0;
    while(high - low > tol){
        mid = (low + high)/2.0;
        double da = area(radius, mid);
        if(da < value)
            low = mid;
        else
            high = mid;
    }
    return mid;
}
int main()
{
    PI = atan(1.0)*4.0;
    alpha = 2.0/9.0*PI;
    //alpha = PI/6.0;
    talpha = tan(alpha);
    double sum = 0;
    for(unsigned int i = 20; i<=25; ++i){
        double value =bsearch(0, radius, i*i) ;
        printf("%d %20.15f\n", i, value);
        sum += value;
    }
    printf("%20.15f\n", (double) sum);
}
