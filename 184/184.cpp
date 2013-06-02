#include <cstdio>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <map>
#include "../lib/typedef.h"
#include "../lib/rational.h"

//the first thing I learned is that for integer points. If we do not want to sort those 
//points, we can use the following properties, 2* theta > tan theat >  theta > sin theta 
//for 0< theta < Pi/4;
class pairLess{
    public:
        bool operator()(const IntPair& p1, const IntPair& p2){
            return (p1.second * p2.first < p2.second * p1.first);
        }

};
vector<IntPair> vpairs;
void process_pair(int x, int y)
{
    int gxy = gcd( x, y);
    if(gxy > 1){
        x /= gxy;
        y /= gxy;
    }
    vpairs.push_back(IntPair(x,y));
}
int main()
{
    int rmax = 500;
    rmax = 500;
    int rmax2 = rmax *rmax;
    //on the x or y axis, (# of points 
    //single side is rmax-1)
    for(int i = 1; i <= rmax; ++i){
        for(int j = 1; j <= rmax; ++j){
            if(i * i +j *j < rmax2)
                process_pair(i, j);
            else
                break;
        }
    }
    int nq = vpairs.size();//points in the quadrant
    //now we need to sort it
    sort(vpairs.begin(), vpairs.end(), pairLess());
    vector<int> vn; //number of pairs for each reduced point
    int cindex = 0;
    unsigned int i = 1;
    int cnt = 1;
    vn.push_back(rmax-1);
    while(i < vpairs.size()){
        if(vpairs[i] != vpairs[cindex]){
            if(cnt >= 30) printf("%d %d\n", cindex, cnt);
            vn.push_back(cnt);
            cnt = 0;
            vpairs[++cindex] = vpairs[i];
        }
        ++cnt;
        ++i;
    }
    if(vpairs.back() == vpairs[cindex]) {
        vn.push_back(cnt);
    }
    int val = accumulate(vn.begin(), vn.end(), 0);
    assert(val == nq+rmax-1);
    
    printf("number of different states is %d\n", nq+rmax-1);
    printf("different num is %d\n", vn.size());
    int nsize = vn.size();
    vn.resize(2*vn.size(), 0);
    vn[nsize] = rmax - 1;
    for(int i = nsize-2; i>=0; --i){
        vn[2*nsize-1-i] = vn[i+1];
    }
    i64 sum = 0;
    for(unsigned int i = 0; i < vn.size();++i){
        for(unsigned int j = i+1; j < vn.size(); ++j){
            i64 t =(i64)vn[i]*vn[j]*(2*val-vn[i]-vn[j]); 
            sum += t;
        }
    }
    assert(sum % 3 == 0);
    printf("%lld\n", 2*sum/3);
}
