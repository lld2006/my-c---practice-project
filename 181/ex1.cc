#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//lesson need to consider how this is done
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

    long long int ****F;
    int i,j,k,l,s;
    
    F=(long long int****) (malloc) ((B+1)*sizeof(long long int));
    for(i=0;i<=B;i++)  F[i]=(long long int***) (malloc) ((W+1)*sizeof(long long int));
    for(i=0;i<=B;i++)  
        for(j=0;j<=W;j++)  F[i][j]=(long long int**) (malloc) ((B+1)*sizeof(long long int));
    for(i=0;i<=B;i++)  
        for(j=0;j<=W;j++) 
           for(k=0;k<=B;k++)  F[i][j][k]=(long long int*) (malloc) ((W+1)*sizeof(long long int));
    // B W B W
    
    for(k=0;k<=B;k++)
        for(l=0;l<=W;l++)   F[0][0][k][l]=1;
    
    for(s=1;s<=B+W;s++)  {
        for(i=0;i<=B;i++)  {
            j=s-i;
            if((j>=0)&&(j<=W))  {
                for(k=B;k>=0;k--)  {
                    for(l=W;l>=0;l--)  {
                        if(k>i)  F[i][j][k][l]=0;
                        else if(k+l==0)  F[i][j][k][l]=F[i][j][0][1];
                        else if(k==B)  {
                              if((i==B)&&(l<=j))  F[i][j][k][l]=1;
                              else                F[i][j][k][l]=0;
                        }
                        else if(l==W)  {
                              if(j<W)  F[i][j][k][l]=F[i][j][k+1][0];
                              else     F[i][j][k][l]=F[i-k][j-W][k][l]+F[i][j][k+1][0];
                        }
                        else if(l>j)  F[i][j][k][l]=F[i][j][k+1][0];
                        else F[i][j][k][l]=F[i-k][j-l][k][l]+F[i][j][k][l+1];
                    }
                 }
              }
         }
     }
     printint64(F[B][W][0][0]);
     printf("time=%.3lf sec.\n",(double) (clock()-dtime)/CLOCKS_PER_SEC);
     
     return 0;
}
