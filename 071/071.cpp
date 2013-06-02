#include <cstdio>
int main()
{
    int nx = 1;
    int dx = 3;
    for(unsigned int i = 3; i <= 1000000; ++i){
        if(i % 7 == 0) continue;
        int num = i * 3/7;
        if(num * dx > nx * i){
            nx = num;
            dx = i;
        }
    }
    printf("%d %d\n", nx, dx);
}
