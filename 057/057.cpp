#include "../lib/int.h"
//why I am doing this? I can use double and log
//to figure out the answer.
int main()
{
    GeneralInteger a0(1);
    GeneralInteger b0(0);
    GeneralInteger a1(1);
    GeneralInteger b1(1);
    GeneralInteger p(0), q(0);;
    int iter = 0;
    int cnt = 0;
    while(iter < 1000){
       p = a0 + a1.multiply(2); 
       q = b0 + b1.multiply(2);
       if(p.numberDigit() != q.numberDigit())
           ++cnt;
       swap(a0, a1);
       swap(b0, b1);
       swap(a1, p);
       swap(b1, q);
       ++iter;
    }
    printf("%d\n", cnt);
}
