#include "../lib/tools.h"
#include "../lib/int.h"

i64 get_power(int number, int prime){
    int sump = 0;
    while(number >= prime){
        int q = number/prime;
        sump += q;
        number = q;
    }
    return sump;
}
int main(){
    vector<int> cnum, primes;
    cnum.resize(20000001, 0);
    primeWithin(primes, 20000000);
    for(unsigned int i=2; i <= 5000000; ++i)
        cnum[i] = - 1;
    for(unsigned int i= 15000001; i<= 20000000; ++i)
        cnum[i]=1;
    for(unsigned int i = 0; i<primes.size(); ++i){
        unsigned int prime = primes[i];
        unsigned int nprime = 20000000/prime;
        unsigned int nupp = nprime*prime;
        //for all composite numbers
        for(int nx = nprime, num = nupp; nx>=2; --nx, num -= prime){
            cnum[nx] += cnum[num];
            cnum[prime] += cnum[num];
            cnum[num] = 0;
        }
    }
    i64 sum = 0;
    for(unsigned int i=0; i< primes.size();++i){
        assert(cnum[i] >= 0);
        sum += cnum[primes[i]]*primes[i];
    }
    printf("%lld\n", sum);
}
