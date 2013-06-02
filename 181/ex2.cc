#include <stdio.h>
#include <time.h>

//best method. The best thing about this algorithm is 
//that the memory usage is very small. and the array is 
//gradually updated to what is needed.
#define B 60
#define W 40

void printint64(long long int n)  {
    long long int M=n;
    int digit[20],i,len;
 
    for(i=0;i<20;i++)  digit[i]=M%10,M/=10;
    len=19;
    while((len>=0)&&(digit[len]==0))  len--;
    for(i=len;i>=0;i--) printf("%d",digit[i]);
    printf("\n");
 
    return;
}

int main()  {

    double dtime=clock();

    long long int F[B+1][W+1];
    int i,j,k,l;
    
    for(i=0;i<=B;i++)
        for(j=0;j<=W;j++)   F[i][j]=0;
    
    F[0][0]=1; //empty
    for(i=0;i<=B;i++)  { //black i
        for(j=0;j<=W;j++)  { //white j
            if(i+j)  {
               for(k=i;k<=B;k++)
                   for(l=j;l<=W;l++)  F[k][l]+=F[k-i][l-j];
            }
        }
    }
    dtime=(double) (clock()-dtime)/CLOCKS_PER_SEC;
    printint64(F[B][W]);
    printf("time=%.3lf sec.\n",dtime);
     
     return 0;
}
