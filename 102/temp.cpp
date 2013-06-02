#include <cstdio>
#include <cassert>
#include <algorithm>
//lesson consider the special case y == 0

using namespace std;

class point
{
  public:
    point():d_x(0), d_y(0){}
    point(int x, int y):d_x(x), d_y(y){}
    int x() const {return d_x;}
    int y() const {return d_y;}
    void set_point(int x, int y){
      d_x = x;
      d_y = y;
    }
  private:
    int d_x;
    int d_y;
};
int direction(const point& pi, const point& pj, const point& pk)
{
    int xik = pk.x()-pi.x();
    int yik = pk.y()-pi.y();
    int xij = pj.x()-pi.x();
    int yij = pj.y()-pi.y();
    return xik*yij-yik*xij;
}
//see if pk is on line segment ij
bool on_segment(const point& pi, const point& pj, const point& pk)
{
   int minx = pi.x() < pj.x()?pi.x():pj.x(); 
   int miny = pi.y() < pj.y()?pi.y():pj.y();
   int maxx = pi.x() < pj.x()?pj.x():pi.x(); 
   int maxy = pi.y() < pj.y()?pj.y():pi.y();
   if((minx <= pk.x() && pk.x()<= maxx) && miny <= pk.y() && pk.y()<= maxy)
       return true;
   else
       return false;
}
int segment_intersection(point& p1, point& p2, point& p3, point& p4)
{
    int d1 = direction(p3, p4, p1);
    int d2 = direction(p3, p4, p2);
    int d3 = direction(p1, p2, p3);
    int d4 = direction(p1, p2, p4);
    if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0))&& 
       ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return 2;
    else if( d1 == 0 && on_segment(p3, p4, p1))
        return 1;
    else if( d2 == 0 && on_segment(p3, p4, p2))
        return 1;
    else if( d3 == 0 && on_segment(p1, p2, p3))
        return 1;
    else if( d4 == 0 && on_segment(p1, p2, p4))
        return 1;
    return 0;
}
bool crossX(int x1, int y1, int x2,int y2, double& cross)
{
    if( y1 * y2 >= 0 ) return false;
    if( x1 == x2){
            cross = x1;
            return true;
        }

    double k = (double)(y2 - y1)/(x2 - x1);
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
        int cross = 0;
        if (segment_intersection(point(x[1],y[1]), point(x[2], y[2]),  point(-1000, 0), point(1000, 0)))
            ++cross;
        if (segment_intersection(point(x[3],y[3]), point(x[2], y[2]),  point(-1000, 0), point(1000, 0)))
            ++cross;
        if (segment_intersection(point(x[1],y[1]), point(x[3], y[3]),  point(-1000, 0), point(1000, 0)))
            ++cross;
            //pos = 0;
            //prod = 1.0;
            //if(crossX(point(x[1], y[1]), x[2], y[2], cross)>0) {++pos; prod *= cross;}
            //if(crossX(x[1], y[1], x[0], y[0], cross)>0) {++pos; prod *= cross;}
            //if(crossX(x[2], y[2], x[0], y[0], cross)>0) {++pos; prod *= cross;}
            //if(pos >= 3)
            //{
            //    printf("alas\n");
            //}
            //assert(pos <= 2);
            //if(pos == 2 && prod < 0) ++count;
        }
    printf("%d\n",count);
}
