#include "../lib/tools.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
int main()
{
    int limit = 250250;
    int mbase = 250;
    i64 mb2 = 10000000000000000LL;
    vector<i64> dpvec, dpvec1;
    dpvec.resize(mbase, 0);
    dpvec1.resize(mbase, 0);

    dpvec[0] = 1;
    for( int im = 1; im <= limit; ++im){
        int value = powermodule(im%mbase, im, mbase);
        for(unsigned int j = 0; j < dpvec.size(); ++j){
            int j1 = (j + value)%mbase;
            dpvec1[j1] = (dpvec[j1] + dpvec[j])%mb2;
        }
        dpvec.swap(dpvec1);
    }
    printf("%lld\n", dpvec[0]-1);
}
