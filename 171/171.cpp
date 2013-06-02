#include "../lib/typedef.h"
#include <cstdio>

int main()
{
    i64 nmod = 1000000000LL;
    vector<i64> sqsum;
    vector<i64> vn;
    sqsum.resize(20*81+1, 0);
    vn.resize(20*81+1, 0);
    vn[0] = 1;
    i64 pow10 = 1;
    for(int i = 1; i<=20; ++i){
        vector<i64> vnew, sumnew;
        sumnew.resize(20*81+1, 0);
        vnew.resize(20*81+1, 0);
        for( int j = 0; j<= (i-1)*81; ++j ){
            for(int d = 0; d< 10; ++d ){
                sumnew[j + d*d] +=  d*pow10*vn[j]+sqsum[j];
                vnew[j+d*d] += vn[j]; // count of numbers which sqsum == j+d*d
            }
        }
        for(int j = 0; j <= i * 81; ++j){
            sumnew[j] %= nmod;
            vnew[j] %= nmod;
        }
        pow10 *= 10LL;
        pow10 %= nmod;
        vn.swap(vnew);
        sumnew.swap(sqsum);
    }
    i64 sum = 0;
    for(unsigned int i=1; i*i< sqsum.size(); ++i){
        sum += sqsum[i*i];
    }
    printf("%lld\n", sum%nmod);
}
