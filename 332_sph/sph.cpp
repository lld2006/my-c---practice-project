#include <cstdio>
#include <tuple>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;
double PI = 3.14;
typedef tuple<double, double,double> triplet;
void debug(triplet& t)
{
    printf("%f %f %f\n", get<0>(t), get<1>(t), get<2>(t));
}
void creat_triple_vec(int r, vector<triplet>& vt)
{
    vt.clear();
    int r2 = r*r;
    for(int i = -r; i<=r; ++i)
        for (int j = -r; j <= r; j++) {
            for (int k = -r; k <= r; k++) {
                if(i*i+j*j+k*k == r2)
                    vt.push_back(triplet(i,j,k));
            }
        }
}

triplet dir ( triplet& p1, triplet& p2)
{
    return triplet(get<0>(p2)-get<0>(p1), get<1>(p2)-get<1>(p1),get<2>(p2)-get<2>(p1));
}

//notice in this problem the norm of OA is r
double norm(triplet & p1){
    return sqrt(get<0>(p1)*get<0>(p1) + get<1>(p1)*get<1>(p1) +get<2>(p1)*get<2>(p1));
}

double cos2(triplet v1, triplet v2)
{
    double ox1 = get<0>(v1);
    double oy1 = get<1>(v1);
    double oz1 = get<2>(v1);
    double ox2 = get<0>(v2);
    double oy2 = get<1>(v2);
    double oz2 = get<2>(v2);
    return (ox1*ox2+oy1*oy2+oz1*oz2)/(norm(v1)*norm(v2));
}

triplet tangent(triplet& p1, triplet& p2) // at point p1
{
    triplet d12 = dir(p1, p2);
    double ca = cos2(d12, p1)/norm(p1)*norm(d12);
    return triplet(get<0>(d12)-ca*get<0>(p1), get<1>(d12)-ca*get<1>(p1), get<2>(d12)-ca*get<2>(p1));
}

double cosine (triplet p1, triplet p2,  triplet p3) //angle at 2;
{
    triplet v1 = tangent(p2, p1);
    triplet v2 = tangent(p2, p3);
    assert(norm(v1) > 0);
    assert(norm(v2) > 0);
    double ox1 = get<0>(v1);
    double oy1 = get<1>(v1);
    double oz1 = get<2>(v1);
    double ox2 = get<0>(v2);
    double oy2 = get<1>(v2);
    double oz2 = get<2>(v2);
    return (ox1*ox2+oy1*oy2+oz1*oz2)/(norm(v1)*norm(v2));
}


triplet ndir(triplet& p1, triplet& p2)
{
    double x = get<1>(p1)*get<2>(p2) - get<1>(p2)*get<2>(p1);
    double y = get<2>(p1)*get<0>(p2) - get<2>(p2)*get<0>(p1);
    double z = get<0>(p1)*get<1>(p2) - get<0>(p2)*get<1>(p1);
    return triplet(x, y, z);
}
double area (triplet& p1, triplet& p2, triplet& p3, double r)
{
    triplet t2 = tangent(p1, p2);
    triplet t3 = tangent(p1, p3);
    triplet t  = tangent(p2, p3);
    if(norm(t2)< 1e-8 || norm(t3) <1e-8 || norm(t) < 1e-8)
        return 0.0;
    else{
       double a1 =  acos(cosine(p2,p1,p3));
       double a2 =  acos(cosine(p1, p2, p3)); 
       double a3 =  acos(cosine(p1, p3, p2));
       double left =  (a1 +a2+a3-PI);
       if(left < 0){
           assert(left > -1e-8);
           left = -left;
       }
       assert(left >= 0 && left <= 2*PI);
       if(left < 1e-8) left =0.0;
       return left * r * r;
    }
}
double minarea(vector<triplet>& vt, int r)
{
    if(vt.size() <= 2) return 0;
    double amin = 1000000;
    for(unsigned int i = 0; i<vt.size()-2; ++i){
        if(get<0>(vt[i])< 0 || get<1>(vt[i]) <0 || get<2>(vt[i])< 0)
            continue;
        for(unsigned int j = i+1; j<vt.size()-1; ++j){
            for(unsigned int k = j+1; k<vt.size(); ++k){
                if(fabs(cos2(ndir(vt[i], vt[j]), vt[k]))<1e-8)
                    continue;
                double ta = area(vt[i], vt[j], vt[k], r);
                if(ta < 1e-8 ) continue;
                assert(ta > 1e-3);
                if(ta < amin)
                    amin = ta;
            }
        }
    }
    assert(amin < 1000000);
    return amin;
}
int main()
{
    PI = atan(1.0)*4;
    vector<triplet> vtrip;
    double total = 0;
    for(int r = 1; r<=50; ++r){
        creat_triple_vec(r, vtrip);
        double ta = minarea(vtrip, r);
        total += ta;
        printf("for r = %d points num = %zu area=%f \n", r, vtrip.size(), ta);
    }
    printf("%f\n", total);
}
