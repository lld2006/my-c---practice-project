#include <string>
#include <set>
#include <cstdio>
#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cassert>
//this is a simple dynamic programming problem. 
//set should not be used, but maybe not so much difference
using namespace std;
int main()
{
    //since each time there is a factor of 6
    //2 for left and right
    //1/3 and 2/3 for P or N;
    //so ignore 6, then we can save time
    string sound("PPPPNNPPPNPPNPN");
    vector<int> primes;
    vector<int> prob;
    prob.resize(2);
    prob[0]=1; prob[1]=2;
    primeWithin(primes, 500);
    set<int> pset(primes.begin(), primes.end());
    vector<i64> oldp; //old position
    vector<i64> newp; //new position
    oldp.resize(501, 0);
    newp.resize(501, 0);
    //last step initialization
    for(unsigned int i = 1; i<oldp.size(); ++i){
        if(pset.find(i)==pset.end())//not a prime
            oldp[i]=4;
        else 
            oldp[i]=2; //2 4 are scaled to 6 otherwise 1 2
    }
    for( int i =13; i>=0; --i){
        bool need_prime = (sound[i]=='P');//this step want a p or n
        bool is_prime = false;
        int  status = (need_prime == is_prime);
        newp[1]= 2*prob[status] * oldp[2];
        newp[500] = 2*prob[status]*oldp[499];
        for(int i = 2; i<500; ++i){
            is_prime = (pset.find(i) != pset.end());
            status = (need_prime == is_prime);
            newp[i] = prob[status] * (oldp[i-1] + oldp[i+1]);
        }
        swap(newp, oldp);
    }
    i64 sum = 0;
    for(int i = 1; i<= 500; ++i){
        assert(oldp[i] > 0);
        sum += oldp[i];
    }
    i64 all = 500*power((i64)6,(i64)15);
    i64 common = gcd(sum, all);
    printf("%lld %lld %lld\n", sum/common, all/common, common); 
}
