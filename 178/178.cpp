#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;
int dim = 10;
int index30(int dim, int i, int j, int k){
    return i*dim*dim+j*dim+k;
}
int main()
{
    vector<i64> vn;
    vn.resize(1000, 0);
    for(unsigned int i =1; i<=9; ++i){
        vn[index30(dim,i,i,i)] = 1;
    }
    i64 sum = 0;
    for(int ndig= 2; ndig<=40; ++ndig){
        for(unsigned int i =0; i<= 9; ++i)
            sum += vn[index30(dim, i,0,9)];
        
        vector<i64> vnew; 
        vnew.resize(1000,0);
        for(int nmin = 0; nmin<=9; ++nmin){
            for(int nmax=nmin; nmax<=9;++nmax){
                for(int i = nmin; i<=nmax; ++i){
                    if(vn[index30(dim, i,nmin, nmax)] ==0)
                        continue;
                    if(i==0){
                        assert(nmax>=1 && nmin==0);
                        vnew[index30(dim,1,nmin, nmax)] += vn[index30(dim,i,nmin, nmax)];
                    }else if(i==9){
                        int newmin = nmin > 8? 8:nmin;
                        assert( nmax==9);
                        vnew[index30(dim,8,newmin, nmax)] += vn[index30(dim, i,nmin,nmax)];
                    }else{
                        int newmin = nmin > i-1? i-1:nmin;
                        vnew[index30(dim, i-1,newmin, nmax)] += vn[index30(dim,i,nmin,nmax)];
                        int newmax = nmax > i+1? nmax:i+1;
                        vnew[index30(dim, i+1,nmin, newmax)] += vn[index30(dim,i,nmin,nmax)];
                    }
                }
            }
        }
        vn.swap(vnew);
    }
    for(unsigned i=0; i<=9; ++i)
        sum += vn[index30(dim,i, 0,9)];
    
    printf("%lld\n", sum);
}
