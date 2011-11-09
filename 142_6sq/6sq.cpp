#include <set>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cassert>
using namespace std;
void intersection(set<int>& s1, set<int>& s2, set<int>& s){
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(s, s.end()));
}
int main(){
    vector<set<int> > allsquares;
    int limit = 300;
    int l2 = limit*limit;    
    allsquares.resize(l2+1);

    for(int a = 1; a<=limit; ++a){
        for(int b = a+1; b<=limit; ++b){
            int xp = b*b-a*a;
            int xr = 2*a*b;
            int min = xr<xp?xr:xp;
            int max = xr+xp -min;
            if(max > l2) continue;
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
    for(int i = 1; i<= limit; ++i){
        if(allsquares[i].empty()) continue;
        int xa = i;
        for(set<int>::iterator iter = allsquares[xa].begin(); iter!=allsquares[xa].end(); ++iter){
            int xb = *iter;
            int xc2 = xa*xa +xb*xb;
            int xc = sqrt(xc2);
            if(xc * xc != xc2) ++xc;
            assert(xc *xc == xc2);//xc is q 
            set<int> qa;
            intersection(allsquares[xc], allsquares[xb], qa);
            if(!qa.empty()){
                for(set<int>::iterator iter = qa.begin(); iter!=qa.end(); ++iter){
                    int xw = *iter;
                    int xv2 = xw*xw+ + xb*xb;
                    int xv = sqrt(xv2);
                    if(xv * xv != xv2) 
                        ++xv;
                    assert(xv * xv == xv2);
                    int xu2 = xw * xw + xc*xc;
                    int xu = sqrt(xu2);
                    if(xu * xu != xu2)
                        ++xu;
                    assert(xu *xu == xu2);
                    if(xu * xu - xv *xv== xa * xa){
                        printf("%d %d %d %d %d %d\n", xa, xb, xc, xu, xv, xw);
                        printf("%f %f %f %f\n", (double)(xu*xu+xv*xv-xw*xw)/2, 
                                (double)(xu*xu-xv*xv+xw*xw)/2,(double)(-xu*xu+xv*xv+xw*xw)/2,
                                (double)(xu*xu+xv*xv+xw*xw)/2);
                    }
                }
            }
            qa.clear();
            intersection(allsquares[xc], allsquares[xa], qa);
            if(!qa.empty()){
                for(set<int>::iterator iter = qa.begin(); iter!=qa.end(); ++iter){
                    int xw = *iter;
                    int xv2 = xw*xw+ + xa*xa;
                    int xv = sqrt(xv2);
                    if(xv * xv != xv2) 
                        ++xv;
                    assert(xv * xv == xv2);
                    int xu2 = xw * xw + xc*xc;
                    int xu = sqrt(xu2);
                    if(xu * xu != xu2)
                        ++xu;
                    assert(xu *xu == xu2);
                    if(xu * xu - xv *xv== xb * xb) {
                        printf("b %d %d %d %d %d %d\n", xa, xb, xc, xu, xv, xw);
                        printf("%f %f %f %f\n", (double)(xu*xu+xv*xv-xw*xw)/2, 
                                (double)(xu*xu-xv*xv+xw*xw)/2,(double)(-xu*xu+xv*xv+xw*xw)/2,
                                (double)(xu*xu+xv*xv+xw*xw)/2);
                    }
                }
            }
        }
    }
}
