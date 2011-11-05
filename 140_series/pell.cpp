#include <cstdio>
#include "../lib/typedef.h"
int main(){
    vector<i64> px, py;
    vector<i64> npx, npy;
    int a0 = 9, b0 = 4, n = 5;
    i64 a=9, b=4;
    px.push_back(a); py.push_back(b);
    for(int i = 1; i < 14; ++i){
       i64 ta = a*a0 +b*b0*n; 
       i64 tb = a*b0+b*a0;
       px.push_back(ta); py.push_back(tb);
       a = ta; b = tb;
    }
    a = 2 ; b = 1;
    npx.push_back(a); npy.push_back(b);
    for(int i = 1; i < 14; ++i){
        i64 ta = a*a0+b*b0*n;
        i64 tb = a*b0+b*a0;
        npx.push_back(ta); npy.push_back(tb);
        a = ta; b=tb;
    }
    for(unsigned int i = 0; i < px.size(); ++i){
        printf("pos %lld %lld\n",px[i], py[i]);
        printf("neg %lld %lld\n",npx[i], npy[i]);
    }
}
