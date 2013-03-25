#include <vector>
#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;

int main(){
    int limit = 20000;
    vector<int> vr;
    vr.resize(limit+1, 0);
    int root = sqrt(limit/6)+1;
    for(i64 ia = 1; ia <=root; ++ia){
        i64 ibmax = sqrt((limit)/2);
        for(i64 ib = ia; ib<=ibmax+1; ++ib){
            i64 icmax = (limit/2 - ia*ib)/(ia+ib)+1;
            for(i64 ic =ib;ic<=icmax+1; ++ic){
                i64 block = 2*(ia*ib+ib*ic+ic*ia);
                assert(block>0);
                if(block <= limit)
                    ++vr[block];
                else
                    break;
                for(i64 n = 1; n ; ++n){
                    i64 deltav = block;
                    i64 side = 4LL*(ia + ib + ic)*n;
                    deltav += side;
                    deltav += n*(n-1)*4;
                    assert(deltav>0);
                    if(deltav <= limit)
                        ++vr[deltav];
                    else
                        break;
                }
            }
        }
    }
    int cnt = 0;
    int num = 0;
    for(int i = 1; i<=limit; ++i)
        if(vr[i]==1000)
            printf("ddd %d\n", i);
    printf("%d %d %d %d %d\n",vr[22], vr[46], vr[78], vr[118], vr[154]);
    printf("%d %d\n", cnt, num);
}
