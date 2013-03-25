#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include "../lib/tools.h"

using namespace std;
int main()
{
    bool flag = true;
    int target = 0;
    set<int> prod;

    vector<int> nvec;
    nvec.resize(9, 0);
    for(int i = 0; i < 9; ++i)
        nvec[i] = i + 1;
    while( flag ){
        int xa = 0, xb = 0, xp = 0;
        if(nvec[1]*nvec[4] % 10 == nvec[8]) {
            for ( int i = 0; i < 2; ++i){
                xa *= 10;
                xa += nvec[i];
            }

            for ( int i = 2; i < 5; ++i){
                xb *= 10;
                xb += nvec[i];
            }

            for ( int i = 5; i < 9; ++i){
                xp *= 10;
                xp += nvec[i];
            }
            if(xa * xb == xp ) {
                printf("%d %d xp=%d\n",xa, xb, xp);
                prod.insert(xp);
            }
        }
        flag = next_permutation( nvec.begin(), nvec.end());
    }
    for(int i = 0; i < 9; ++i)
        nvec[i] = i + 1;
    flag = true;
    while(flag){
        int xa = 0, xb = 0, xp = 0;
        if(nvec[0]*nvec[4] % 10 == nvec[8]) {
            xa = nvec[0];

            for ( int i = 1; i < 5; ++i){
                xb *= 10;
                xb += nvec[i];
            }
            for ( int i = 5; i < 9; ++i){
                xp *= 10;
                xp += nvec[i];
            }
            if(xa * xb == xp){
                printf("%d %d xp=%d\n",xa, xb, xp);
                prod.insert(xp);
            }
        }
        flag = next_permutation(nvec.begin(), nvec.end());
    }
    for( set<int>::iterator iter = prod.begin(); iter != prod.end(); ++iter){
        target += *iter;
    }
    printf("%d\n", target);
    return 0;
}
