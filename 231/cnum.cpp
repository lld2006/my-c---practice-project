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
    vector<int> primes;
    int num1=200000000, num2 = 50000000;
    primeWithin(primes, num1);
    i64 sum = 0;
    for(unsigned int i = 0; i<primes.size(); ++i){
        unsigned int prime = primes[i];
        int npow = get_power(num1, prime)-get_power(num2, prime)-get_power(num1-num2, prime);
        sum += npow * prime;
        //for all composite numbers
    }
    printf("%lld\n", sum);
}
