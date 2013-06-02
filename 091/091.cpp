#include <cstdio>
#include "../lib/tools.h"
int main()
{
    int limit = 5000;
    int total = 3*limit*limit;// right angle at 00, on x and y
    for(int x = 1; x <=limit;++x){
        for(int y = 1; y<=limit; ++y){
            int gxy = gcd(x, y);
            int dx = y/gxy;
            int dy = x/gxy;
            int nx =  x/dx;
            int ny = (limit - y)/dy;
            total += nx < ny? nx:ny;
            nx = (limit-x)/dx;
            ny = y/dy;
            total += nx < ny? nx:ny;
        }
    }
    printf("%d\n", total);
}
