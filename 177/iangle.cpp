#include <vector>
#include <cstdio>
#include <cassert>
#include <cmath>

double pi = 3.1415926535897;
double ltol = 1e-8;
using namespace std;
//now let me start from a different point of view
//start from the smaller diagonal, and angle 1 is the smallest angle of the 
//four
vector<double> vsin;
vector<double> vcos;

double mysin( int i)
{
    assert(i> 0 && i < 180);
    return vsin[i];
}

double mycos(int i)
{
    assert( i > 0 && i < 180);
    return vcos[i];
}

bool sideeq(double a, double b)
{
    if(fabs(a-b)<ltol) 
        return true;
    return false;
}
bool sideless(double a, double b)
{
    if(a > b + ltol) 
        return false;
    else if(sideeq(a,b)) 
        return false;
    return true;
}
int main()
{
    pi = atan(1.0)*4.0;
    vsin.resize(181, 0);
    vcos.resize(181, 0);
    for(unsigned int i = 0; i <= 180; ++i){
        vsin[i] = sin(static_cast<double>(i)*pi/180); // angle from 1-->90
        vcos[i] = cos(static_cast<double>(i)*pi/180); //i=0 178 angle179-->1
    }

    int total = 0;
    double AC = 1;
    for(int a1 = 1; a1 < 90; ++a1)
        for(int a2 = a1; a2 <= 178 -a1; ++a2)
        //for(int a2 = a1; a2 <= 89; ++a2)
            for(int a3 = a1; a3 <= 178 -a2; ++a3)
                for(int a4 = a1; a4 <= 178-a1; ++a4){
                    int D = 180 - a1 - a4;
                    int B = 180 - a2 - a3;
                    double DA = AC/mysin(D)*mysin(a4);
                    double AB = AC/mysin(B)*mysin(a3);
                    double BDx = DA*mycos(a1) - AB *mycos(a2);
                    double BDy = DA*mysin(a1) + AB*mysin(a2);
                    double BD = sqrt(BDx*BDx+BDy*BDy);
                    if(sideless(BD, AC)) continue;
                    bool deq = sideeq(AC, BD);
                    double cosADB = (DA*DA+BD*BD-AB*AB)/(2*DA*BD);
                    double dADB = acos(cosADB);
                    dADB *= 180/pi;
                    int ADB = round(dADB);
                    if(fabs(dADB-ADB) > 1e-10) 
                        continue;
                    int a5 = ADB;
                    int a6 = D - a5;
                    int a7 = 180 - a1 - a2 - a5;
                    int a8 = B - a7;
                    int minangle = a5;
                    if(deq){
                        if(a6 < minangle) minangle = a6;
                        if(a7 < minangle) minangle = a7;
                        if(a8 < minangle) minangle = a8;
                        if(minangle < a1) continue;
                    }

                    if(a5<=0||a6<=0||a7<=0||a8<=0)
                        continue;
                    if(a2==a1 && a3 > a4)
                        continue;
                    else if(a4==a1 && a2 > a3)
                        continue;
                    else if(a3 == a1 && a2 > a4)
                        continue;
                    if(a1==a3 && a2==a4)
                        assert(a5==a8 && a6 == a7);
                    if(a1==a2 && a3==a4) 
                        assert(a5==a7 && a6==a8);
                    //printf("%d %d %d %d %d %d %d %d\n", a1, a2, a7
                    //        ,a8, a3,a4, a6,a5);
                    ++total;
                }//loop a1 a2 a3 a4
    printf("%d\n", total);
}
