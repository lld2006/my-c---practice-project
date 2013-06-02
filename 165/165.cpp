#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/rational.h"
#include <algorithm>
using namespace std;
typedef pair<rational, rational> RPair;
//lesson division, need to be non zero value for denominator
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
class rless2{
    public:
    bool operator()(const RPair& p1, const RPair& p2)
    {
        return p1.first < p2.first ||(p1.first==p2.first && p1.second < p2.second);
    }
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
void create_line_segment_data(vector<int>& data)
{
    i64 s = 290797;
    i64 mod = 50515093;
    for(unsigned int i = 0; i < data.size(); ++i){
        s = s * s;
        s %= mod;
        data[i] = s % 500;
    }
}
int main()
{
    //learn the creative method to determine whether two line
    //segment intersect with each other.
    vector<int> data;
    vector<pair<rational, rational>> vcross;
    vector<point> points;
    data.resize(20000, 0);
    create_line_segment_data(data);
    points.resize(10000);
    for(unsigned int i = 0; i < 10000; ++i)
       points[i].set_point(data[2*i], data[2*i+1]); 
    for(unsigned int segi = 0; segi < 5000; ++segi)
        for(unsigned int segj = segi+1; segj < 5000; ++segj){
            int ret = segment_intersection(points[2*segi],points[2*segi+1], points[2*segj], points[2*segj+1]);
            if(ret == 2){
                int x1,x2,y1,y2,x3,x4,y3,y4;
                x1 = points[2*segi].x();
                y1 = points[2*segi].y();
                x2 = points[2*segi+1].x();
                y2 = points[2*segi+1].y();
                x3 = points[2*segj].x();
                y3 = points[2*segj].y();
                x4 = points[2*segj+1].x();
                y4 = points[2*segj+1].y();
                if(x1 == x2) {
                    vcross.push_back(RPair(rational(x1, 1, false), rational((y4-y3)*(x1-x3)+y3*(x4-x3), x4-x3, false)));
                }else if(x3==x4){
                    vcross.push_back(RPair(rational(x3, 1, false), rational((y2-y1)*(x3-x1)+y1*(x2-x1), x2-x1, false)));
                }else{
                    int den = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
                    int num1 = (x1*y2-y1*x2)*(x3-x4)-(x1-x2)*(x3*y4-y3*x4);
                    int num2 = (x1*y2-y1*x2)*(y3-y4)-(y1-y2)*(x3*y4-y3*x4);
                    vcross.push_back(RPair(rational(num1, den, false), rational(num2, den, false)));
                }
            }
        }
    sort(vcross.begin(), vcross.end(), rless2());
    int cnt = 1;
    for(unsigned int i = 1; i < vcross.size(); ++i){
        if(vcross[i] == vcross[i-1]) continue;
        ++cnt;
    }
    printf("%d\n", cnt);
}
