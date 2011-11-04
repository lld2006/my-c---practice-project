#include <cstdio>
#include "../lib/tools.h"

// largest prime factor = upper
int hamming( int number, const vector<int>& primes, int upper){
    if(number < 1) return 0;
    int sum = 1; //current state is a qualified hamming number
    for(unsigned int i = 0; i < primes.size(); ++i){
        if(primes[i] > upper || primes[i]>number) break;
        int n2 = number / primes[i];
        sum += hamming(n2, primes, primes[i]);
    }
    return sum;
}
int main(){
    vector<int> primes;
    int thresh = 1000000000;
    primeWithin(primes, 100);
    int sum = hamming( thresh, primes, primes.back());
    printf("%d\n", sum);
}
