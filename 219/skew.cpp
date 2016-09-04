#include "../lib/typedef.h"
#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/tools.h"
using namespace std;
int dim = 1000;
vector<i64> vc;

int main()
{
    vc.resize( dim*dim, 0);
    i64 cnt = 2;
    i64 cost = 5;
    i64 limit = 1000000000LL;
    //limit = 6;
    for(int xysum = 1; xysum; ++xysum){
        for(int ix = xysum; ix >= 0; ix-=4){
            int iy = (xysum - ix)/4;
            i64 tcnt = combination((i64)ix+iy, (i64)iy);
            if(cnt + tcnt <= limit){
                cnt += tcnt;
                cost += (xysum+5)*tcnt;
            }else{
                cost += (limit-cnt)*(xysum+5);
                cnt = limit;
                break;
            }
        }
        if(cnt == limit) break;
    }
    printf("%lld\n",cost);
}
