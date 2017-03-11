#include "../lib/tools.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
//some comments, first it should be clear that the answer should only contain nonempty set
//second, be careful about operator priority, I made a mistake when I use i1= i1>=mbase ?:;
int main(){
    int limit = 250250;
    int mbase = 250;
    i64 mb2 = 10000000000000000LL;
    vector<int> modvec;
    modvec.resize(limit);
    vector<i64> dpvec;
    dpvec.resize(mbase, 0);

    for(int i = 1; i<= limit; ++i){
        int base = i % mbase;
        int value = powermodule(base, i, mbase);
        modvec[i-1] = value;
    }
    dpvec[0] = 1;
    for(unsigned int im = 0; im < modvec.size(); ++im){
        vector<i64> tvec(dpvec);
        int value = modvec[im];
        if(value != 0){
            for(unsigned int i = 0; i < tvec.size(); ++i){
                int i1 = i + value;
                i1 = (i1>= mbase? i1 - 250: i1);
                assert(value < 250 && value >=0);
                tvec[i1] = dpvec[i];
            }
        }
        for(unsigned int i = 0; i< dpvec.size(); ++i){
            dpvec[i] += tvec[i];
            if(dpvec[i] > mb2) dpvec[i] %= mb2;
        }
    }
    printf("%lld\n", dpvec[0]-1);
}
