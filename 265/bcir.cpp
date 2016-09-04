#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;

int ndig = 5;
int maxp = 32;
int mod = 16;

i64 searchCircle(vector<int> bvec, vector<bool>& flags, int pcurr, int cvalue){
    i64 sum = 0;
    if(pcurr == maxp -1){
        vector<bool> ft(flags);
        for(int i =0; i< ndig -1; ++i){
            cvalue %= mod;
            cvalue *= 2;
            if(ft[cvalue])
                return 0;
            ft[cvalue] = true;
        }
        for(unsigned int i = 0; i< bvec.size(); ++i){
            sum *= 2;
            sum += bvec[i];
        }
        return sum;
    }
    ++pcurr;
    int ct = cvalue% mod; //remove the highest digit
    ct *= 2;
    for(int i = 0; i < 2; ++i){ //binary system 0, 1 only
        int ct2 = ct + i;
        if(flags[ct2]) continue;
        flags[ct2] = true;
        bvec[pcurr] = i;
        sum += searchCircle(bvec, flags, pcurr, ct2);
        flags[ct2] = false;
        bvec[pcurr] = 0;
    }
    return sum;
}
int main()
{
    vector<bool> flags;
    flags.resize(32,0);
    flags[0] = true;
    flags[1] = true;
    vector<int> bvec;
    bvec.resize(maxp, 0);
    bvec[ndig] = 1;
    // the initial setup part is done
    // start from 000001 the rest need to search;
    i64 sum = searchCircle(bvec, flags, ndig, 1);
    printf("%lld\n", sum);
}
