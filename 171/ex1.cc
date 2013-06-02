#include <stdio.h>
#include <time.h>
#define N 1000000000
 
int main()  {
 
    double dtime=clock();
 
    long long int S[1621],T[1621],E[1621],F[1621],pow10=1,all=0;
    int d,j,n,p;
 
    S[0]=0;
    E[0]=1;

    for(n=1;n<=20;n++)  {
        for(j=0;j<=81*(n-1);j++)  T[j]=S[j],F[j]=E[j];
        for(j=0;j<=81*n;j++)      S[j]=0,E[j]=0;
        for(p=0;p<=81*(n-1);p++)
            for(d=0;d<10;d++)  S[p+d*d]+=(T[p]+d*F[p]*pow10)%N,E[p+d*d]+=F[p];
        for(j=0;j<=81*n;j++)  S[j]%=N,E[j]%=N;
        pow10*=10;
        pow10%=N;
    }
 
    j=0;
    while(j*j<=81*20)  all+=S[j*j],j++;
    all%=N;        

    dtime=(double) ((clock()-dtime)/CLOCKS_PER_SEC);
    printf("sum=%d, time=%.3lf sec.\n",(int) all,dtime);
 
    return 0;
}
