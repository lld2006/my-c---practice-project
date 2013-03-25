#include <cstdio>
#include <cassert>
#include <cstdlib>
#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <numeric>
#include <cmath>
#include <algorithm>
using namespace std;
//lesson, do not use initial value in a loop
//do not let it fall through if nothing need to be done in a loop, 
//be careful about the continue part  on line 64

void markFlag(i64 start, i64 shift, vector<i64>& flags){
    i64 pos =start;
    i64 value;
    while(pos < static_cast<int>(flags.size())){
        if(flags[pos] == 1 || flags[pos] == -1){
            pos += shift;
            continue;
        }
        if(flags[pos]>1) 
            value = flags[pos];
        else
            value = pos * pos * 2 - 1;
        while(value % shift == 0)
            value /= shift;
        //assert(pos != 31);
        flags[pos] = value;
        pos += shift;
    }
}

int main(){
    
    //i64 limit  = 500000;
    i64 limit  = 50000000;
    //i64 limit = 100;
    vector<int> primes;
    primeWithin(primes, 1.42*limit);
    vector<i64> flags;

    flags.resize(limit+1, 0); //flag of prime, init with 0 

    //int pos = 0;
    for(unsigned int n = 2; n <= limit; ++n){
        if(n % 100000 == 0)
            printf("%d\n", n);
        i64 value = (i64)n*n*2-1;
        i64 prime;
        if(flags[n]== 0){// not determined yet, composite number will become 1 eventually
            i64 root = sqrt((double)value+1);
            if( root * root == value) 
                prime = root;
            else{ 
                prime = value;
                flags[n]= -1; //prime
            }
        }
        else if(flags[n] > 1)
            prime = flags[n];
        else{
            assert(flags[n] == 1);
            continue;
        }
        i64 pos;
        if( value == prime )
            pos = n + prime;
        else
            pos = n;
        i64 pos2 = prime - n%prime;
        markFlag(pos, prime, flags);
        markFlag(pos2, prime, flags);
    }
    int ct = count(flags.begin(), flags.end(), -1);
    printf("%d\n", ct);
}
