#include <cstdio>
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


    double k = (double)(y2 - y1)/ (x2 - x1);
    cross = x1 -y1/k ;
    return true;
}

int main()
{
    FILE* fp;
    fp = fopen("triangles.txt", "r");
    int x[3], y[3];
    int pos=0 , count = 0;
    double prod = 1.0, cross = 0;
    while(fscanf(fp, "%d %d %d %d %d %d", x, y, x+1, y+1, x+2, y+2)==6){
            pos = 0;
            prod = 1.0;
            if(crossX(x[1], y[1], x[2], y[2], cross)>0) {++pos; prod *= cross;}
            if(crossX(x[1], y[1], x[0], y[0], cross)>0) {++pos; prod *= cross;}
            if(crossX(x[2], y[2], x[0], y[0], cross)>0) {++pos; prod *= cross;}
            if(pos >= 3)
            {
                printf("alas\n");
            }
            assert(pos <= 2);
            if(pos == 2 && prod < 0) ++count;
        }
    printf("%d\n",count);
}
