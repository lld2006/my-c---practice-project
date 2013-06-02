#include <set>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/tools.h"
//first from x-y=m^2 y-z=n^2 x-z=p^2, p^2=m^2+n^2 
//let me define x+y=q^2 x+z=r^2 y+z=s^2 where q>r>s
//then x-y+ y+z = x+z which means m^2+ s^2 = r^2
// x-z+y+z = x+y, which means p^2 + s^2 = q^2
// y-z+x+z = x+y, which means n^2+r^2=q^2
using namespace std;
void intersection(set<int>& s1, set<int>& s2, set<int>& s){
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(s, s.end()));
}
int main(){
    i64 min = 1000000000LL;
    vector<set<int>> allsquares;
    int limit = 83;
    int l2 = limit*limit;    
    allsquares.resize(l2+1);

    for(int a = 1; a<=limit; ++a){
        int incb = 1;
        if(a % 2 ==0) incb = 2;
        for(int b = a+1; b<=limit; b+=incb){
            if(gcd(a, b) > 1) continue;
            int xp = b*b-a*a;
            int xr = 2*a*b;
            int max = b*b+a*a;
            if(max > l2) continue; //limit2 not 12
            int count = 0;
            while (true){
               ++count;
               allsquares[xr*count].insert(xp*count); 
               allsquares[xp*count].insert(xr*count);
               if(max *(count+1) > l2) break;
            }
        }
    }
    //now test part
    for(int i = 1; i<= l2; ++i){
        if(allsquares[i].empty()) continue;
        i64 xa = i; //n
        for(set<int>::iterator iter = allsquares[xa].begin(); iter!=allsquares[xa].end(); ++iter){
            i64 xb = *iter; //m
            i64 xc2 = (i64)xa*xa +(i64)xb*xb;
            i64 xc = sqrt(xc2); //p
            assert((i64)xc *xc == xc2);
            set<int> qa;
            intersection(allsquares[xc], allsquares[xb], qa);
            if(!qa.empty()){
                for(set<int>::iterator iter = qa.begin(); iter!=qa.end(); ++iter){
                    i64 xw = *iter; // s
                    i64 xv2 = xw*xw+ + xb*xb; 
                    i64 xv = sqrt(xv2); //r
                    assert(xv * xv == xv2);
                    i64 xu2 = xw * xw + xc*xc;
                    i64 xu = sqrt(xu2); //q
                    assert(xu > xv && xv > xw);
                    assert(xu *xu == xu2);
                    if((xv*xv+xw*xw > xu*xu) && xu * xu - xv *xv== xa * xa){
                        i64 sum = xu*xu+xv*xv+xw*xw;
                        if((sum % 2) == 0 && sum/2 < min){
                            sum /= 2;
                            min = sum;
                            printf("%lld %lld %lld %lld %lld %lld\n", xa, xb, xc, xu, xv, xw);
                            printf("a %lld %lld %lld %lld\n", sum-xu*xu, sum-xv*xv, sum-xw*xw, sum);
                        }
                    }
                }
            }
        }
    }
}
