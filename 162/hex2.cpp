#include <cassert>
#include <cstdio>
unsigned long long hex(int pos, int flag, int maxdig)
{
    ++pos;
    int xa = 0;
    if(flag & 1) ++xa;
    if(flag & 2) ++xa;
    if(flag & 4) ++xa;
    if(xa == 3){
        int shift = maxdig - pos+1;
        unsigned long long sum = 1;
        assert(shift >= 0);
        while(shift){
            sum *= 16;
            --shift;
        }
        sum -= 1;
        sum /= 15;
        sum *= 16;
        sum += 1;
        return sum;
    }
    if(pos == maxdig){
        if(xa <= 1) return 0;
        if(xa == 2) return 1;
    }
    unsigned long long sum=0;
    sum += hex(pos, flag|1, maxdig);
    if(pos == 2) {
        printf("%I64d\n", sum);
    }
    sum += hex(pos, flag|2, maxdig);
    if(pos == 2) {
        printf("%I64d\n", sum);
    }
    sum += hex(pos, flag|4, maxdig);
    if(pos == 2) {
        printf("%I64d\n", sum);
    }
    sum += 13*hex(pos, flag, maxdig);
    if(pos == 2) {
        printf("%I64d\n", sum);
    }
    return sum;
}
int main(){
    int maxdig = 16;
    unsigned long long g1 = hex(1, 1, maxdig);
    unsigned long long g2 = hex(1, 0, maxdig);
    unsigned long long g= g1*2 + g2*13;
    printf("%I64d\n", g);
}
