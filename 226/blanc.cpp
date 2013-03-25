#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "../lib/tools.h"
#include "../lib/typedef.h"
//lesson, made a mistake in find_y if res *2 >pmod, need to subtract 
i64 scale;
double find_y(i64 px)
{
    i64 sum = 0;
    i64 pmod = scale;
    i64 pa = px;
    while(pmod > 1){
        i64 res = pa % pmod;
        if(res == 0) break;
        if(res * 2 > pmod){
            res = pmod-res;
        }
        sum += res;
        pmod /= 2;
    }
    return sum/(double)(scale);
}
double area(i64 nx)
{
    double b_area = 0;
    i64 pmod = scale/2;
    i64 n2 = 2;
    while(pmod >=1){
        double value = (double) nx/pmod;
        i64 integ = value;
        value -= integ;
        assert(value >= 0 && value < 1);
        double len = double(1)/n2;
        double unit_area = len*len;
        b_area += (double)(integ)/n2/n2;
        if(integ % 2 == 0)
            b_area += unit_area * value * value;
        else
            b_area += unit_area *(1.0 -(1.0-value) * (1.0-value));
        n2 *=2;
        assert(pmod %2 ==0 ||pmod == 1);
        pmod/=2;
        //printf("%30.20e\n", b_area);
    }
    return b_area/2;
}
int main()
{
    i64 base = 2;
    i64 p = 50;
    scale      = power(base, p);//scale of the system
    i64 ulimit = power(base, p-2);
    i64 dlimit = power(base, p-5);
    double y1 = find_y(ulimit);
    double y2 = find_y(ulimit/2);
    double y3 = find_y(5*ulimit/4);
    printf("test y value %e %e %e\n", y1, y2, y3);
    printf("area %30.20e %30.20e\n", area(ulimit), area(ulimit-1280000));
    //exit(1);
    i64 mid = (ulimit + dlimit)/2;
    double xc = 1.0/4;
    double yc = 1.0/2;
    double d2 = 1.0/16;
    double yt;
    while(ulimit-mid>1 || dlimit-mid > 1){
        yt = find_y(mid);
        double xt = (double)(mid)/scale;
        double dist = (xt-xc)*(xt-xc) +(yt-yc)*(yt-yc);
        printf("mid %lld, %lld %lld %30.20e\n", ulimit, mid, dlimit, dist);
        if(dist < d2)
            ulimit = mid;
        else
            dlimit = mid;
        mid = (ulimit + dlimit)/2;
    }
    double yt1 = find_y(mid), xt1=(double)mid/scale;
    double zz = (xt1 - xc)*(xt1-xc)+(yt1-yc)*(yt1-yc);
    printf("%lld %30.20e %30.20e %30.20e\n",mid, (double)mid/scale, yt1,zz );
    double a1 = area(mid);
    //double a1 = area(scale/2);
    //printf("%30.20e\n", a1);
    printf("%30.20e %30.20e\n", a1, 1.0/4-a1-0.12231073080135466);
}
