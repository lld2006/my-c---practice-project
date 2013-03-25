#include <cstdio>
#include "../lib/typedef.h"
#include <vector>
using namespace std;
int main(){
    i64 limit = 100000000000000000;
    //i64 limit = 1000000;
    vector<i64> fibvec;
    fibvec.push_back(1);
    fibvec.push_back(2);
    int pos = 1;
    i64 value = 0;
    while(true) {
        value = fibvec[pos] + fibvec[pos-1];
        if(value > limit) break; 
        ++pos;
        fibvec.push_back(value);
    }
    printf("%d\n", static_cast<int>(fibvec.size())); //0 -- 81 82 fib numbers
    vector<i64> zsum; // sum of rep number less than fibonacci number 
    zsum.resize(fibvec.size(), 0);
    zsum[1] =1;
    zsum[2] = 2;
    for(unsigned int i = 3; i < zsum.size(); ++i){
        zsum[i] = zsum[i-1] + zsum[i-2] + fibvec[i-2];
        printf("%d %lld\n", i, zsum[i]);
    }
    i64 delta = limit - fibvec.back() - 1;
    printf("delta %lld fibback %lld\n", delta, fibvec.back());
    i64 sum2 = 0; 
    while( delta > 1) {
        sum2 += (delta+1);
        unsigned int i = 0;
        for( i = fibvec.size() -1 ; i>=0; --i){
            if(fibvec[i] <= delta) 
                break ;
        }
        sum2 += zsum[i];
        delta = delta - fibvec[i];
    }
    printf("%lld\n", zsum.back()+sum2+1);
}
