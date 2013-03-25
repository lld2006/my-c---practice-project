#include <cstdio>
#include <cassert>
#include <vector>
#include "../lib/tools.h"
using namespace std;
//lesson when I got a "0", this should makes us still in the same position. I missed this part
void gauss_elimination(int n, vector<double>& A)
{
    assert(static_cast<int>(A.size()) == n * n);
    for(int i = 0; i < n; ++i){
        double diag = A[index0(n, i, i)];
        for(int j = i+1; j < n; ++j){
            //first find the aji/aii
            if(A[index0(n, j, i)]!=0)
                A[index0(n, j, i)] /= diag;
            //update jth row
            for(int k = i+1; k<n; ++k){
                A[index0(n, j, k)] -= A[index0(n, j, i)] * A[index0(n,i,k)];
            }
        }
    }
}
void LU(vector<double>& A, vector<double>& rhs, vector<double>& sol)
{
    int nsize = rhs.size();
    sol.clear();
    sol.resize(nsize, 0);
    //forward
    assert(static_cast<int>(A.size()) == nsize * nsize);
    vector<double> y(rhs);
    //diagonal belongs to upper triangle matirx
    for(int i = 0 ; i < nsize; ++i){
        for(int j = 0; j < i; ++j){
            y[i]-= A[index0(nsize, i,j)] * y[j];
        }
    }
    //backward
    for(int i = nsize -1 ; i>=0; --i){
        for(int j = nsize - 1; j > i; --j){
            y[i] -= A[index0(nsize, i, j)] * sol[j];
        }
        sol[i] = y[i]/A[index0(nsize, i, i)];
    }
}


int main()
{
    int nmax = 1000;
    int shift = nmax/2;//shift
    vector<double> vmat, rhs, sol;
    vmat.resize(nmax*nmax, 0);
    rhs.resize(nmax, -1);
    //rhs = -1
    for(unsigned int m = 0; m < shift-1; ++m){
        vmat[index0(nmax, m, m)] =(double) (m+1) / nmax - 1;
        vmat[index0(nmax, m, m+1)] = (double) (nmax-2-2*m)/nmax;
        vmat[index0(nmax, m, m+shift)] = (double) 1/nmax;

        vmat[index0(nmax, m+shift, m+shift)] = (double) (m+1) /nmax-1; 
        vmat[index0(nmax, m+shift, m+shift+1)] = (double) (nmax-2-2*m)/nmax;
    }
    unsigned int m = shift-1;
    vmat[index0(nmax, m, m)] =(double) (m+1) / nmax- 1;
    vmat[index0(nmax, m, m+shift)] = (double) 1/nmax;

    vmat[index0(nmax, m+shift, m+shift)] = (double) (m+1) /nmax-1; 
    gauss_elimination(nmax, vmat);
    LU(vmat, rhs, sol);
    printf("%30.20f\n", sol[0]);
    
}
