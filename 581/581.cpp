//need to figure out why!!! TODO
#include <vector>
#include <cstdio>
#include "../lib/tools.h"
#include <queue>
using namespace std;
//the bruteforce version is good, but it has very severe limitations
//it is straight forward, but I cannot create so many primenumbers 
//upto 10^10 or even larger
class i64Less
{
    public:
    bool operator()(const I64Pair& p1, const I64Pair& p2){
        return p1.first > p2.first;
    }
};
int main()
{
    priority_queue<I64Pair, vector<I64Pair>, i64Less> myprq;
    vector<int> primes ={2,3,5,7,11,13, 17, 19, 23, 29, 31,37,41,43,47};
    for(unsigned int i = 0; i < primes.size(); ++i){
        myprq.push(I64Pair(primes[i], i));
    }
    i64 last = 1;
    i64 sum = 0;
    i64 nmax = 1000000000000000LL;
    i64 thresh = 10;
    while(last < nmax){
        if(last > thresh){
            printf("value = %lld size=%d sum=%lld\n", last, (int)myprq.size(), sum );
            thresh *= 50;
        }
        I64Pair nextPair = myprq.top();
        i64 next = nextPair.first;
        assert(next > last);
        myprq.pop();
        if(next == last +1){
            sum += last;
        }
        for(unsigned int k = nextPair.second; k<primes.size(); ++k){
            i64 val = next*primes[k];
            if(val < nmax){
                myprq.push(I64Pair(val, k));
            }
        }
        last = next;
    }
    printf("%lld\n", sum);
}
//int main()
//{
//    i64 nmax = 500000;
//    nmax = 2000000000LL;
//    vector<int> primes;
//    sievePrimes(nmax, primes);
//    vector<bool> ftable;
//    ftable.resize(nmax, true); //has no >47 primes
//    
//    for(unsigned int k = 15; k<primes.size(); ++k){
//        int p = primes[k];
//        for(int m = p; m < ftable.size(); m+=p)
//            ftable[m] = false;
//    }
//
//    
//    i64 sumIndex = 0;
//    i64 max = 0;
//    for(i64 i = 1; i<(i64)ftable.size();++i){
//        if(ftable[i]&&ftable[i-1]){
//            sumIndex += i;
//            max = i;
//        }
//    }
//    printf("%lld %lld\n", sumIndex, max);
//}
