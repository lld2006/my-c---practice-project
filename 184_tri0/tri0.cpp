#include <cstdio>
#include <cassert>
#include <map>
#include "../lib/typedef.h"
#include "../lib/rational.h"

map<IntPair, IntPair, coord_less> pairmap;
void process_pair(int x, int y)
{
    int xr, yr;
    if(x == 0 && y == 0) return;
    if(x == 0){
       xr = 0;
       yr = y>0? 1:-1;
    }else if ( y == 0){
        yr = 0; 
        xr = x>0? 1: -1;
    }else{
        int xabs = x > 0 ? x:-x;
        int yabs = y > 0 ? y:-y;
        int gxy = gcd( xabs, yabs);
        xr = x/gxy;
        yr = y/gxy;
    }

    IntPair pa(xr, yr);
    map<IntPair,IntPair,coord_less>::iterator iter; 
    iter = pairmap.find(pa);
    if(iter == pairmap.end()){
        pairmap.insert(pair<IntPair, IntPair>(pa, IntPair(1,0)));
    }else{
        (iter->second.first)++;
    }
    //printf("%d %d pairmap size %d\n", x, y, static_cast<int>(pairmap.size()));
}
int main()
{
   int rmax = 105;
   int rmax2 = rmax *rmax;
   for(int i = -(rmax - 1); i <= (rmax - 1); ++i){
       int jmax = sqrt(static_cast<double>(rmax2 - i*i));
       for(int j = -jmax; j <= jmax; ++j)
           if(i * i +j *j < rmax2)
               process_pair(i, j);
   }
   map<IntPair, IntPair, coord_less>::iterator iter, iter2,iter3;
   //the second is the number of points less than x, y
   int sum = 0;
   for(iter = pairmap.begin(); iter != pairmap.end(); ++iter){
        iter->second.second = sum;
        sum += iter->second.first;
   }
   printf("number of points inside is %d pairmap size %d\n", 
           sum, static_cast<int>(pairmap.size()));
   i64 stat = 0;
   int cnt = 0;
   coord_less cobj;
   for(iter = pairmap.begin(); iter != pairmap.end(); ++iter){
       if(iter->first == pair<int, int>(-1, 0))
           break;
        ++cnt;
        if(cnt % 100 == 0)
            printf("%d\n", cnt);
        IntPair pa = iter->first;
        IntPair pna(-iter->first.first, -iter->first.second);
        IntPair pbmax;
        int diff = 0;
        for(iter2= iter; iter2 != pairmap.end(); ++iter2){
            if(iter2->first == pa)
                continue;
            if(iter2->first == pna)
                break;
            int quadb = cobj.quadrant(iter2->first.first, iter2->first.second);
            if(quadb<=2){
                diff = iter2->second.second-iter->second.second-iter->second.first;
            }else{
                diff = sum/2 - iter->second.second-iter->second.first;
            }
            assert(diff >= 0 );
            stat += static_cast<i64>(iter->second.first)*diff * iter2->second.first;
            //printf("pair1 %d %d, pair2 %d %d||%lld %d %d %d\n", 
            //        iter->first.first, iter->first.second, 
            //        iter2->first.first, iter2->first.second,
            //        stat, iter->second.first, diff, iter2->second.first);
        }
   }
   printf("%lld\n",stat);
}
