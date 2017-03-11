#include <cstdio>
#include <cassert>
#include <vector>
#include <numeric>
using namespace std;
void update_pvec(vector<double>& vp){
    vector<double> nvp;
    nvp.resize(900, 0);
    for(unsigned int i = 0; i<30; ++i){
        for(unsigned int j =0; j<30; ++j){
            int nb = 4;
            int np = i*30+j;
            if(i %30 == 0 || (i+1)%30 ==0) --nb;
            if(j %30 == 0 || (j+1)%30 ==0) --nb;
            double pi = vp[i*30+j];
            if(pi == 0.0) continue;
            pi/=nb;
            int nrow = i - 1;
            if(nrow >=0) nvp[np-30] += pi;
            nrow = i+1;
            if(nrow <30) nvp[np+30] += pi;
            int ncol = j-1;
            if(ncol >= 0) nvp[np-1] += pi;
            ncol = j+1;
            if(ncol < 30) nvp[np+1] += pi;
        }
    }
    nvp.swap(vp);
}
int main()
{
    vector<double> vp, totalp;
    totalp.resize(900, 1.0);
    for(unsigned int row = 0; row < 15; ++row){
        for(unsigned int col = 0; col < 15; ++ col){
            vp.clear();
            vp.resize(900, 0.0);
            vp[row*30+col]=1.0;
            for(unsigned int i = 0; i < 50; ++i){
                update_pvec(vp);
            }
            //double val = accumulate(vp.begin(), vp.end(), 0.0);
            //printf("%d %20.10f\n",row*30+col, val );
            for(unsigned int i = 0; i < 30; ++i){
                for(unsigned int j = 0; j < 30; ++j){
                    int nx = 30*i+j;
                    int ny = 870-30*i+j;
                    int nz = 30*i+29-j;
                    totalp[nx] *= (1.0-vp[nx]);
                    totalp[nx] *= (1.0-vp[899-nx]);
                    totalp[nx] *= (1.0-vp[ny]);
                    totalp[nx] *= (1.0-vp[nz]);
                    assert(totalp[i]>0);
                }
            }
        }
    }
    double val = accumulate(totalp.begin(), totalp.end(), 0.0);
    printf("%20.10f\n", val);
}
