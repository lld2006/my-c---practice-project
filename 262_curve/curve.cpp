#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstdlib>
double radius = 1000*sqrt(17.0/40); 
double xcenter = 750;
double ycenter = 750;
double tol = 3e-11;
double tol2 = 1e-13;
double f(double x, double y)
{
    return ( 5000-0.005*(x*x+y*y+x*y)+12.5*(x+y) ) * exp( -fabs(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7) );
}
double f1(double x, double y)
{
    return ( 5000-0.005*(x*x+y*y+x*y)+12.5*(x+y) ) * exp( -(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7) );
}
double dfx(double x, double y)
{
    double x1 = x/1000;
    double y1 = y/1000;
    //use negative value
    double nexp = x1*x1+y1*y1-1.5*(x1+y1)+0.7;
    double nbase =  5000-0.005*(x*x+y*y+x*y)+12.5*(x+y) ;
    double dbase = -0.005*(2*x+y)+12.5;
    double dexp = 2e-3*x1-0.0015;
    if(nexp <=0){
        return (dbase+nbase*dexp)*exp(nexp);
    }else{
        return (dbase-nbase*dexp)*exp(-nexp);
    }
}
//assumption only one maximum, giving two ends, find max
void binary_search(double x1, double y1, double x2, double y2, double& retx, double& rety)
{
    double dydx=(y2-y1)/(x2-x1);
    double df1 = dfx(x1,y1) + dydx * dfx(y1,x1);
    double df2 = dfx(x2, y2)+ dydx * dfx(y2, x2);
    assert(df1 * df2 < 0);
    double xmid = 0, ymid=0;
    while(fabs(x2-x1)> 1e-12){
        xmid = (x1+x2)/2.0;
        ymid = (y1+y2)/2.0;
        double df3 = dfx(xmid, ymid)+dydx*dfx(ymid,xmid);
        if(df3 * df1 > 0){
            x1 = xmid;
            y1 = ymid;
        }else{
            x2 = xmid;
            y2 = ymid;
        }
    }
    retx = (x1+x2)/2;
    rety = (y1+y2)/2;
}

double find_y_at_h(double x, double h, double yguess)
{
    double y = yguess;
    assert(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7 > 0);
    double fy = f(x, yguess);
    while(fabs(fy-h)>tol){
        double slope = dfx(yguess, x); 
        double deltay = (fy-h) /slope;
        if(fabs(deltay) > 50)
            deltay= deltay >0?50:-50;
        yguess -= deltay;
        fy = f(x, yguess);
    }
    return yguess;
}

double tangent_h(double x, double h, double& y, double yguess)
{
    y = find_y_at_h(x, h,yguess);
    double dx = dfx(x,y);
    double dy = dfx(y,x);
    assert(dy != 0);
    return -dx/dy;
}
//find where start and end to line segment part
double find_tangent(double height, double start, double end, double yguess, double& ymid )
{
    double yfinal = 200;
    double xfinal = 200;
    double yend, ystart;
    double dend = tangent_h(end, height, yend, yguess);
    double y2 = yend + (xfinal-end)*dend;

    double dstart = tangent_h(start, height, ystart, yguess);
    double ys = ystart + (xfinal-start)*dstart;
    assert((y2 - yfinal)*(ys - yfinal) <0);

    double mid, y1;
    while(fabs(start - end) > tol){
        mid = (start + end)/2;
        double dmid = tangent_h(mid, height, ymid, yguess);
        y1 = ymid + (xfinal - mid)*dmid;
        if((y1-yfinal)*(ys - yfinal) > 0){
            assert((y1-yfinal)*(y2-yfinal) < 0);
            start = mid;
        }else{
            end = mid;
            y2 = y1;
        }
    }
    printf("tangent at small %30.15f\n", y1);
    return mid;
}
//along x axis, find y which give barrier eq h
double find_barrier_eq_h(double ymin, double ymax, double h, double& x)
{
    double ymid, ret1, ret2, hmid;
    binary_search(0, ymin, 1600, ymin, ret1, ret2);
    double hmin = f(ret1, ymin) -h;
    binary_search(0, ymax, 1600, ymax, ret1, ret2);
    double hmax = f(ret1,ymax)  - h;
    assert(hmin*hmax < 0);
    while(ymax - ymin > tol){
        ymid = (ymax+ymin)/2;
        binary_search(0, ymid, 1600, ymid, ret1, ret2);
        hmid = f(ret1,ymid) - h;
        if(hmid * hmin > 0)
            ymin = ymid;
        else 
            ymax = ymid;
    }
    x = ret1;
    return ymid;
}
void find_barrier_200(double xb, double h, double& ret1, double& ret2)
{
     double xstart = 600;
     double xend = xb;
     double x1, y1, x2, y2, h1, h2, ym, xm;
     binary_search(200, 200, xstart, 0, x1, y1);
     h1 = f(x1, y1)- h;
     binary_search(200, 200, xend, 0, x2, y2);
     h2 = f(x2, y2) - h;
     assert(h1 * h2 < 0);
     while(fabs(xend-xstart) > tol){
        double xmid = (xstart + xend)/2;
        binary_search(200, 200, xmid, 0, xm, ym);
        double hmid = f(xm, ym)-h;
        if(hmid * h1 > 0){
            xstart = xmid;
            h1 = hmid;
        }else{
            xend = xmid;
            h2 = hmid;
        }
     }
     binary_search(200,200, (xstart+xend)/2, 0, ret1, ret2);
}
void find_barrier_1400(double xb, double h, double& ret1, double& ret2)
{
     double ystart = 900;
     double yend = 672.89;
     double ybound = 1561.907083805850789;//1561.9
     double x1, y1, x2, y2, h1, h2, ym, xm;
     binary_search(1400, 1400, ybound, ystart, x1, y1);
     h1 = f(x1, y1)- h;
     binary_search(1400, 1400, ybound, yend, x2, y2);
     h2 = f(x2, y2) - h;
     assert(h1 * h2 < 0);
     while(fabs(yend-ystart) > tol){
        double ymid = (ystart + yend)/2;
        binary_search(1400, 1400, ybound, ymid, xm, ym);
        double hmid = f(xm, ym)-h;
        if(hmid * h1 > 0){
            ystart = ymid;
            h1 = hmid;
        }else{
            yend = ymid;
            h2 = hmid;
        }
     }
     binary_search(1400,1400, ybound, (ystart+yend)/2, ret1, ret2);
}
int main()
{
   /*   
   {
       double xstart = 1400, ystart = 1400;
       double xfinal = 1561.907083805850789, yfinal = 672.892772938465328;
       int nseg = 1000;
       double retx, rety;
       double dx = (xfinal- xstart)/nseg;
       double dy = (yfinal- ystart)/nseg;
       for(int i = 0; i <= nseg; ++i){
           //binary_search(1400, 1400, 1600, ystart+i*dy, retx, rety);
           printf("%d %30.15f\n", i, f(xstart+dx*i, ystart+i*dy));
       }
       binary_search(xstart, ystart, xfinal, yfinal, retx, rety);
       printf("%30.15f\n", f(retx, rety));
       exit(1);
   }
   */ 
   double PI = 4.0*atan(1.0);
   double ret1, ret2;
   double radius = sqrt(17.0/40)*1000;
   //first find the fmin, minimum height
   binary_search(0,0, 1600, 0, ret1, ret2 );
   double barrierx = ret1;
   double maxh = f(ret1, 0);
   printf("%30.15f, %30.15f %30.15f\n", ret1, f(ret1, 0), dfx(ret1, 0));
   //second, find the path to the barrier
   //double y200 = 0;
   //double x200 = find_tangent(maxh, 300, barrierx, -100,y200 );
   double x200, y200, x1400, y1400, tp;
   find_barrier_200(barrierx, maxh, x200, y200);
   printf("data 200| %30.15f %30.15f %30.15f\n", x200, y200, f(x200, y200)-maxh);
   printf("part2 %30.15f %30.15f %30.15f\n", f(x200, y200)-maxh, tangent_h(x200, maxh, tp, y200), (y200-200)/(x200-200) );
   find_barrier_1400(700, maxh, x1400,y1400);
   // x1400 = find_barrier_eq_h(1410, 1600, maxh, ret1);
   // y1400 = find_y_at_h(x1400, maxh, 1600);
   printf("data 1400 %30.15f %30.15f %30.15f\n", x1400, y1400, f(x1400, y1400)-maxh);
   printf("part 2 %30.15f %30.15f %30.15f\n", f(x1400, y1400)-maxh, tangent_h(x1400, maxh,tp, y1400), (y1400-1400)/(x1400-1400) );
   int nseg = 1000000;
   double y0 = y200;
   double total = sqrt((x200-200)*(x200-200)+(y200-200)*(y200-200));
   total += sqrt((x1400-1400)*(x1400-1400)+(y1400-1400)*(y1400-1400));
   //{
   //    double xstart = 1600, ystart = 900;
   //    double xfinal = 1400, yfinal = 1400;
   //    int nseg = 1000;
   //    double dx = (xfinal- xstart)/nseg;
   //    double dy = (yfinal- ystart)/nseg;
   //    for(int i = 0; i <= nseg; ++i){
   //        printf("%d %30.15f\n", i, f(xstart+i*dx, ystart+i*dy));
   //    }
   //    exit(1);
   //}
   //total += sqrt((x200-barrierx)*(x200-barrierx)+y200*y200);
   double dx = (1561.907083805850789 -x200)/nseg;
   for(unsigned int i=1; i<=nseg;++i){
       double y1 = find_y_at_h(x200+i*dx, maxh, y0);
       //printf("%30.15f %30.15f %30.15f\n", x200+i*dx, y1, f(x200+i*dx, y1));
       double ds = dx*dx+ (y1-y0)*(y1-y0);
       ds= sqrt(ds);
       total += ds;
       y0= y1;
   }
   //printf("------------------");
   nseg = 1000000;
   double x4 = 1561.907083805850789;
   dx = (x4 - x1400)/nseg;  
   y0 = find_y_at_h(x1400, maxh, y1400);

   for(unsigned int i=1; i<= nseg;++i){
       double y1 = find_y_at_h(x1400+i*dx, maxh, y0);
       //printf("%30.15f %30.15f %30.15f\n", x4+i*dx, y1, f(x4+i*dx, y1));
       double ds = dx*dx+ (y1-y0)*(y1-y0);
       ds= sqrt(ds);
       total += ds;
       y0= y1;
   }
   printf("%30.15f\n", total);
}
