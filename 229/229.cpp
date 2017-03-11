#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <bitset>
#include "../lib/typedef.h"
using namespace std;

void bset(bitset<10000001>& bits, int multiplier, int index)
{
    i64 seg = 10000000LL*index;
    i64 seg1 = 10000000LL*(index+1);
    for(i64 i =1; i*i*multiplier <= seg1; ++i){
        i64 i2 = i*i*multiplier;
        i64 jstart = 0;
        if(i2 >= seg  ) 
            jstart = 1;
        else{
            jstart = round(sqrt(seg - i2) );
            if(jstart * jstart <seg-i2) ++jstart;
        }
        assert(jstart >= 1);
        for(i64 j2 = i2+jstart*jstart, incr =2*jstart-1 ; j2 <= seg1; incr += 2, j2 += incr ){
            bits.set(j2-seg);
        }
    }
}
int main()
{
    bitset<10000001> b1;
    bitset<10000001> b2;
    bitset<10000001> b3;
    bitset<10000001> b4;
    int cnt = 0;
    for(unsigned int i = 0; i < 200; ++i ){
        b1.reset(); b2.reset(); b3.reset(); b4.reset();
        bset(b1, 1, i);
        bset(b2, 2, i);
        bset(b3, 3, i);
        bset(b4, 7, i);
        b1 &= b2;
        b1 &= b3;
        b1 &= b4;
        cnt += b1.count()-b1.test(0);
        printf("%d %d\n", i , cnt);
    }
    printf("%d\n", cnt);
}
