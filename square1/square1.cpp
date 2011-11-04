#include <cstdio>
#include <cmath>
#include <cassert>
int main()
{
    int start = 1;
    int count = 0;
    for(int i =3 ; i<= 1000; ++i){
        if(i %2 ==0) 
            start = 2;
        else
            start = 1;
        count += (i-start)/2;
    }
    for(int n = 1001; n <= 250001; ++n){
        double xn = n;
        double yn = sqrt(xn*xn - 1000000);
        int m = yn;
        if( fabs( yn -m ) < 1e-8){
        //from m  to n -2
            count += (n-m)/2;
        }else if(fabs (yn-m-1) < 1e-8){
            assert(0);
            count += (n -m -1)/2;
        }else{
            count += (n-m-1)/2;
        }
    }
    printf("%d\n", count);
}
