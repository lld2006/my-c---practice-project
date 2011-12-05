#include <cmath>
#include <cstdio>

int main(){
    //printf("%f\n", log(2.71828));

    //for(int n = 334; n <= 1000; ++n){
    //    int m = 1000 - n;
    //    double f = static_cast<double>((2*n - m))/2000;
    //    double value = m*log(1-f)+n*log(1+2*f)-9*log(10);
    //    if(value >=0){
    //        printf("%d\n", n);
    //        break;
    //    }
    //}
    //calculate 1000!/500!/500! /2^1000 need 432 to 1000
    long double sum = -1000*log((long double)2);
    for(unsigned int i = 0; i <= 499; ++i){
        sum += log((long double)(1000-i))-log((long double)(i+1));
    }
    long double p500 = exp(sum);
    long double ptot = (long double)(1)/(long double)2+p500/(long double)2;
    long double pt = p500;
    for(unsigned int i = 500; i>=433; --i){
        pt *= (long double)(i)/(long double)(1001-i);
        ptot += pt;
    }
    printf("%30.20Lf\n", ptot);
}
