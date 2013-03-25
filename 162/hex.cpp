#include "../lib/int.h"
GeneralInteger hex(int pos, int flag, int maxdig)
{
    ++pos;
    int xa = 0;
    if(flag & 1) ++xa;
    if(flag & 2) ++xa;
    if(flag & 4) ++xa;
    if(xa == 3){
        int shift = maxdig - pos+1;
        GeneralInteger one(1);
        GeneralInteger sum(1);
        assert(shift >= 0);
        while(shift){
            sum = sum.multiply(16);
            --shift;
        }
        sum = sum.minus(one);
        sum = sum.divide(15);
        sum = sum.multiply(16);
        sum = sum +GeneralInteger(1);
        return sum;
    }
    if(pos == maxdig){
        if(xa <= 1) return 0;
        if(xa == 2) return 1;
    }
    GeneralInteger sum(0);
    sum += hex(pos, flag|1, maxdig);
    if(pos == 2) {
        sum.print();
        printf("\n");
    }
    sum += hex(pos, flag|2, maxdig);
    if(pos == 2) {
        sum.print();
        printf("\n");
    }
    sum += hex(pos, flag|4, maxdig);
    if(pos == 2) {
        sum.print();
        printf("\n");
    }
    GeneralInteger gx= hex(pos, flag, maxdig);
    sum += gx.multiply(13);
    if(pos == 2) {
        sum.print();
        printf("\n");
    }
    return sum;
}
int main(){
    int maxdig = 16;
    GeneralInteger g1 = hex(1, 1, maxdig);
    GeneralInteger g2 = hex(1, 0, maxdig);
    GeneralInteger g(0);
        g= g1.multiply(2) + g2.multiply(13);
    g.print();
}
