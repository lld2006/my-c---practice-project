#include <cmath>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstdlib>
using namespace std;
//lesson1, be careful about assignment, sometimes some of the operation in the loop will
//modify the value in the array, if that is the case, we need to use += instead of =;
//lesson2, when we have an if clause, be careful what we need to do in the clause, it is true
//that we need to do some of the special operations in side the clause, but some general 
//operations(which should be applied to all) should not be put inside the clause.

void poly_mult(const vector<long double>& v1, const vector<long double>& v2, vector<long double>& vr){
    unsigned int size1 = v1.size();
    unsigned int size2 = v2.size();
    vr.clear();
    vr.resize(size1+size2, 0);
    for(unsigned int i = 0; i < size1; ++i)
        for(unsigned int j = 0; j < size2; ++j){
            vr[i+j] += v1[i]*v2[j];
        }
    int i = vr.size()-1;
    while(vr[i]==0){
        vr.pop_back();
        --i;
    }
    return;
}

long double polyfun(const vector<long double>& vp, long double base){
    long double sum = 0;
    for(unsigned int i = 0; i < vp.size(); ++i){
        if(vp[i] != 0)
            sum += vp[i] * pow(base, i);
    }
    return sum;
}
    
int main(){
    //for each z^i, we have a series of q
    vector<vector<long double> > vgen, vcp; 
    vector<vector<long double> > vpoly;                            
    vgen.resize(51);
    vgen[0].push_back(1);
    //multiply to get gen function
    for(int i = 1; i <=50; ++i){
        vpoly.clear();
        vpoly.resize(2);
        vpoly[0].push_back(0);// q^0, z 0th power term
        vpoly[0].push_back((long double)i/50); //q^1 z^0 term 
        vpoly[1].push_back(1); //q^0  z^1 term
        vpoly[1].push_back(-(long double)i/50); //q^1 z^1 term
        vcp = vgen;
        vgen.clear();
        vgen.resize(vcp.size());
        for(int j = 0; j <= 50; ++j){ //consider at most z^20 
            vector<long double> vtr;
            if(!vcp[j].empty()){
                poly_mult(vcp[j], vpoly[0], vtr);
                if(vgen[j].empty()|| vgen[j].size()< vtr.size()){
                    vgen[j].resize(vtr.size(), 0);
                }
                for(unsigned int k = 0; k < vtr.size(); ++k )
                    vgen[j][k] += vtr[k];
                if( 1||j <=19){
                    poly_mult(vcp[j], vpoly[1], vtr);
                    if(vgen[j+1].empty()||vgen[j+1].size() < vtr.size())
                        vgen[j+1].resize(vtr.size(), 0);
                    for(unsigned int k = 0; k < vtr.size(); ++k )
                        vgen[j+1][k] += vtr[k];
                }
            }
        }
    //debug code
    //long double b = 1;
    //for(unsigned int ix = 0; ix<= 50; ++ix){
    //    long double psc = polyfun(vgen[ix], b);
    //    printf("%d %20.15Lf\n", ix, psc);
    //}
    }
    vector<long double>& v20=vgen[20];
    long double xl = 0, xh = 1, xmid=0;
    long double fl, fh, fmid;
    long double prob = 0.02;
    while(fabs(xh-xl) > 1e-12){
        xmid = (xl+xh)/2.0;
        fl = polyfun(v20, xl)-prob;
        fh = polyfun(v20, xh)-prob;
        assert(fl + prob >=0 && fl+prob <=1);
        assert(fh + prob >=0 && fh+prob <=1);
        if(!((fl >=0 && fh<=0)|| (fl<=0 &&fh>=0)))
            printf("%20.15Lf %20.15Lf\n", fl, fh);
        assert((fl >=0 && fh<=0)|| (fl<=0 &&fh>=0));
        fmid = polyfun(v20, xmid)-prob;
        if((fl >=0 && fmid >=0) || (fl<=0 && fmid <=0))
            xl = xmid;
        else
            xh = xmid;
        printf("%20.15Lf %20.15Lf\n", xl, xh);
    }
    printf("%30.20Lf\n", (long double)50/xl);
}
