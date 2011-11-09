#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <set>
#include "../lib/typedef.h"
    vector<i64> px, py;
    vector<i64> npx, npy;
    int n = 5;
void generate_squares(int xp, int xq, set<i64>& nset){
    for(unsigned int i = 0; i < 5; ++i){
        i64 uy = xq*px[i]*px[i] + 2LL*xp * px[i]*py[i] +n*xq*py[i]*py[i];
        uy = uy > 0?uy: -uy;
        nset.insert(uy);
        uy = xq*px[i]*px[i] - 2LL*xp * px[i]*py[i] +n*xq*py[i]*py[i];
        uy = uy > 0?uy: -uy;
        nset.insert(uy);
        uy = xq*npx[i]*npx[i] + 2LL*xp*npx[i]*npy[i] +n*xq*npy[i]*npy[i];
        uy = uy > 0?uy: -uy;
        nset.insert(uy);
        uy = xq*npx[i]*npx[i] - 2LL*xp*npx[i]*npy[i] +n*xq*npy[i]*npy[i];
        uy = uy > 0?uy: -uy;
        nset.insert(uy);
    }
}
int main(){
    int a0 = 9, b0 = 4 ;
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
    set<i64> nset;
    int xp = 7, xq =1;
    nset.insert(xq);
    generate_squares(xp, xq, nset);
    xp = 8; xq =2;
    nset.insert(xq);
    generate_squares(xp, xq, nset);
    xp = 13; xq =5;
    nset.insert(xq);
    generate_squares(xp, xq, nset);
    for(set<i64>::iterator iter=nset.begin(); iter!= nset.end(); ++iter){
        printf("%lld\n", *iter);
    }
    int count = 0;
    i64 sum = 0;
    for(set<i64>::iterator iter=nset.begin(); iter!= nset.end(); ++iter){
        i64 i = *iter;
        i64 sq = floor(sqrt((double)5ll*i*i+44));
        if(sq*sq == i*i*5+44){
            if((sq-7)%5==0){
                ++count;
                sum += (sq-7)/5;
                printf("%lld %lld %d %lld\n", sq, i, count, (sq-7)/5);
            }
        }
        if((sq+1)*(sq+1) == i*i*5+44){
            if((sq-6)%5==0){
                ++count;
                sum += (sq-6)/5;
                printf("c %lld %lld %d %lld\n", sq+1, i, count, (sq-6)/5);
            }
        }
    }
    printf("%lld\n", sum);
}
