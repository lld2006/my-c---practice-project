#include "../lib/tools.h"
//some of the key point of the problem
//even number has no contribution, 
//
i64 get_mod_np1(i64 n)
{
    return 0;
    //assert( n & 1);
    //
    //if(n % 4 == 1){
    //    i64 nmod = (n+1)/2;
    //    i64 res = powermodule(n, n-1, )
    //    
    //}else{// n % 4 == 3

    //}
}
int main()
{
    int nmax = 500000000;
    //nmax = 100;
    vector<int> vtotient;    
    vtotient.resize(nmax/2, 0);
    for(unsigned int i = 0; i< vtotient.size(); ++i )
        vtotient[i] = 2*i+1;
    for(unsigned i = 1; i< vtotient.size(); ++i){
        int np;
        //only process on primes
        if(vtotient[i] == 2*i+1){
            np = 2*i+1;
            for(unsigned int j = i; j < vtotient.size(); j+=np){
                vtotient[j]/=np;
                vtotient[j] *= (np-1);
            }
        }
    }
    //now all numbers get their totient number
    i64 sum = 0;
    for(i64 i = 0; i < vtotient.size(); ++i){
        //we cannot brute force the number mod (n+1) 
        //or mod (n^2 -1) since it is too big.
        //what we can do is to use chinese remainder theorem
        sum += vtotient[i]; 
    }
    printf("%lld\n", sum);
}
