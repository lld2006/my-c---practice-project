#include <cmath>
#include <cstdio>
#include <cassert>
//the problem itself is amazing! once you know the trick, it is simple!
double pi = atan(1.0)*4;
double area(int a, int b, int c)
{
    double s3 = 0.0;
    assert(a <= b && b<= c);
    double q = (a+b-c)/2.0;
    double p = (a+c-b)/2.0;
    double r = (b+c-a)/2.0;
    double triA = sqrt(p*q*r*(p+q+r));
    double s = triA/(p+q+r);//in-circle
    s3 += s*s;
    double y = sqrt(r*(r+q)*(p+r)/(p+q+r));
    assert(y > s);
    double r1 = s*(y-s)/(y+s);
    double rx = 1/sqrt(s) + 1/sqrt(r1);
    double x = 1/(rx*rx);
    double t = s*(y-s-2*r1)/(y+s);//region inside r1
    s3 += r1*r1;
    y = sqrt(p*(q+p)*(r+p)/(p+q+r));
    double r2 = s*(y-s)/(y+s); //from p
    y = sqrt(q*(q+r)*(q+p)/(p+q+r));
    double r3 = s*(y-s)/(y+s);
    assert(r1>=r2);
    assert(r2>=r3);
    //printf("a=%d b=%d c=%d\n", a, b, c);
    //printf("%f %f %f %f %f\n",r1,r2,r3,t,x);
    if(t > r2) r2 = t;
    if(x > r2) r2 = x;
    if(r3>r2)r2=r3;
    s3 += r2*r2;
    //printf("p=%15.10f q=%15.10f r=%15.10f\n", p, q, r);
    //printf("r1=%15.10f r2=%15.10f r3=%15.10f\n", r1, r2, r3);
    return s3 * pi;
}
int main()
{
    double atot = 0;
    double cnt = 0;
    int n = 1803;
    for(int ni=2; ni<=n; ++ni){
        printf("%d\n", ni);
        for(int b=(ni+1)/2; b<ni; ++b){
            for(int c = b; c<ni; ++c){
                int a = ni-b;
                assert(a+b> c);
                assert(a>0 && a<=b);
                ++cnt;
                double t = area(a, b, c);
                atot += t;
            }
        }
    }
    printf("%15.10f\n",atot/cnt);
}
