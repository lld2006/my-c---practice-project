// should the number of rectangles are related with the area under:
// in order to use integers, let us define the length of each square to be 2
#include <cstdio>
#include <cassert>
#include "../lib/tools.h"
#include "../lib/typedef.h"
i64 grid_points(int x, int y, int xb, int yb)
{
    int total = 2*y*y-y ;  //y^2 is corner y^2-y is center
    if(x ==0 ||x == xb) return 0;

    int y1 = y - x; //y1 < 0 means reach x axis first
    int y2 = y+x-xb; //y2 < 0 means reach right boundary first
    //assert(y1 >= 0||y2>=0);
    
    if(y1 > 0){//left
       total -= (2*y1*y1-y1); 
    }
    if(y2 > 0){//right
        total -= (2*y2*y2-y2);
    }
    return total;
}
i64 center_points(int x, int y , int xb, int yb)//remember x y are still doubled
{
    int total = 0;
    assert(x > 0 && x < xb);
    assert(y > 0 && y < yb);
    int y1 = y -x;
    int y2 = y+x-xb;
    assert((y1 & 1) == 0);
    assert((y2 & 1) == 0);
    total = 2*y*y- 2*y;  //y^2-1+(y-1)^2
    if(y1 > 0){
        total -=(2*y1*y1-2*y1);
    }
    if(y2 > 0){
        total -= (2*y2*y2-2*y2);
    }
    assert( total %4 ==0);
    return total>>2;
}
i64 num_points(int x, int y, int xb, int yb)
{
    assert(xb >= yb);//otherwise swap x and y in main
    if(x % 2 == 0 && y % 2 == 0){
        assert( ((x & 1) == 0 ) && ((y & 1) == 0) && 
               ((xb & 1) == 0) && ((yb & 1) == 0));
        return grid_points(x/2, y/2, xb/2, yb/2);
    }else{
        assert(((x & 1)== 1) && ((y & 1) == 1));
        return center_points(x,y,xb,yb);
    }
}
i64 gridpoint(int xb, int yb)
{
    if(xb < yb)
        swap(xb, yb);
    i64 sum = xb*(xb+1)*yb*(yb+1)/4;
    xb *= 2;
    yb *= 2;
    for(int x = 2; x < xb; x+=2)
        for(int y = 2; y<= yb; y+=2){
           sum += num_points(x, y, xb, yb);
        }
    for(int x =1; x < xb; x+=2)
        for(int y = 1; y < yb; y+=2){
            sum += num_points(x, y, xb, yb);
        }
    return sum;
}
int main(){
    i64 sum = 0;
    int gxb = 47; int gyb =43;
    for(int i = 1; i<=gxb; ++i)
        for(int j = 1; j<=gyb; ++j)
            sum += gridpoint(i, j);
    printf("%lld\n", sum);
}
