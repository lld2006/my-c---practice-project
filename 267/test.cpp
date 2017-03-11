#include <cstdio>
#include <cmath>
//f=0.146885 and k=432 is the minimum k that we can have (1+2f)^(1000-k)(1-f)^k > 1e9
int main()
{
    int limit = 100000;
    double delta = 0.15/limit;
    for(int i = 1; i<limit; ++i){
        double f = delta * i;
        double value = pow(f*2+1, 1+2*f) * pow(1-f, 2-2*f);
        printf("%f, %f %f\n", f, value, 2000.0/3*(1-f));
    }
}
