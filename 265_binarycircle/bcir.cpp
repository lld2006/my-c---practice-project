#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;

int ndig = 5;
int maxp = 32;
int mod = 16;

i64 searchCircle(vector<int> bvec, vector<int> flags, int pcurr, int cvalue){
    i64 sum = 0;
    if(pcurr == maxp -1){
        for(int i =0; i< ndig -1; ++i){
            cvalue %= mod;
            cvalue *= 2;
            if(flags[cvalue] == 1)
                return 0;
            flags[cvalue] = 1;
        }
        for(unsigned int i = 0; i< bvec.size(); ++i){
            sum *= 2;
            sum += bvec[i];
        }
        return sum;
    }
    ++pcurr;
    int ct = cvalue% mod;
    ct *= 2;
    for(int i = 0; i < 2; ++i){
        int ct2 = ct + i;
        if(flags[ct2]) continue;
        vector<int> ft(flags);
        vector<int> bt(bvec);
        ft[ct2] = 1;
        bt[pcurr] = i;
        sum += searchCircle(bt, ft, pcurr, ct2);
    }
    return sum;
}
int main(){
    vector<int> flags;
    flags.resize(32,0);
    flags[0] = 1;
    flags[1] = 1;
    vector<int> bvec;
    bvec.resize(maxp, 0);
    bvec[ndig] = 1;
    // the initial setup part is done
    // start from 0 1 the rest need to search;
    i64 sum = searchCircle(bvec, flags, ndig, 1);
    printf("%lld\n", sum);
}
