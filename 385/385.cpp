#include <cstdio>
#include <complex>
using namespace std;
int main()
{
    int target = 100;
    for(int a1= 0; a1<=target; ++a1){
        for(int b1 = 0; b1<=target; ++b1){
            for(int c1=-target; c1<=target; ++c1){
                for(int d1 = -target; d1<=target; ++d1){
                    complex<int> z1 = complex<int>(a1, b1);
                    complex<int> z2 = complex<int>(c1, d1);
                    if(z1*z2+z1*z1+z2*z2==39)
                        printf("%d %d %d %d %d %d\n", a1, b1, c1, d1, -(a1+c1), -(b1+d1));
                }
            }
        }
    }
}
