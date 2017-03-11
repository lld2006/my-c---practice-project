//first Bernoulli numbers are zero for odd n, so only need to consider even
//20010=2*3*5*23*29, it is kind of special, for all primes are small
//this is a clue! It is still not easy to find all numbers that only 
//have p-1 as factors of these five. Let me do some brute force work to
//see if any clue can be found
//======================== TODO still brute force like way of solving it==
#include "../lib/tools.h"
int main()
{
    vector<int> primes;
    primeWithin(primes, 1000000000); 
    //vector<int> ftable;
    //factor_table_min(100000, ftable);
    //for(int i = 1; i<= 350; ++i){
    //    int n = 308*i;
    //    int found = true;
    //    for(unsigned int k = 3; k < primes.size(); ++k){
    //        int prime = primes[k];
    //        if(prime == 23 || prime ==29) continue;
    //        //if(prime * 2 > n) break;
    //        if(n % (prime -1 ) == 0){ 
    //            found = false;
    //            break;
    //        }
    //    }
    //    if(found)
    //        printf("%d\n", i);
    //}
    vector<int> sieves ;
    sieves.resize(1000000000/308+1, 1);
    for(int i = 3; i < static_cast<int>(primes.size()); ++i){
        int np = primes[i]-1;
        if(np == 22 || np == 28) continue;
        if(np % 4 == 0) 
            np >>= 2;
        else if(!(np & 1))
            np >>= 1;
        if(np % 11 == 0){
            np /= 11;
        } 
        if(np % 7 == 0)
            np/=7;
        assert(np > 1);
        for(unsigned int k = np; k < sieves.size(); k+=np){
            sieves[k] = 0;
        }
    }
    int count = 0;
    for(unsigned int k = 1; k< sieves.size(); ++k){
        if(sieves[k]){
            ++count;
            printf("%d %lld\n", count, k*308LL);
            if(count == 100000)
                break;
        }
    }
}
