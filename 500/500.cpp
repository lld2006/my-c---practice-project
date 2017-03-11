#include <cstdio>
#include <cstdlib>
#include <vector>
#include "../lib/tools.h"
#include <queue>
using namespace std;

i64 chinese_remainder_theorem(const vector<i64>& vp, const vector<i64>& vr)
{
    i64 N = 1;
    for(unsigned int i = 0; i < vp.size(); ++i)
        N*= vp[i];
    i64 sum = 0;
    for(unsigned int i = 0; i< vp.size(); ++i){
        i64 a =  N /vp[i];
        i64 b = vp[i];
        i64 x=1, y=1, gcd=1;
        extended_euclid(a, b, x, y, gcd);
        if((a *x ) % b != 1){
            assert(x < 0);
            x+=b;
            assert((a * x )% b == 1);
        }
        sum +=  vr[i] * a *x;
    }
    sum %= N;
    return sum;
}
struct logPowNumber
{
    int base;
    int power;
    int index;//index in prime vector
    double logValue;
    logPowNumber(int b, int p, int i, double l):base(b), power(p), index(i), logValue(l){}

};
class logLess
{
    public:
        bool operator()(const logPowNumber& l1, const logPowNumber& l2)
        {
            return l1.logValue > l2.logValue;
        }
};
int main(int argc, char** argv)
{
    //OK, first need to notice that the numnber in the queue will
    //soon become huge, so use log to avoid large numbers.
    vector<int> primes;
    vector<int> primepow;
    vector<double> logprime;
    primeWithin(primes, 8000000);
    //results are stored in primepow, final power for each prime
    primepow.resize(primes.size(), 0 );
    logprime.resize(primes.size(), 0 );

    priority_queue<logPowNumber, vector<logPowNumber>, logLess> vpq;

    for(unsigned int i = 0; i < primes.size(); ++i){
        logprime[i] = log(primes[i]);
        vpq.push(logPowNumber(primes[i], 1, i, logprime[i]));
    }
    int total = 0;
    int max = 0;
    i64 nmod = 500500507LL;
    while(total < 500500){
        const logPowNumber& nt = vpq.top();
        ++total;
        int index = nt.index;//prime index
        int base = nt.base;
        int power = nt.power;
        double val = nt.logValue;
        if(base > max) max = base;
        primepow[index]  = (1<<power) - 1;
        vpq.pop();
        vpq.push(logPowNumber(base, power+1, index, val*2.0));
    }
    printf("primesize = %u max = %d\n", primes.size(), max);
    i64 prod = 1;
    for(unsigned int i = 0; i < primepow.size(); ++i){
        i64 np = primepow[i];
        if(np == 0) break;
        i64 val = powermodule(primes[i], np, nmod );
        prod *= val;
        prod %= nmod;
    }
    printf("%lld\n", prod);
}
