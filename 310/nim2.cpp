#include <vector>
#include <cmath>
#include <cassert>
#include <cstdio>
#include "../lib/typedef.h"
using namespace std;
int check_nim2_value(int n, vector<int>& vnim)
{
    vector<int> vflags;
    vflags.resize(n+1, 0);
    int rmax = sqrt(n);
    if((rmax+1)*(rmax+1) == n)
        ++rmax;
    assert(rmax * rmax <= n);
    for( int i = 1; i<= rmax; ++i){
        int value = n - i*i;
        ++vflags[vnim[value]];
    }
    for(unsigned int j = 0; j < vflags.size(); ++j){
        if(vflags[j] == 0)
            return j;
    }
    return vflags.size();
}
int main()
{
    int limit = 100000;
    vector<int> vnim2;
    vnim2.resize(limit+1, 0);
    int maxvalue = 0;
    for(unsigned int i = 1; i < vnim2.size(); ++i){
        vnim2[i] = check_nim2_value(i, vnim2);
        if(maxvalue < vnim2[i]) maxvalue = vnim2[i];
    }
    vector<int> vcnt;
    vcnt.resize(maxvalue +1 , 0);
    for(unsigned int i = 0; i < vnim2.size(); ++i){
        ++vcnt[vnim2[i]];
    }
    //test 
    // int n1=0;
    //for( int i = 0; i <= limit; ++i)
    //    for( int j = i; j <= limit; ++j)
    //        for( int k = j ;k<=limit; ++k){
    //            if((vnim2[i] ^ vnim2[j] ^ vnim2[k]) == 0){
    //                printf("%d %d %d\n", i,j, k);
    //                ++n1;
    //            }
    //        }
    //printf("%d\n",n1);
    //return 0;
    ////////////////////////
    i64 total = 0;
    for(unsigned int i = 0; i < vcnt.size(); ++i){
        if(vcnt[i] == 0) continue;
        for(unsigned int j = i+1; j < vcnt.size(); ++j){
            if(vcnt[j] == 0) continue;
            for(unsigned int k = j + 1;k <vcnt.size(); ++k){
                if(vcnt[k]== 0) continue;
                //now i j k triples found in just one order
                if((i ^ j ^ k)==0) //losing position
                    total += (i64)vcnt[i] * vcnt[j] * vcnt[k];
            }
        }
    }
    
    //configs involving 3 zeros;
    total += vcnt[0];//all 3 zeros equal
    total += vcnt[0]*(vcnt[0]-1);
    total += (i64)vcnt[0] *(vcnt[0]-1) *(vcnt[0]-2)/6;
    //now only one zero
    i64 c1 = 0;
    for(unsigned int i = 1; i < vcnt.size(); ++i){
        c1 += (i64)vcnt[i]*(vcnt[i] -1)/2;
        c1 += vcnt[i];// 2 identical 
    }
    total += c1 * vcnt[0];
    printf("%lld\n", total);
}
