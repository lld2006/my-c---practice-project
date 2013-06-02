//base should be a prime
#include <cstdio>
#include "../lib/tools.h"
void update_5(i64 num, vector<int>& vn, int& nall);
i64 numberof(i64 num, int base)
{
    i64 cnt = num;
    while(num){
        int res = num % base;
        cnt -= res;
        num/= base;
    }
    return cnt/(base-1);
}
void update_2(i64 num, vector<int>& vn, int& nall)
{
    if(num <= 1) return;
    int quote = num/100000;
    nall += quote;
    int res = num % 100000;
    //actually 5 will be updated later
    for(int i=1; i<= res; i+=2){
        ++vn[i];
    }
    update_2(num/2, vn, nall);
    update_5(num/5, vn, nall);
}
void update_5(i64 num, vector<int>& vn, int& nall)
{
    if(num <= 1) return;
    int quote = num/100000;
    nall += quote;
    int res = num % 100000;
    //actually 5 will be updated later
    for(int i=1; i<= res; i+=2){
        ++vn[i];
    }
    update_5(num/5, vn, nall);
}
int main()
{
    i64 target = 1000000000000LL;
    //target = 75;
    vector<int> vn;
    vn.resize(100000, 0);
    int nall = 0;
    i64 n2 = numberof(target, 2);
    n2 -= numberof(target, 5);
    update_2(target, vn, nall);
    i64 prod = 1;
    for(int i = 1; i < 100000; i+=2){
        if(i % 5)
        prod *= i;
        prod %= 100000;
    }
    i64 result = powermodule(prod, nall, 100000);
    result *= powermodule(2, n2, 100000);
    result %= 100000;
    for(unsigned int i = 1; i< vn.size(); i+=2 ){
        if((i % 5 )== 0) continue;
        if(vn[i]){
            result *= powermodule(i, vn[i], 100000);
            result %= 100000;
        }
    }
    printf("%lld\n", result);
}
