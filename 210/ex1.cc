#include <stdio.h>
#include <math.h>
#define r 1000000000

long long int ABS(long long int x)  {
    if(x>0)  return x;
    return -x;
}

long long int MIN(long long int x,long long int y)  {
    if(x>y)  return y;
    return x;
}

long long int MAX(long long int x,long long int y)  {
    if(x<y)  return y;
    return x;
}

int main()  {

    long long int count=0,det,R,y,r2,r4,L,x1,x2;
    
    R=r;
    r2=R*R/16;
    r4=R/4;
    
    for(y=-r;y<=r;y++)  {
        L=r-ABS(y);
        det=r2-(4*y*y-R*y);
        if(det>0)  {
           det=(long long int)  sqrt(det-1);
           x1=MAX(-L,(r4-det+(r4>=det))/2);
           x2=MIN(L,(r4+det)/2);
           if(x1<=x2)  count+=x2-x1+1;
        }
    }
    printf("%lld\n",count+3*R*R/2-R/4+1);
    return 0;
}
