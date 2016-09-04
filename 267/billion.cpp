#include <cmath>
#include <cstdio>

int main(){
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
