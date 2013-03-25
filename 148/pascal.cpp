#include <cstdio>
#include <cmath>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;
int fast(int number){
    int ret = 0;
    int count = 0;
    for(int i = 1; i <=number; ++i){
        int v1 = number+1-i;
        int v2 = i;
        while(v1%7==0){
            ++count;
            v1/=7;
        }
        while(v2%7==0){
            --count;
            v2/=7;
        }
        if(count > 0)
            ++ret;
    }
    return number+1-ret;
}
i64 ndiv(i64 num, vector<i64>& nvec){
    if(num <7) return num*(num+1)/2;
    i64 sum = 0;
    int value = num;
    int pwr = log((double)value)/log((double) 7);    
    int p7 = power(7LL, pwr);
    int quo = num/p7;
    i64 remainder = value- p7*quo;
    sum += quo*(quo+1)/2*nvec[pwr]+(quo+1)*ndiv(remainder, nvec);
    return sum;
}
int main(){
    vector<i64> n7vec;
    i64 prod = 28;
    i64 value = 1;
    for(int i = 0; i<=10; ++i){
        n7vec.push_back(value);
        value *= prod;
    }
    i64 num = 1000000000;
    value = ndiv(num, n7vec);
    printf("%lld\n", value);
}
