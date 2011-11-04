#include <vector>
#include <cassert>
#include "../lib/primelist.h"
#include <cstdio>
#include <cstdlib>
using namespace std;
//9699690
int main()
{
    //int start = 9699690; //2 3 5 7 11 13 17 19 23 29 31 37
    vector<int> primes;
    vector<int> pflag;
    primeWithin(primes, 1000); 
    vector<pair<int, int> > ifac;
    int max = 0;
    for(int ni =6; ni< 1000000; ni+=6){
    factor(ni, ifac, primes);
    //add our base to the ifac
    pflag.clear();
    pflag.resize(40,0);
    for(unsigned int j = 0; j <ifac.size(); ++j){
        if(ifac[j].first <= 37){
            ifac[j].second += 1;
            pflag[ifac[j].first] = 1;
        }
    }
    for( int i = 0; i < 12; ++i){ // 10 means 37
        if(pflag[primes[i]] == 0)
            ifac.push_back(pair<int, int>(primes[i], 1));
    }
    //ifac adjustment done
    int sfac = 0;
    int total1 = 1;
    int total = 1;
    //first calc all factors
    for(unsigned int i = 0; i < ifac.size(); ++i){
        total1 *= (ifac[i].second+1);
        total *= (ifac[i].second);
    }
    sfac = total;// for 1
        //for i independent factors;
    for(unsigned int i = 1; i <= ifac.size(); ++i){ 
        // need to use next combination
        vector<int> comb;
        comb.resize(i, 0);
        for( unsigned int j = 0; j < i; ++j)
            comb[j] = j;
        do{
            int num = 1;
            int sametype = total;
            for(unsigned int j = 0; j < comb.size(); ++j){
                assert(comb[j] < static_cast<int>(ifac.size()));
                num *= (ifac[comb[j]].second+1);
                sametype /= ifac[comb[j]].second;
            }
            assert(total1 % num == 0);
            //num -= 1;
            sfac += sametype * num;
        }while(next_combination(comb, ifac.size(), i));
    }
    if((sfac+1)/2 > max){
        assert((sfac+1) %2 == 0);
        max = (sfac+1)/2;
        printf(" %d  %d\n", ni, (sfac+1)/2);
//        if(max > 1000) exit(0);
    }
    }
}
