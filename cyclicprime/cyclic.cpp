#include<cstdio>
#include<cmath>
#include<vector>
#include<cassert>
#include<algorithm>
#include<set>
#include "../lib/primelist.h"
// TODO find a better algorithm
int main()
{
    int upper = 10000;
    vector<int> pvec;
    primeWithin(pvec, upper);
    vector<int> fvec;
    fvec.resize(upper, 0);
    for( unsigned int i = 0; i< pvec.size(); i++){
        assert( pvec[i] < upper );
        fvec[pvec[i]] = 1;
    }
    
    for(unsigned int i = 0; i < pvec.size(); ++i){
        if( pvec[i] < 1000) continue;
        vector<int> nvec;
        int i1 = pvec[i];
        while ( i1 ){
            int res = i1% 10;
            i1 /= 10;
            nvec.insert(nvec.begin(), res);
        }
        assert(nvec.size() == 4);
        bool flag = true;
        set<int> prime;
        while(flag){
            int num = nvec[0] * 1000  + nvec[1] * 100 + nvec[2]*10 +nvec[3];
            if(fvec[num] == 1)prime.insert(num);
            flag = next_permutation(nvec.begin(), nvec.end());
        }
        if( prime.size() >= 3 ) {
            set<int>::iterator iter;
            nvec.clear();
            nvec.resize(prime.size());
            copy(prime.begin(), prime.end(), nvec.begin());
            for(unsigned int i = 0; i< nvec.size()-2; ++i)
                for(unsigned int j = i+1; j< nvec.size()-1; ++j){
                    int num = nvec[j]*2-nvec[i];
                    if(prime.find(num) != prime.end())
                        printf("%d %d %d\n", nvec[i], nvec[j], num);
                }
        }
    }
}
