#include <stdio.h>
#include <time.h>


void printint64(long long int n)  {
    long long int M=n;
    if(M<0)  printf("-"),M=-M;
    int digit[20],i,len;
    
    for(i=0;i<20;i++)  digit[i]=M%10,M/=10;
    len=19;
    while((len>0)&&(digit[len]==0))  len--;
    for(i=len;i>=0;i--) printf("%d",digit[i]);
    printf("\n");
    
    return;
}

int main()  {

    double dtime=clock();

    long long int A[6561],B[6561],sum;
    int n,i,j,c,d,prod,pow3,lpow3,k,x[3];
    
    A[0]=1;
    A[1]=1;
    A[2]=1;
    pow3=1;
    lpow3=3;
    for(n=2;n<=8;n++)  {
        pow3*=3;
        lpow3*=3;
        for(i=0;i<lpow3;i++)  B[i]=0;
        for(i=0;i<pow3;i++)  {
            for(j=0;j<lpow3;j++)  {
                prod=1;
                c=i;
                d=j;
                for(k=1;k<n;k++)  {
                    x[0]=1,x[1]=1,x[2]=1;
                    x[c%3]=0;
                    x[d%3]=0;
                    x[(d/3)%3]=0;
                    c/=3;
                    d/=3;
                    prod*=x[0]+x[1]+x[2];
                }
                B[j]+=(long long int) A[i]*prod;
            }
        }
        for(i=0;i<lpow3;i++)  A[i]=B[i];
    }
    sum=0;
    for(i=0;i<6561;i++)  sum+=A[i];
    printint64(sum);
    
    printf("Time=%.3lf sec.\n",(double) (clock()-dtime)/CLOCKS_PER_SEC);
    
    return 0;
}
