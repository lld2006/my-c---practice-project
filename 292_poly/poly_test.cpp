#include <cstdio>
#include <functional>
#include <algorithm>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include "../lib/rational.h"
using namespace std;
vector<vector<vector<i64>>> vmem;
//think about the problem in this way, there are two different 
//possibilities if we do not want to duplicate solutions.
vector<IntPair> vpr;
vector<int> vlen;//store the length of each side
int perilimit=6;
//xc0 yc0 are used for left turn check
//v1 X v2
int cross_product (int vx1, int vy1, int vx2, int vy2)
{
    return  vx1*vy2 - vy1* vx2;
}
//start from the leftmost lowest point, this point is unique for each polygon
//set this point as 0 0
i64 search_polygon_single(int xc, int yc, int pc, int dirIndex, int nsides)//
{
    assert(xc != 0 || yc != 0);
    assert(pc <= perilimit);
    if(yc == 0 && xc < 0) return 0; //violated the assumption that first point is the leftmost lowest point
    
    if(xc==0 && yc == 0 && pc<= perilimit && nsides >= 3) //return to original point with more than 3 sides
        return 1;
    //if the point is too far from 0 0, and perimeter is definitely large, return
    double dlen = sqrt(xc*xc+yc*yc);
    if(dlen > perilimit - pc)
        return 0;
    
    i64 sum = 0;
    //since the direction are now sorted, we can reduce the search space
    for(unsigned int i = dirIndex+1; i < vpr.size(); ++i){
        int xi = vpr[i].first;
        int yi = vpr[i].second;//this is actually the new direction
        int len = vlen[i];
        int dirx = vpr[dirIndex].first;
        int diry = vpr[dirIndex].second;
        if(xi*yc - xc*yi > 0) break;
        if(cross_product(dirx, diry, xi, yi) <= 0)
            continue;
        if(cross_product(xc, yc, xi, yi) < 0 ) 
            continue;
        if(xc*yi==yc*xi){
            int n1 = 0;
            if(xi != 0 ){
                int xr = xc%xi;
                assert(xr == 0);
                n1 = xc / xi;
            }else if(yi != 0 ){ 
                assert(xi == 0 && (yi == 1|| yi==-1));
                n1 = -yc;
            }else{
                assert(0);
            }
            assert(n1 < 0);
            if(pc -n1 * len <= perilimit)
                ++sum;
            continue;
        }

        int pleft = perilimit - pc;
        for( int j = 1; j <= pleft/len; ++j){
            int x1 = xc + xi*j;
            int y1 = yc + yi*j;
            if(y1 < 0) break;
            if(pc + len *j > perilimit) continue;
            sum += search_polygon_single(x1, y1, pc+len*j,i, nsides+1);
        }
    }
    return sum;
}
int main()
{
    int peri2 = perilimit/2;
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
            }else{
                break;
            }
        }
    }
    vpr.push_back(IntPair(1,0));//special in x or y direction
    vpr.push_back(IntPair(0,1));//special in x or y direction
    vpr.push_back(IntPair(-1,0));//special in x or y direction
    vpr.push_back(IntPair(0,-1));//special in x or y direction
    printf("%zu\n", vpr.size());
    sort(vpr.begin(), vpr.end(), coord_less());
    for(unsigned int j = 0; j < vpr.size(); ++j){
        int len = round(sqrt(vpr[j].first * vpr[j].first + vpr[j].second*vpr[j].second));
        vlen.push_back(len);
    }
    //all the possibile elements are ready
    //now initialize the mem vector
    //3 dimension, the first is the intital distance, from 0 0,
    //second is the direction constrain, angle can not less than this index
    //third is the total perimeter to be collected
    vmem.resize(peri2);
    for(unsigned int j=0; j <vmem.size(); ++j){
        vmem[j].resize(vpr.size()+1);
    }
    for(unsigned int i = 0; i < vmem.size(); ++i)
        for(unsigned int j = 0; j < vmem[i].size(); ++j)
             vmem[i][j].resize(120, -1);

    i64 total = 0;
    for(unsigned int i = 0; i< vpr.size(); ++i){
        for(unsigned int j = 1; j <= peri2/vlen[i]; ++j){
            printf("%d len%d j=%d\n",i,vlen[i], j );
            int x0 = j*vpr[i].first;
            int y0 = j*vpr[i].second;
            int p0 = j * vlen[i];
            total += search_polygon_single(x0, y0, p0, i, 1);//the lower left corner
        }
    }
    printf("%lld\n", total);
}
