#include <cstdio>
#include <cstdlib>
#include "../lib/tools.h"
#include <algorithm>
using namespace std;
/*
//prod is the value for n the corresponding i/n is 4 delta-n, delta must be less than prod
int checkSolutions(int value, int prod, vector<IntPair> ifac,set<int>& flags){
    int count = 0;
    if(flags.insert(prod).second){
        int quo = value /prod;
        int div = (quo+prod)/4;
        int remainder = (quo+prod)%4;
        if(remainder == 0 && div < prod ) ++count;
    }
    for(unsigned int i = 0; i < ifac.size();++i){
        vector<IntPair> ifac2(ifac);
        int prod2 = prod * ifac[i].first;
        --ifac2[i].second;
        if(ifac2[i].second == 0){
            if(i != ifac2.size() - 1)//last one
                swap(ifac2[i], ifac2[ifac2.size()-1]);
            ifac2.pop_back();
        }
        count += checkSolutions(value, prod2, ifac2, flags);
    }
    return count;
}
int main(){
    int limit = 1000000;
    vector<int> primes;
    vector<IntPair> ifac;
    primeWithin(primes, limit);
    int count = 0;
    set<int> flags;
    //factor(1155, ifac, primes);
    //int sol = checkSolutions(1155, 1, ifac, flags);
    //printf("%d\n",sol); 
    //exit(0);
    for(int i = 4; i<= limit; ++i){
        if( i % 1000 == 0) printf("%d\n", i);
        factor(i, ifac, primes);
        int product = 1;
        for(unsigned int j = 0; j < ifac.size(); ++j){
            product *= (ifac[j].second+1);
            if(product < 10) continue;
            flags.clear();
            int number = checkSolutions(i, 1, ifac, flags );
            if(number == 10)
                ++count;
        }
    }
    printf("%d\n", count);
}
*/
int main(){
    int limit = 50000000;
    vector<int> flags;
    flags.resize(limit + 1, 0);
    for(i64 n = 1; n <= limit; ++n){
        i64 deltamax = ((double)limit/n+n)/4+1;
        if(n < deltamax) deltamax = n;
        for(i64 delta = n/4; delta < deltamax; ++delta){
        i64 prod = (4 * delta -n)* n;
        if(prod > limit|| prod <= 0) continue;
        flags[prod]++;
        }
    }
    int num = count(flags.begin(), flags.end(), 1);
    printf("%d\n", num);
}
