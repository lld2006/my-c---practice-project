#include <cstdio>
#include <cassert>
#include <vector>
#include <cmath>
#include <tr1/unordered_set>
#include "../lib/typedef.h"
using namespace std;
vector<double> vsin;
vector<double> vcos;
typedef std::tr1::unordered_set<u64> hashset;
hashset vset;
double pi = 3.1415926535897932384;
double mysin( int i)
{
    assert(i>0 && i < 180);
    if( i > 90 ) 
        i = 180 - i;
    return vsin[i-1];
}
double mycos(int i)
{
    assert( i > 0 && i<= static_cast<int>(vcos.size()));
    return vcos[179-i];
}
int find_angle(double value) //based on the sin value
{
    int start= 0;
    int last = 89;
    int mid = 0;
    if(value <vsin[0]){
        if(fabs(value - vsin[0]) < 1e-10)
            return 1;
        else
            return -1;
    }
    assert(value >= vsin[0] && value <= vsin.back());
    while(last - start > 1){
        mid = (start + last)/2;
        if(vsin[mid] < value)
            start = mid;
        else if (vsin[mid] > value)
            last = mid; 
        else{
            assert(fabs(value - vsin[mid]) < 1e-10);
            return mid + 1;
        }
    }
    assert(start +1 == last);
    if(fabs(vsin[start] - value) < 1e-10)
       return start+1; 
    else if(fabs(vsin[last] -value) < 1e-10)
        return last + 1;
    else 
        return -1;
}
void process_value(const vector<int>& angles)
{
    u64 sum = 0;
    if(angles[4]==0 || angles[5]==0 || angles[6]==0||angles[7]==0) return;
    if(angles[4]+angles[5] >= 180) return ;//convexity check
    if(angles[6]+angles[7] >= 180) return ;
    for(int shift = 0; shift < 8; shift += 2){
        sum = 0;
        for(unsigned int i = 0; i< angles.size(); ++i){
            int ni = (shift + i)%8;
            assert(angles[ni] > 0 && angles[ni] < 180);
            sum <<= 8;
            sum += angles[ni];
        }
        if(vset.find(sum) != vset.end()) return;
    }
    vset.insert(sum);    
}
int main()
{
    vsin.resize(90, 0);
    vcos.resize(179, 0);
    for(unsigned int i = 0; i < 90; ++i){
        vsin[i] = sin(static_cast<double>(i+1)*pi/180); // angle from 1-->90
    }
    for(unsigned int i = 0; i < 179; ++i){
        vcos[i] = cos(static_cast<double>(179-i)*pi/180); //i=0 178 angle179-->1
    }
    for(int a1 = 1 ; a1 < 90; ++a1){
        for(int a2 = 1; a2 <= 90-a1; ++a2){
            for(int a3=1; a3<180-a1-a2; ++a3){
                for(int a4 = 1; a4<180-a2-a3; ++a4){
                    double bd = mysin(a1+a2)/mysin(a1+a2+a3);
                    double bc = mysin(a2)/mysin(a2+a3+a4);
                    double cd = sqrt(bc*bc+bd*bd-2*bc*bd*mycos(a4));
                    double sina7 = bc*mysin(a4)/cd;
                    int a7 = find_angle(sina7);
                    if(a7 == -1) continue;
                    if(bd*bd+cd*cd < bc*bc)
                        a7= 180-a7;
                    int a8 = 180-a1-a2-a3;
                    assert(a8 > 0);
                    vector<int> angles;
                    angles.resize(8);
                    angles[0] = a1;
                    angles[1] = a2;
                    angles[2] = a3;
                    angles[3] = a4;
                    angles[4] = 180-a2-a3-a4;
                    angles[7] = 180 - a1 -a2 -a3;
                    angles[6] = a7;
                    angles[5] = 180 - angles[4] - a4 - a7;
                    process_value(angles);
                }
            }
        }
    }
    printf("%d\n", static_cast<int>(vset.size()));
}
