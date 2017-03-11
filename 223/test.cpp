#include <cstdio>
#include <cmath>
#include <cassert>
int main()
{
    int limit = 200;
    int cnt = (limit-1)/2;
    for(int a = 2; a <= limit/3;++a){
        for(int b = a; b<limit/2; ++b){
            int val = a*a + b*b-1;
            int v2 = round(sqrt(val));
            if(v2 * v2 == val && v2 + a + b <= limit){
                ++cnt;
                printf("%d %d %d %d\n", a, b, v2, a+b+v2);
                assert(a+b > v2);
            }
        }
    }
    printf("%d\n", cnt);
}
