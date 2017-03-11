#include <stdio.h>


#define N 30
#define steps 50

int main()  {
    
    int i,j,k,l,d,s,x,y;
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};
    double sum,ct[N][N],A[N][N],B[N][N],tot[N][N];
    
    for(i=0;i<N;i++)  {
        for(j=0;j<N;j++)  {
            if((i==0)||(i==N-1)||(j==0)||(j==N-1))  ct[i][j]=1.0/3.0;
            else ct[i][j]=0.25;
        }
    }
    ct[0][0]=0.5;
    ct[0][N-1]=0.5;
    ct[N-1][0]=0.5;
    ct[N-1][N-1]=0.5;
    
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)  tot[i][j]=1.0;
        
    for(i=0;i<N;i++)  {
        for(j=0;j<N;j++)  {
            for(k=0;k<N;k++)
                for(l=0;l<N;l++)  A[k][l]=0.0;
            A[i][j]=1;
            for(s=1;s<=steps;s++)  {
                for(k=0;k<N;k++)
                    for(l=0;l<N;l++)  B[k][l]=A[k][l],A[k][l]=0.0;
                for(k=0;k<N;k++)  {
                    for(l=0;l<N;l++)  {
                        for(d=0;d<4;d++)  {
                            x=k+dx[d];
                            y=l+dy[d];
                            if((x>=0)&&(x<N)&&(y>=0)&&(y<N))  A[x][y]+=B[k][l]*ct[k][l];
                        }
                    }
                }
           }
           for(k=0;k<N;k++)
               for(l=0;l<N;l++)  tot[k][l]*=1.0-A[k][l];
      }
   }
   sum=0.0;
   for(i=0;i<N;i++)
       for(j=0;j<N;j++)  sum+=tot[i][j];
   printf("%.6lf\n",sum);
   return 0;
}
