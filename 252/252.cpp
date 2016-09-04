#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>
#include "../lib/typedef.h"
using namespace std;

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

point gp(-1, 0, 0);
int gid = 0;
int idmax = 10000000;
struct point;
vector<point> vpoints;

// First version 
// First start with a point which has the minimum y in all points in the rectangle
// (point as lower left and 1000-1000 as upper right)
// in the convex if two points has the same ymin, then the rest of the 
// points has larger x coordinate a second point is still needed to setup 
// a triangle. I will use the points which has the maximum ctan value,  
// the rest qualified points has smaller ctan value.  when a new point 
// is picked, it should has a larger angle  
//
// Second version
// it is found that this version is too slow! It is clear that if the first point is determined
// there are 499 choices left as the second point, and probably 498 left as the third, the total
// is huge, maybe 500! It is impossible to find the result.
// The thing is, my restriction is too weak and did not consider the "hole"

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

//find all candidates when the ll corner point is determined
void sieve_all_qualified_points(int id, vector<int>& vq)
{
    vq.push_back(id);
    for(unsigned int j = 0; j < vpoints.size(); ++j ){
        if(vpoints[j].y() < vpoints[id].y()) continue;
        if((vpoints[j].y() ==  vpoints[id].y() && vpoints[j].x() > vpoints[id].x() ) ||
            vpoints[j].y() > vpoints[id].y())
            vq.push_back(j);
    }
}

class angleLess{
    public:
    bool operator()(const int& ip1, const int& ip2)
    {
       int p1y = vpoints[ip1].y() - gp.y(); 
       int p1x = vpoints[ip1].x() - gp.x();
       int p2y = vpoints[ip2].y() - gp.y(); 
       int p2x = vpoints[ip2].x() - gp.x();
       double c1, c2;
       if(p1y== 0){
           if(p1x > 0) 
               c1 = 1000000;
           else
               c1 = -1000000;
       }else{
           c1 = (double)p1x/p1y;
       }
       if(p2y == 0){
           if(p2x > 0) 
               c2 = 1000000;
           else
               c2 = -1000000;

       }else{
           c2 = (double)p2x/p2y;
       }
       if(c1==c2)
           return fabs(p1x) < fabs(p2x);
       return c1 > c2;
    }
};

// all points are sorted based on the angle
void sort_base_i(vector<int>& vqual, int id)
{
    gp = vpoints[id]; // let me use a global variable to sort all points based on angles
    sort(vqual.begin()+1, vqual.end(), angleLess());
}

int triangleArea(int i, int j, int k)
{
    int x1 = vpoints[i].x();
    int y1 = vpoints[i].y();
    int x2 = vpoints[j].x();
    int y2 = vpoints[j].y();
    int x3 = vpoints[k].x();
    int y3 = vpoints[k].y();
    int area = x1*(y2-y3) + x2*(y3-y1)+x3*(y1-y2);
    return area;
}

bool isRightTurn(int i, int j, int k)
{
    int x1 = vpoints[i].x();
    int y1 = vpoints[i].y();
    int x2 = vpoints[j].x();
    int y2 = vpoints[j].y();
    int x3 = vpoints[k].x();
    int y3 = vpoints[k].y();
    
    int v1x = x2 -x1;
    int v1y = y2 -y1;
    int v2x = x3 -x2; 
    int v2y = y3 -y2;
    int cross = v1x * v2y - v1y *v2x;
    return (cross < 0);
}

//cIndex is index in vqual
//area is current area with all points so far
int convexHole(int startIndex, int cIndex, int area, vector<int>& vqual,const vector<int>& vIndices)
{
    if(cIndex == (int)vqual.size()){
        return area;
    }
    //now handle cIndex
    int max = 0;
    for(int index = cIndex; index < (int)vqual.size(); ++index){
    //for(int index = cIndex; index < cIndex+1; ++index){
       assert((startIndex != index) && (vqual[index]!=vqual[startIndex]));
       assert(vIndices.size()>= 2);
       int current = vIndices.back();
       int prev = vIndices[vIndices.size()-2];
       //restriction
       if(isRightTurn(prev, current, vqual[index])) continue;
       //I was distracted by the right turn part
       int ta = triangleArea(vqual[0], current, vqual[index]); 
       vector<int> vnew(vIndices);
       if(ta > 0){
           vnew.push_back(vqual[index]);
           int tmax =  convexHole(startIndex, index+1, area+ta, vqual, vnew);
           if(tmax > max) max = tmax;
       }else{
            assert(ta == 0);
            int ta1 = convexHole(startIndex, index+1, area, vqual, vnew);
            vnew.back() = vqual[index];
            int ta2 = convexHole(startIndex, index+1, area, vqual, vnew);
            int tmax = (ta1 > ta2? ta1:ta2);
            if(tmax > max) max = tmax;
       }
       
    }
    return max;
}

int dynamic_search_convex(int pc, vector<int>&vqual)
{
   int max = 0;
   vector<int> vIndices;
   for (unsigned int j = 1; j < vqual.size(); ++j){
      vIndices.clear();
      vIndices.push_back(vqual[0]);
      vIndices.push_back(vqual[j]);
      int area = convexHole(j, j+1, 0, vqual, vIndices); 
      if(area > max){ 
          max = area;
      }
   }
   return max;
}
int find_max_convex_from_minyx(int selected)
{
    vector<int> vqual;
    sieve_all_qualified_points(selected, vqual);
    //not enough points
    if(vqual.size()<=2) return 0;
    sort_base_i(vqual, selected);
    //now all qualified points are sorted by angles, so now start with a
    //point j and search all convex i-j-...
    int va1 = dynamic_search_convex(selected, vqual);
    return va1;
}

int main()
{
    int target = 500;
    //target = 20;
    //create 500 points in vector vpoints
    create_points(target, vpoints);
    FILE* fp = fopen("dots.txt", "w");
    for(unsigned int i = 0 ; i< vpoints.size(); ++i){
        fprintf(fp, "%d %d\n", vpoints[i].x(), vpoints[i].y());
    }
    fclose(fp);
    int val = 0;
    for(unsigned int i = 0; i < vpoints.size(); ++i){
        
        int valx = find_max_convex_from_minyx(i);
        if(valx > val) {
            val = valx;
            printf("index %d area %d\n", i, val);
        }
        printf("%d %f\n",i, val/2.0);
    }
    printf("%f\n",val/2.0);
}
bool debug(const vector<int>& vIndices)
{
    if(vIndices.size() == 2 && vIndices[0]==396 && vIndices[1]== 72) return true; 
    if(vIndices.size() == 3 && vIndices[0]==396 && vIndices[1]== 72 && vIndices[2] == 142) return true; 
    if(vIndices.size() == 4 && vIndices[0]==396 && vIndices[1]== 72 && vIndices[2] == 142 && vIndices[3]==112) return true; 
    if(vIndices.size() == 5 && vIndices[0]==396 && vIndices[1]== 72 && vIndices[2] == 142 && vIndices[3]==112 && vIndices[4]==135) return true; 
    return false;
}

