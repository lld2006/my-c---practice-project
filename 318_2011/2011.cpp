#include <cmath>
#include <cstdio>
#include <cassert>
typedef long long int i64;

int main()
{
    i64 sum = 0;
    i64 cnt = 0;
    double long ten = 10;
    for(unsigned int p = 1; p <=1005; ++p){
        for(unsigned int q = p +1; q <=2011-p; ++q){
            long double rootp = sqrt((long double)p);
            long double rootq = sqrt((long double)q);
            long double diff = (q-p)/(rootq+rootp);
            if(diff < 1.0){
                int ip = rootp + 0.01;
                int iq = rootq + 0.01;
                assert(ip * ip != rootp || iq * iq != rootq);
                int order = -log(ten)*2011/log(diff);
                assert(order > 0);
                sum += (order+2)/2;
                ++cnt;
            }else{
                assert(diff==1.0 || diff > 1+1e-15);
                break;
            }
        }
    }
    printf("%lld %lld\n", sum, cnt);
}
