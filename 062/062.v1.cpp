#include <cstdio>
#include <cmath>
#include <cstdlib>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <unordered_map>
int main()
{
    vector<i64> vbounds;
    for(int i = 8; i < 15; ++i){
        i64 value = pow(10, (double)i/3.0);
        vbounds.push_back(value);
    }
    for(unsigned int i = 0; i< vbounds.size()-1; ++i){
        i64 nstart = vbounds[i]+1;
        i64 nend = vbounds[i+1]+1;
        for( i64 j = nstart; j < nend; ++j){
            i64 j3 = j*j*j;
            int cnt = 0;
            for(i64 k = j+1; k < nend; ++k){
                i64 k3 = k*k*k;
                if(isPermutation(j3, k3)){
                    ++cnt;
                }
                if(cnt == 4){
                    printf("%lld\n", j3);
                    exit(0);
                }
            }
        }
    }
}
