#include <cstdio>
#include <functional>
#include <algorithm>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include "../lib/rational.h"
#include <unordered_map>
using namespace std;
//vector<vector<vector<vector<i64>>>> vmem;
//think about the problem in this way, there are two different 
//possibilities if we do not want to duplicate solutions.
vector<IntPair> vpr;
vector<int> vlen;//store the length of each side
int perilimit=120;
int peri2 = perilimit/2;
unordered_map<i64, i64> pmap;
//v1 X v2
int cross_product (int vx1, int vy1, int vx2, int vy2)
{
    return  vx1*vy2 - vy1* vx2;
}
i64 get_mem_value(int xc, int yc, int aindex, int peri)
{
    xc += peri;
    yc += peri;
    i64 result = xc;
    result <<= 8;
    result += yc;
    result <<=8;
    result += aindex;
    result <<= 8;
    result += peri;
    auto iter =pmap.find(result);
    if(iter != pmap.end())
        return iter->second;
    else
        return -1;
}
void set_mem_value(int xc, int yc, int aindex, int peri, i64 value)
{
    xc += peri;
    yc += peri;
    i64 result = xc;
    result <<= 8;
    result += yc;
    result <<=8;
    result += aindex;
    result <<= 8;
    result += peri;
    auto ret = pmap.insert(make_pair(result, value));
    assert(ret.second);
}
//start from the leftmost lowest point, this point is unique for each polygon
//set this point as 0 0
//now, we need to memorize the result
// this function fulfill the functionality of number of paths from 0 0 to xc yc with pneed
// and convecx, angleIndex is constrained
i64 search_polygon_single(int xfin, int yfin, int pneed, int angleIndex)//
{
    assert(xfin != 0 || yfin != 0);
    assert(pneed  >= 0);
    assert(angleIndex >= 0 && angleIndex <= static_cast<int>(vpr.size()));
    if(pneed == 0){
        if(xfin == 0 && yfin == 0)
            return 1;
        else
            return 0;
    }
    if(angleIndex == static_cast<int>(vpr.size()))
        return 0;
    i64 nmem = get_mem_value(xfin, yfin, angleIndex, pneed);
    if(nmem >= 0 ) 
        return nmem;
    
    i64 sum = 0;
    //use sorted direction to reduce the search space
    for(unsigned int i = angleIndex; i < vpr.size(); ++i){
        //the new direction
        int xi = vpr[i].first; 
        int yi = vpr[i].second;
        int len = vlen[i];
        //current direction
        int nl=0;
        if(xfin*yi==yfin*xi){// on the same line
            if(xi != 0 ){
                assert(xfin % xi == 0);
                nl = xfin / xi;
            }else{
                assert(xi == 0 && (yi == 1|| yi==-1));
                nl = yfin/yi;
            }
            if(nl > 0 && (pneed -nl * len >= 0))
                ++sum;
            continue;
        }

        for( int j = 1; j <= pneed/len; ++j){
            int x1 = xfin - xi*j;
            int y1 = yfin - yi*j;
            sum += search_polygon_single(x1, y1, pneed-len*j,i+1);
        }
    }
    set_mem_value(xfin, yfin, angleIndex, pneed, sum);
    return sum;
}
int main()
{
    for(int n = 1; n<=10 ;++n){
        for(int m = n+1; ;m+=2){
            if(gcd(m,n)!=1) continue;
            int a = m*m-n*n;
            int b = 2*m*n;
            int c = m*m+n*n;
            if(c < peri2){
                vpr.push_back(IntPair(a, b));
                vpr.push_back(IntPair(b, a));
                vpr.push_back(IntPair(a, -b));
                vpr.push_back(IntPair(b, -a));
                vpr.push_back(IntPair(-a, b));
                vpr.push_back(IntPair(-b, a));
                vpr.push_back(IntPair(-a, -b));
                vpr.push_back(IntPair(-b, -a));
            }else
                break;
        }
    }
    vpr.push_back(IntPair(1,0));
    vpr.push_back(IntPair(0,1));
    vpr.push_back(IntPair(-1,0));
    vpr.push_back(IntPair(0,-1));

    printf("%zu\n", vpr.size());
    sort(vpr.begin(), vpr.end(), coord_less());
    //angle and length part
    for(unsigned int j = 0; j < vpr.size(); ++j){
        int len = round(sqrt(vpr[j].first * vpr[j].first + vpr[j].second*vpr[j].second));
        vlen.push_back(len);
        
    }
    //all the possibile elements are ready
    //now initialize the mem vector
    //dim1  destination x; -peri2 peri2
    //dim2  destination y; -peri2 peri2
    //dim3  angle index, all segment must be equal or greater 
    //      than this index;
    //dim4  perimeter constraint: perimeter max 0-->perilimit

    i64 total = 0;
    for(unsigned int i = 0; i< vpr.size(); ++i){
        for( int j = 1; j <= peri2/vlen[i]; ++j){
            //printf("%d len%d j=%d\n",i,vlen[i], j );
            int x0 = j * vpr[i].first;
            int y0 = j * vpr[i].second;
            int p0 = j * vlen[i];
            i64 tp = search_polygon_single(-x0,-y0, perilimit-p0, i+1);
            if(tp >= 1)
                total += tp - 1;
        }
    }
    printf("mapsize %zu\n", pmap.size());
    printf("%lld\n", total);
}
