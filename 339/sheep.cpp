#include <vector>
#include <cstdio>
#include <cassert>
#include "../lib/tools.h"
using namespace std;
void gauss_elimination(int n, vector<double>& a)
{
    assert(static_cast<int>(a.size()) == n * n);
    for(int i = 0; i < n; ++i){
        double diag = a[index0(n, i, i)];
        for(int j = i+1; j < n; ++j){
            //first find the aji/aii
            if(a[index0(n, j, i)]!=0)
                a[index0(n, j, i)] /= diag;
            //update jth row
            for(int k = i+1; k<n; ++k){
                a[index0(n, j, k)] -= a[index0(n, j, i)] * a[index0(n,i,k)];
            }
        }
    }
}
void LU(vector<double>& a, vector<double>& rhs, vector<double>& sol)
{
    int nsize = rhs.size();
    sol.clear();
    sol.resize(nsize, 0);
    //forward
    assert(static_cast<int>(a.size()) == nsize * nsize);
    vector<double> y(rhs);
    //diagonal belongs to upper triangle matirx
    for(int i = 0 ; i < nsize; ++i){
        for(int j = 0; j < i; ++j){
            y[i]-= a[index0(nsize, i,j)] * y[j];
        }
    }
    //backward
    for(int i = nsize -1 ; i>=0; --i){
        for(int j = nsize - 1; j > i; --j){
            y[i] -= a[index0(nsize, i, j)] * sol[j];
        }
        sol[i] = y[i]/a[index0(nsize, i, i)];
    }
}
void debugMat(vector<double>& mat, int nsize)
{
    for( int i = 0; i < nsize; ++i){
        for( int j = 0; j < nsize; ++j){
            printf("%d %d %f\n",i,j, mat[index0(nsize,i,j)]);
        }
    }
}
int main()
{
    int limit = 10000;
    //limit = 5;
    vector<vector<double>> vn;
    //the first dimension is black and second for white;
    vn.resize(2*limit+1);
    for(unsigned int i = 1; i<vn.size(); ++i){
        vn[i].resize(i+1,0.0);
    }
    vector<double> vnmax;//for each column v(i, j) j=1,...,i the max
    vnmax.resize(2*limit+1, 0.0);
    vn[1][1]=1.0;
    vn[2][1]=7.0/3.0;
    vn[2][2]=7.0/3.0;
    vn[3][1] = 43./12.;//these simple cases(not so simple though) are manually solved.
    vnmax[1] = 1.0;
    vnmax[2] = vn[2][1];
    vnmax[3] = vn[3][1];
    for( int t = 5; t<=2*limit; ++t){
        //if(t % 100 == 0)
        //printf("%d\n", t);
        int nstate = (t-1)/2;
        vector<double> mata,matb, matc, rhs, sol;
        matb.resize(nstate+1, 0.0);
        mata.resize(nstate+1, 0.0);
        matc.resize(nstate+1, 0.0);
        rhs.resize(nstate+1, 0.0);
        sol.resize(nstate+1, 0.0);
        matb[1] = t;
        rhs[1] = (t-1)*t;
        matc[1] = -1;
        for(int ns = 1; ns < nstate-1; ++ns){
            //state 0 is n-1, 1 state 2 is n-2:2 etc the first 
            //is always greater than the second;
            matb[ns+1] = t;
            mata[ns+1] = -(t-ns-1);
            matc[ns+1] = -(ns+1);
            rhs[ns+1] = 0;
        }
        matb[nstate] = t;
        mata[nstate] = -(t/2+1);
        rhs[nstate] = (t-1)/2*vnmax[t/2];
        vector<double> cp, dp;
        cp.resize(nstate+1,0.0);
        dp.resize(nstate+1,0.0);
        cp[1] = matc[1]/matb[1];
        for(int i = 2; i<= nstate-1; ++i){
            cp[i] = matc[i]/(matb[i]-cp[i-1]*mata[i]);
        }
        dp[1] = rhs[1]/matb[1];
        for(int i = 2; i <= nstate; ++i){
            dp[i] = (rhs[i]-dp[i-1]*mata[i])/(matb[i]-cp[i-1]*mata[i]);
        }
        sol[nstate] = dp[nstate];
        for(int i = nstate-1; i>=1; --i){
            sol[i] = dp[i] - cp[i]*sol[i+1];
        }
        //debugMat(mat, nstate);
        //gauss_elimination(nstate, mat);
        //LU(mat, rhs, sol);
        for(unsigned int i = 1; i < sol.size(); ++i){
            vn[t-i][i] = sol[i];
            vnmax[t-i] = sol[i];
        }
    }
    printf("%20.10f\n", (vn[limit+1][limit-1]+vn[limit-1][limit-2])/2);
}
