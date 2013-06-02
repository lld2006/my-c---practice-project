#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
    int len = 100;
    int sum = 0;
    for( int a = 2; a< len ; ++a)
        for (int b=1; b < a; ++b){
            int xa = a*a-b*b;
            int xb = 2*a*b;
            int xc = a*a+b*b;
            if(xc <= len){
                //assume xa < xb
                if(xa > xb)
                    swap(xa, xb);
                sum += (3*xa-xb);
            }
        }
    printf("%d\n", sum);
}
