#include <cstdio>
#include <vector>
#include <numeric>
#include <cassert>
#include "../lib/primelist.h"

using namespace std;

int main()
{
    int upper = 12000;
    int sum = 0;
    //0 find all primes within "upper"
    vector<int> primes;
    vector<int> ifactor;
    vector<int> sieve;
    primeWithin(primes, upper);
    for(int i = 5; i <= upper; ++i){
        //first check the factor in i;
        factor(i, ifactor, primes); 
        //second check the lbound and hbound 
        int lbound, ubound;
        lbound = i/3 + 1;
        ubound = i/2;
        //create the sieve and find all irreducible.
        //lbound ... ubound
        if(ifactor.size() == 0) {//primes
            sum += (ubound - lbound +1);
            printf("%d %d\n", i, sum);
            continue;
        }
        sieve.clear();
        sieve.resize(ubound-lbound+1, 1);
        int xlow, xhigh;
        for(unsigned int j = 0; j < ifactor.size(); ++j){
            if(lbound % ifactor[j] == 0)
                xlow = lbound;
            else{
                xlow = (lbound /ifactor[j]+1) *ifactor[j]; //here made a mistake lesson
                if(xlow == 0) xlow = ifactor[j];
            }
            
            xhigh = ubound / ifactor[j]* ifactor[j];
            for( int k = xlow ; k <= xhigh; k += ifactor[j]){
                assert(k >= lbound);
                assert( k - lbound < static_cast<int>(sieve.size()));
                sieve[k-lbound] = 0;
            }
        }
        //finally collect all prime numerator
        sum = accumulate(sieve.begin(), sieve.end(), sum);
        printf("%d %d\n", i, sum);
    }
    printf("%d\n", sum);
}




