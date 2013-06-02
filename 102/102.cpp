#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>
//lesson consider the special case y == 0

using namespace std;

bool crossX(int x1, int y1, int x2,int y2, double& cross)
{
    if( y1 * y2 >= 0 ) return false;
    
    if( x1 == x2){
        cross = x1;
        return true;
    }

    double k = (double)(y2 - y1)/(x2 - x1);
    cross = x1 -y1/k ;
    assert(fabs(cross) > 1e-8);
    return true;
}

int main()
{
    FILE* fp;
    fp = fopen("triangles.txt", "r");
    int x[3], y[3];
    int pos=0 , count = 0;
    double  cross = 0;
    int prod = 1;
    while(fscanf(fp, "%d %d %d %d %d %d", x, y, x+1, y+1, x+2, y+2)==6){
            pos = 0;
            prod = 1;
            if(crossX(x[1], y[1], x[2], y[2], cross)>0) {++pos; if(cross < 0)prod = -prod;}
            if(crossX(x[1], y[1], x[0], y[0], cross)>0) {++pos; if(cross < 0)prod = -prod;}
            if(crossX(x[2], y[2], x[0], y[0], cross)>0) {++pos; if(cross < 0)prod = -prod;}
            int x0 = 0;
            for(unsigned int i = 0; i < 3; ++i){
                if(y[i] == 0) x0 = x[i];
            }
            assert(pos <= 2 );
            if(pos == 1){
                if(x0 * cross < 0){
                    ++count;
                    continue;
                }
            }
            
            assert(prod != 0.0);
            if(pos == 2 && prod == -1) ++count;
        }
    printf("%d\n",count);
}
