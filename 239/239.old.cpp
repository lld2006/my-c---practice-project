#include <cstdio>
//inclusion exclusion principle
//There are 25 prime numbers from 1 to 100
//to make exact 22 dearrangement, we first select 3 of them in the right position. 
//The total number is C_25^3=25*24*23/6=2300;
int main(){
    long double prob=1;
    int prime = 22; //number of primes
    int total = 97; //number of the total number, 3 in position primes
    //excluded
    for(int i = 1; i<= 22; ++i){
        long double tpb = 1;
        for(int j = 1; j<= i; ++j)
            tpb *= (long double)(prime+1-j)/(j*(long double)(total+1-j));
        prob += (i & 1)? -tpb:tpb;
    }
    prob *= (long double)(23)/(99*98);
    printf("%30.20Lf\n", prob);
}
