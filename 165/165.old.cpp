#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;
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
class double_less
{
  public:
    bool operator()(const pair<double, double>& p1, const pair<double, double>& p2) const
    {
        bool xeq = fabs(p1.first - p2.first) < 1e-11;
        bool yeq = fabs(p1.second - p2.second) < 1e-11;
        if(xeq){
            if(yeq) 
                return false;
            else
                return p1.second < p2.second;
        }else{
            return p1.first < p2.first;
        }
    }
};
int main()
{
    //learn the creative method to determine whether two line
    //segment intersect with each other.
    //int r1, r2;
    //point x1(27, 44), x2(12, 32), x3(46, 53), x4(17, 62), x5(46, 70), x6(22, 40);
    //r1 = segment_intersection(x3, x4, x5, x6);
    //r2 = segment_intersection(x1, x2, x5, x6);
    //printf("23 %d 13 %d\n", r1, r2);
    //exit(1);
    vector<int> data;
    set<pair<double, double>, double_less > intersec_set;
    vector<point> points;
    data.resize(20000, 0);
    create_line_segment_data(data);
    points.resize(10000);
    for(unsigned int i = 0; i < 10000; ++i)
       points[i].set_point(data[2*i], data[2*i+1]); 
    int sum = 0;
    //int cnt = 0;
    for(unsigned int segi = 0; segi < 5000; ++segi)
        for(unsigned int segj = segi+1; segj < 5000; ++segj){
            int ret = segment_intersection(points[2*segi],points[2*segi+1], points[2*segj], points[2*segj+1]);
            if(ret == 2){
                double xr, yr, yr1;
                if((points[2*segi].x() == points[2*segi+1].x())||
                    (points[2*segj].x()==points[2*segj+1].x())){
                    if(points[2*segi].x()==points[2*segi+1].x()){
                        xr = points[2*segi].x();
                        double k2 = (double)(points[2*segj+1].y()-points[2*segj].y())
                            /(double)(points[2*segj+1].x()-points[2*segj].x());
                        yr = points[2*segj].y()+k2*(xr-points[2*segj].x());
                    }else{
                        xr = points[2*segj].x();
                        double k1 = (double)(points[2*segi+1].y()-points[2*segi].y())
                            /(double)(points[2*segi+1].x()-points[2*segi].x());
                        yr = points[2*segi].y()+k1*(xr-points[2*segi].x());
                    }
                }else{
                    double k1 = (double)(points[2*segi+1].y()-points[2*segi].y())
                        /(double)(points[2*segi+1].x()-points[2*segi].x());
                    double k2 = (double)(points[2*segj+1].y()-points[2*segj].y())
                        /(double)(points[2*segj+1].x()-points[2*segj].x());
                    xr = k1*points[2*segi].x()-k2*points[2*segj].x() ;
                    xr += points[2*segj].y()-points[2*segi].y();
                    xr /= (k1-k2);
                    yr = points[2*segi].y()+k1*(xr-points[2*segi].x());
                    yr1 = points[2*segj].y()+k2*(xr-points[2*segj].x());
                    assert(fabs(yr-yr1) <1e-9);
                    ++sum;
                }
                //++cnt;
                intersec_set.insert(pair<double, double>(xr, yr));
            }
        }
    printf("%zu\n", intersec_set.size());
    //printf("%d\n", cnt);
}
