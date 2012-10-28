#include <cstdio>
#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cassert>
int sumdig(i64 number)
{
    int sum = 0; 
    while(number > 0){
        int residue = number % 10;
        sum += residue;
        number /= 10;
    }
    return sum;
}
void debug(vector<i64>& vi, int level)
{
    i64 cnt = 0;
    for(unsigned int i = 0; i <vi.size(); ++i){
        cnt += vi[i];
    }
    i64 prod = 1;
    for( int i = 1; i <=level; ++i){
        prod *= 10;
    }
    assert(prod == cnt);
}
int main()
{
    vector<vector<i64> > vdiff;
    vdiff.resize(19);
    for(unsigned int i = 0; i < vdiff.size(); ++i){
    //18 levels considered, the first level from 0 to 9
    //and the subsequent level has 2.....18 digits
    //to be safe, for m digits number, 137 n may have m+3
    //digits; so the difference can be -9*m to 9(m+3)
    //so the vector size is 9*(2m+3)+1, and the number is
    //from 0 to 999
        vdiff[i].resize((18*i+28)*1000, 0);
    }
    //now initialize the first level
    for(unsigned int i = 0; i <10; ++i){
        unsigned int prod = i * 137;
        unsigned int sum1 = i;
        unsigned int sum2 = sumdig(prod);
        int diff = sum2 -sum1+9;
        int n3 = prod/10;
        ++vdiff[1][index0(1000, diff, n3)];
    }
    debug(vdiff[1], 1);
    //based on level 1, go through level 2 to 18;
    for(unsigned int level = 2; level<=18; ++level){
        vector<i64>& v1= vdiff[level-1];
        vector<i64>& v2= vdiff[level];
        int ndiff = (2*level+1)*9+1;
        for(int num = 0; num < 1000; ++num){
            for(int diff = 0; diff < ndiff; ++diff){
                i64 oldcnt = v1[index0(1000,diff, num)];
                if(oldcnt == 0)
                    continue;
                assert(level!=2 || oldcnt == 1);
                //now need to be expanded;
                for(unsigned int i = 0; i <= 9; ++i){
                   int oldsum = sumdig(num); 
                   int np = num + 137*i;
                   int newsum = sumdig(np);
                   int newdiff = diff+9 +newsum-oldsum-i;
                   int newnum = np/10;
                   assert(newdiff >= 0 && newdiff <= ndiff+18);
                   assert(newnum >= 0 && newnum < 1000);
                   v2[index0(1000, newdiff, newnum)] += oldcnt;
                }
            }
        }
        debug(v2, level);
    }
    i64 sum = 0;
    vector<i64>& vf=vdiff[18];
    for(int num = 0; num < 1000; ++num){
        sum += vf[index0(1000, 162,num)];//162 ==> 0
    }
    printf("%lld\n", sum);
}
