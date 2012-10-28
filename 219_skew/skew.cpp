#include "../lib/typedef.h"
#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/tools.h"
using namespace std;
/*  
typdef pair<i64, i64> IntPair;
typedef set<IntPair> CostSet;
class costless
{
    public:
        bool operator()(const IntPair& p1, const IntPair& p2)
        {
            if(p1.first+p1.second*4 < p2.first+p2.second*4)
                return true;
            else if(p1.first+p1.second*4 > p2.first+p2.second*4){
                return false;
            }else if(p1.first < p2.first){
                return true;
            }else{
                return false;
            }
        }
};
int main()
{
    int limit = 1000;
    CostSet cset;
    cset.insert(IntPair(1,0));
    cset.insert(IntPair(0,1));
    int cnt = 2;
    while(true){
        CostSet::iterator iter = cset.begin();
        i64 n0 = iter->first;
        i64 n1 = iter->second;
        i64 prod = 1;
    }
}
*/
int dim = 1000;
vector<i64> vc;
i64 combi(int x, int y)
{
    i64 prod = 1;
    i64 imin = x < y? x:y;
    i64 imax = x < y? y:x;

    for(unsigned int i = x+y; i > imax; --i){
        prod *= i;
    }
    for(unsigned int i = 1; i <= imin; ++i){
        prod /= i;
    }
    return prod;
//    assert(x < dim && y < dim);
//    if(x == 0 || y == 0) return 1;
//    if(vc[index0(x, y, dim)] != 0)
//        return vc[index0(x, y, dim)];
//    else{
//        i64 value = vc[index0(x-1, y, dim)] + vc[index0(x, y-1, dim)];
//        vc[index0(x, y, dim)] = value;
//        return value;
//    }
}
int main()
{
    vc.resize( dim*dim, 0);
    i64 cnt = 2;
    i64 cost = 5;
    i64 limit = 1000000000LL;
    for(int xysum = 1; xysum; ++xysum){
        for(int ix = xysum; ix >= 0; ix-=4){
            int iy = (xysum - ix)/4;
            i64 tcnt = combi(ix, iy);
            if(cnt + tcnt <= limit){
                cnt += tcnt;
                cost += (xysum+5)*tcnt;
                //printf("%lld %lld %lld %d %d xysum=%d\n", cnt, cost, tcnt, ix, iy, xysum);
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
