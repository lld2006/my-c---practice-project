#include <cstdio>
#include "../lib/tools.h"
vector<int> primes;
//new means start from new, else continue adding to the tail
//need to monitor the maximum number till now. boolean may be erased.
int primeset(int ndig, int cmax, int cnum, vector<int> nflags, bool bnew){
    if(ndig == 9){
        if(bnew) 
            return 1;
        else 
            return 0;
    }
    int current = 0;
    int sum = 0;
    for(int i =1; i<=9; ++i){
        if(nflags[i]==1) continue;
        if(bnew) 
            current = i;
        else
            current = cnum *10+ i;
        vector<int> flag(nflags);
        flag[i] = 1;
        if(isPrime(current, primes) && current > cmax){
            sum += primeset(ndig+1, current, 0, flag, true);
            sum += primeset(ndig+1, cmax, current, flag, false);
        }else{
            sum += primeset(ndig+1, cmax, current, flag, false);   
        }
    }
  return sum;
}
int main(){
    int limit = 100200;
    primeWithin(primes, limit);
    vector<int> nflags;
    nflags.resize(10,0);
    nflags[0]= 1;
    int count = primeset(0, 0, 0, nflags, true);
    printf("%d\n",count);
}
