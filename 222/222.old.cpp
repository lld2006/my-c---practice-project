#include "../lib/tools.h"
#include <cassert>
#include <cstdio>
#include <algorithm>
int dim = 21;
double check_min(int s, int d, vector<double>& hsphere){
    //assert(s < d && s >= 0 && d < dim);
    double thmin = 60+s+d;
    int jmin, jmax;
    if(s == 0 || d == 0){
        jmin = 1;
        if(s == 1 || d == 1)
            jmin =2;
    }else{
        jmin = 0;
    }
    if(s == dim -1 || d == dim - 1){
        jmax = dim - 2;
        if(s == dim -2 || d == dim - 2)
            jmax = dim - 3;
    }else{
        jmax = dim - 1;
    }
    assert(s != jmin && d != jmax && s != jmax && d != jmin);
    thmin +=  hsphere[index0(dim, s, jmin)] + hsphere[index0(dim, d, jmax)];
    int xd = 0;
    for(int xs = 0; xs < dim - 1; xs++){
        if(xs == s || xs == d) continue;
        xd = xs +1;
        while (xd == s || xd ==d){
            ++xd;
        }
        if(xd > dim - 1) continue;
        thmin += hsphere[index0(dim, xs, xd)];
    }
    return thmin;
}
double check_perm_sum(const vector<int>& pvec, const vector<double>& hsphere)
{
    double sum = 60+pvec[0]+pvec.back();
    for(int i = 0; i < static_cast<int>(pvec.size())-1; ++i)
        sum += hsphere[index0(dim, pvec[i], pvec[i+1])];
    return sum;
}
int main()
{
    //0 is 30.... and 20 ---> 50
    //so I need a vector of 21 choose 2 == 210
    vector<double> hsphere;
    hsphere.resize(dim*dim, 0);
    for(int i = 0; i < dim; ++i){
        for(int j = i+1; j < dim; ++j){
            hsphere[index0(dim, i, j)] = 10*sqrt(static_cast<double>(2)*(i+j)+20);
            hsphere[index0(dim, j, i)] = hsphere[index0(dim, i,j)];
        }
    }
    if(true){
        assert(dim%2 ==1);
        double gsum = 60+dim-2+dim-1+hsphere[index0(dim, 0, 1)]; 
        for(int i = dim -2; i > 1; i-=2){
            gsum += hsphere[index0(dim, i, i -2)];
        }
        for(int i = 0; i < dim-2; i+=2){
            gsum += hsphere[index0(dim, i, i+2)];
        }
        int res = gsum*1e3+0.5;
        printf("%d\n", res);
        exit(1);
    }
    if(false){
        double pmin = 1e9;
        //do a permutation check
        vector<int> vperm;
        vperm.resize(dim, 0);
        for(int i = 0; i < dim; ++i){
            vperm[i] = i;
        }
        do{
            double tmin = check_perm_sum(vperm, hsphere);
            if(tmin < pmin){
                pmin = tmin;
                printf("%20.10f\n", pmin);
                for(unsigned int i = 0;  i<vperm.size(); ++i)
                    printf("%d ", vperm[i]);
                printf("\n");
            }
        }while(next_permutation(vperm.begin(), vperm.end()));
        exit(1);
    }
    double hmin = 1e9;
    for( int source = 0; source < dim; ++source)
        for(int drain = 0; drain < dim; ++drain){
            if(source == drain) continue;
            double tmin = check_min(source, drain, hsphere );
            if(tmin < hmin) {
                hmin = tmin;
                printf("%d %d %20.10f\n", source, drain, tmin);
            }
        }
    int imin = hmin*1e6+0.5;
    printf("%d %20.10f\n", imin, hmin);
}
