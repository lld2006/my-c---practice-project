#include <cstdio>
#include "../lib/typedef.h"
#include "../lib/primelist.h"
#include <vector>
#include <algorithm>

bool radless(IntPair p1, IntPair p2)
{
    return (p1.first < p2.first ||
            (p1.first==p2.first && p1.second < p2.second));
}
int main()
{
    vector<int> primes;
    IntPairVec ifac;
    IntPairVec radvec;
    int top = 100000;
    primeWithin(primes, 320);
    for(int i =1; i <= top; ++i){
        factor(i, ifac, primes);
        int rad=1;
        if(ifac.empty())
            rad = i;
        else{
            for(unsigned int j = 0; j < ifac.size(); ++j)
                rad *= ifac[j].first;
        }
        radvec.push_back(IntPair(rad, i));
    }
    IntPairVec::iterator iter;
    nth_element(radvec.begin(),radvec.begin()+9999, radvec.end(), radless);
    printf("%d\n", (radvec.begin()+9999)->second );
}
