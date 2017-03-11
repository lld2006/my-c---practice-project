#include <iostream>
#include <bitset>
#include <cmath>
#include <stdint.h>

const uint32_t size=2000000000;
std::bitset<size+1> bs[4];

int main() {
    uint32_t coef[] = {0,1,1,4}, sum = 0;
    uint64_t e;
    for (uint32_t a=1,c=1; (c=a*a)<=size; a++)
        for (uint32_t b=1,d=1; (d=b*b)<=size && (e=c+d)<=size; b++)
            for (int i=0; i<4 && (e+=(uint64_t)coef[i]*d)<=size; i++)
                bs[i].set(e);
    for (uint32_t i=0; i<=size; i++) {
        if (bs[0][i]&&bs[1][i]&&bs[2][i]&&bs[3][i]) ++sum;
    }
    std::cout << sum << std::endl;
}
