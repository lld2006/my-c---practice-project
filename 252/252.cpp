#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int gid = 0;
int idmax = 10000000;

struct point
{
    point(int tid, int tx, int ty):id(tid), d_x(tx), d_y(ty)
    { }
    int x() const {return d_x;}
    int y() const {return d_y;}
    int id;
    int d_x;
    int d_y;
};

int cross_product(const point& p1, const point& p2)
{
    return p1.x()*p2.y()-p1.y()*p2.x();
}
int direction(const point& pi, const point& pj, const point& pk)
{
    return cross_product(point(idmax, pk.x()-pi.x(), pk.y()-pi.y()), point(idmax, pj.x()-pi.x(), pj.y()-pi.y()));
}
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

class polarless{
    //we can use atan2 to test if this class's validity
  public:
    bool operator() (const point& p1, const point& p2)
    {
        assert(p1.x() != 0 || p1.y() != 0);
        assert(p2.x() != 0 || p1.y() != 0);

        point xp(idmax, 1, 0);//negative x direction
        int cp1 = cross_product(xp, p1);
        int cp2 = cross_product(xp, p2);
        if(cp1 == 0 || cp2 ==0){
            assert(p1.x() != 0 && p2.x() != 0);
            if(cp1 == 0 && cp2 == 0){
                int a1 = (p1.x() < 0);
                int a2 = (p2.x() < 0);
                return a1 < a2;
            }else if(cp1 == 0){
                if(p1.x() > 0) //angle zero for p1
                    return true;
                else//angle pi for p1 
                    return (cp2 < 0);
            }else{ //cp2 == 0
                if(p2.x()==0)
                    return true;
                else //angle pi for p2
                    return (cp1 > 0);
            }   
        }else{
            if(cp1 > 0 && cp2 < 0) 
                return true;
            else if(cp1 < 0 && cp2 > 0)
                return false;
            else{
                int cp12 = cross_product(p1, p2);
                return (cp12 > 0);
            }
        }
    }
};
void create_points(int target, vector<point>& vpoints)
{
    vector<int> vxy;
    i64 s0 = 290797;
    int cnt = 0;
    while(cnt < target*2){
        s0 *= s0;
        s0 %= 50515093;
        vxy.push_back((s0%2000)-1000);
        ++cnt;
    }
    assert(static_cast<int>(vxy.size()) == 2*target);
    for(unsigned int i = 0; i < vxy.size(); i+=2){
        vpoints.push_back(point(gid++, vxy[i], vxy[i+1]));
    }
}
void sort_point_polar(int ith, vector<vector<int>>& vpolar, const vector<point>& vpoints)
{
    vector<point> vp(vpoints);
    swap(vp[ith], vp.back());
    vp.pop_back();
    int xi = vpoints[ith].x();
    int yi = vpoints[ith].y();
    for(unsigned int i = 0; i < vp.size(); ++i){
        vp[i].d_x -= xi;
        vp[i].d_y -= yi;
    }
    sort(vp.begin(), vp.end(), polarless());
    vector<int> vindices;
    vindices.reserve(vpoints.size());
    for(unsigned int i = 0; i < vp.size(); ++i){
        vindices.push_back(vp[i].id);
    }
    swap(vindices, vpolar[ith]);
}
int main()
{
    int target = 20;
    vector<point> vpoints;
    create_points(target, vpoints);
    vector<vector<int>> vpolar;
    vpolar.resize(500); 
    for(unsigned int i = 0; i < vpolar.size(); ++i){
        sort_point_polar(i, vpolar, vpoints);
    }
}
