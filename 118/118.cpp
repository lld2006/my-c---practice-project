#include <cstdio>
#include "../lib/tools.h"
vector<int> pflags; 
vector<int> primes;
//new means start from new, else continue adding to the tail
//need to monitor the maximum number till now. boolean may be erased.
int primeset(int ndig, int cmax, int cnum, vector<int>& flag, bool bnew){
    if(ndig == 9){
        return bnew;
    }
    int current = 0;
    int sum = 0;
    for(int i =1; i<=9; ++i){
        if(flag[i]==1) continue;
        current = cnum*10+i;
        flag[i] = 1;
        if(current > cmax && ((current < 100000 && pflags[current])||isPrime(current, primes))){
            sum += primeset(ndig+1, current, 0, flag, true);
        }
        sum += primeset(ndig+1, cmax, current, flag, false);   
        flag[i] = 0;
    }
    return sum;
}
int main(){
    int limit = 100000;
    vector<int> nflags;
    primeWithin(primes, limit);
    nflags.resize(10,0);
    nflags[0] = 1;
    pflags.resize(100000, 0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        pflags[px] = 1;
    }
    nflags[0]= 1;
    int count = primeset(0, 0, 0, nflags, true);
    printf("%d\n",count);
}
