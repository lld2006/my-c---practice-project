#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;

int interior(int a, int b, int c, int d)
{
    int A2 = a*b+b*c+c*d+d*a + 2;
    int bound = gcd(a, b)+gcd(b, c)+gcd(c,d)+gcd(d, a);
    int final = A2-bound;
    assert((final & 1 )== 0);
    return final>>1;
}

int main()
{
    int nmax = 50001;
    vector<int> vsq;
    vsq.resize(nmax, 0);
    for(unsigned int i = 0; i < vsq.size(); ++i){
        int i2 = i * i;
        if(i2 >= nmax) break;
        vsq[i2]= 1;
    }
    int total = 0;
    int imax = 100;
    for(int ia = 1; ia <= imax; ++ia){
        for(int ib = 1; ib<= imax; ++ib){
            for(int ic = 1; ic<= imax; ++ic){
                for(int id = 1; id<= imax; ++id){
                    int res = interior(ia, ib, ic, id);
                    assert(res >= 0 && res < 50000);
                    if(vsq[res])++total;
                }
            }
        }
    }
    printf("%d\n", total);
}
