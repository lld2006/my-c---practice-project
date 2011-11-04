# include <cstdio>
# include <cmath>
# include <cassert>
# include "../lib/int.h"
// exceed int limit, need to use general integers
GeneralInteger f6(int d6);
GeneralInteger f5(int d5);
int main()
{
    int d6 = 144, d5=166;
    int flag;
    GeneralInteger n6 = f6(d6);
    GeneralInteger n5 = f5(d5);
    flag = (n6 == n5);//operator == overloadin 
    while(flag) 
    {
        if(d6 % 1000 == 0)
        {
        printf("d5= %d d6=%d\n", d5, d6);
        n5.print();
        n6.print();
        }
        if(flag > 0) {   
            ++d5;
            n5 = f5(d5);
        }
        else {
            ++d6;
            n6 = f6(d6);
        }
        flag = ( n6 == n5);
    }
    n6.print();
    return 0;
}


//hexagonal number
GeneralInteger f6(int d6)
{
    GeneralInteger x6(d6);
    x6 = x6.multiply( 2*d6 - 1);
    return x6;
} 

//pentagonal number
GeneralInteger f5(int d5)
{
  int i5 = 0, multiplier = 0;
  if( d5 %2 == 0) {
    i5 = 3* d5 -1;
    multiplier = d5/2;
  }else{
    i5 = (3 * d5 -1)/2;
    multiplier = d5;
  }
    GeneralInteger x5(i5);
    x5 = x5.multiply(multiplier);
    return x5;
}    
