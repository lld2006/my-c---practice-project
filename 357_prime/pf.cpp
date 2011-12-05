#include "../lib/tools.h"
//first only numbers of 4n+2 can be of this type. 
//second, n+1 must be a prime. so only primes of 4n+3 are candidates
//
int main(){
    int limit = 100000000;
    limit = 10000;
    vector<int> primes;
    primeWithin(primes, limit);
    vector<bool> flags;
    flags.resize(limit , 0);
}
