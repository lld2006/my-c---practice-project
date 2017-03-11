//I do not think anyone can learn too much from this problem
#include <cstdlib>
#include <cstdio>
#include <cmath>
int main(int argc, char* argv[])
{
    double pi4 =atan(1.0);
    int n = 1;
    if(argc==2) n=atol(argv[1]);
    double y = n+1-sqrt(2*n);
    y/=(n*n+1);
    double area =  (1- n*y+y-atan((1-n*y)/(1-y)))/2;
    printf("%15.10f\n", area/(1-pi4));
}
