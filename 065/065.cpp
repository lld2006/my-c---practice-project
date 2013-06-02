#include "../lib/int.h"
#include <cstdio>
#include <numeric>
int main()
{
    GeneralInteger a1(3);
    GeneralInteger a0(2);
    GeneralInteger b1(1);
    GeneralInteger b0(1);
    GeneralInteger a(0), b(0);
    for(unsigned int i = 3; i <= 100; ++i){
         int mult = 1;
         if(i%3 == 0) 
             mult = 2*(i/3);
         a = a1.multiply(mult) + a0;
         b = b1.multiply(mult) + b0;
         a0 = a1; 
         b0 = b1;
         a1 = a;
         b1 = b;
    }
    vector<int>& vn = a1.getNumber();
    int sum = accumulate(vn.begin(), vn.end(), 0);
    printf("%d\n", sum);
}
