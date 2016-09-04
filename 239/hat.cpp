#include <cstdio>
//inclusion exclusion principle
//There are 25 prime numbers from 1 to 100
//to make exact 22 dearrangement, we first select 3 of them in the right position. 
//The total number is C^25_3=25*24*23/6=2300; Then use inclusion-exclusion principle,
// k primes in position. The count is C^25_j*(97-j)!, the total possible count is 100!
int main(){
    long double prob=1;
    int prime = 22; //number of primes
    int total = 97; //number of the total number, 3 in position primes
    //excluded
    long double tpb = 1;
    for(int i = 1; i<= 22; ++i){
        tpb *= (long double)(prime+1-i)/(i*(long double)(total+1-i));
        prob += (i & 1)? -tpb:tpb;
    }
    prob *= (long double)(23)/(99*98);
    printf("%22.20Lf\n", prob);
}
