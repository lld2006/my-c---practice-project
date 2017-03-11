//E(n+1)=E(n) + 1 + average(g(n))
//      =E(n)+(2^n-1)/n
//E(1) = 0;
#include<cstdio>
int main()
{
    int n = 30;
    double avgn = 0.0;
    for( int k = 2; k<=n; ++k){
       double val = (1<<(k-1))-1; 
       val /= k;
       val += avgn;
       avgn = val; 
       printf("%d    %20.10f\n", k, avgn);
    }
}
