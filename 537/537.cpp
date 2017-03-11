#include "../lib/tools.h"
#include <cstdio>
#include <vector>
using namespace std;
i64 nmod = 1004535809LL;
//this is stupid, need to use FFT for vector multiplication
void product_vec(const vector<int>& va, const vector<int>& vb, vector<int>& vc)
{
    vc.clear(); 
    vc.resize(va.size(), 0);
    for(unsigned int i = 0; i < va.size(); ++i){
        for(unsigned int j = 0; j < va.size() - i; ++j){
            i64 tp = (i64)va[i] * vb[j];
            tp %= nmod;
            vc[i+j] = (vc[i+j]+tp)%nmod;
        }
    }
}
int main()
{
    //this looks like a simple dynamic programming problem 
    //round by round is too slow
    vector<int> primes;
    primeWithin(primes, 230000);
    int nmax = 20000;
    vector<vector<int>> vnp;
    int layer = log(nmax)/log(2.0)+1;
    vnp.resize(layer);
    for( int i = 0; i<layer; ++i)
        vnp[i].resize(nmax+1, 0);
    int ps = 1;
    for( int i =0; i <= nmax; ++i){
        vnp[0][i] = primes[i]-ps;
        ps = primes[i];
    }
    //preparation
    for(int i = 1; i < layer; ++i){
        printf("prep %d\n", i);
        product_vec(vnp[i-1], vnp[i-1], vnp[i]);
    }
    vector<int> vc, vn;
    vn.resize(nmax+1, 0);
    vc.resize(nmax+1, 0);
    vc[0] = 1;
    int n = nmax;
    int level = 0;
    while(n){
        printf("%d\n", n);
        if(n & 1){
            product_vec(vc, vnp[level], vn);
            vc.swap(vn);
        }
        n/=2;
        ++level;
    }
    printf("%d\n", vc[nmax]);
}
