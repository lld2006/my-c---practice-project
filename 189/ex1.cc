#include <stdio.h>
#include <time.h>
#include <cassert>
 
 
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
    int n,i,j,d,pow3,lpow3,k,p,c1,c2,x[3];
 
    A[0]=1;
    A[1]=1;
    A[2]=1;
    pow3=1;
    lpow3=3;
    for(n=2;n<=8;n++)  {
        pow3*=3; //3^n
        lpow3*=3; //3^(n+1)
        for(i=0;i<pow3;i++)  B[i]=A[i],B[i+pow3]=A[i],B[i+2*pow3]=A[i];
        
        p=pow3/3; //3^(n-1)
        for(k=1;k<n;k++)  {
            for(i=0;i<lpow3;i++)  A[i]=0;
            for(i=0;i<lpow3;i++){
                c1=(i/(3*p))%3; //in i = 0, this is actually the highest digit
                c2=(i/p)%3;     //          this being the second digit
                d=i-p*c2;
                for(j=0;j<3;j++){
                    x[0]=1,x[1]=1,x[2]=1;
                    x[c1]=0;
                    x[c2]=0;
                    x[j]=0;
                    //keep the current position or move to a new position
                    //we write it to position d+j*p simply because we have 
                    //B[d+c2*p] numbers at d+c2*p this count should be kept
                    //x sum is the multiplier of up-side down triangles
                    //this greatly reduced the number of divisions needed.
                    //this is actually a row-wise dynamic programming inside
                    //a length-wise dynamic programming
                    A[d+j*p]+=(long long int) B[i]*(x[0]+x[1]+x[2]); 
                    assert(i == d+c2*p);
                }
            }
            for(i=0;i<lpow3;i++)  B[i]=A[i]; // this line is very important
            p/=3;
        }
    }
    sum=0;
    for(i=0;i<6561;i++)  {
        sum+=A[i];
    }
    printint64(sum);
 
    printf("Time=%.3lf sec.\n",(double) (clock()-dtime)/CLOCKS_PER_SEC);
 
    return 0;
}
