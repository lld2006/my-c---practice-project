#include <cstdio>
#include "../lib/tools.h"

// largest prime factor = upper
// how many hamming numbers are there within number
int hamming( int number, const vector<int>& primes, int upper){
    if(number == 0) return 0;
    int sum = 1; //1 is always valid hamming number
    for( int i = 0; i <= upper; ++i){
        //let us say the laregest prime factor is primes[i];
        int n2 = number / primes[i]; 
        sum += hamming(n2, primes, i);
    }
    return sum;
}
int main(){
    vector<int> primes;
    int thresh = 1000000000;
    primeWithin(primes, 100);
    int nsize = primes.size();
    int sum = hamming( thresh, primes, nsize-1);
    printf("%d\n", sum);
}
