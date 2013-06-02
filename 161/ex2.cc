#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    int x[3][9]={{0,0,0,0,0,0,0,-1,0},
                 {0,0,0,1,0,0,1,0,0},
                 {0,0,0,2,1,1,1,0,0}};
    int y[3][9]={{0,0,0,0,0,0,0,1,0},
                {0,1,1,0,1,1,0,0,0},
                {0,0,2,0,1,0,1,1,0}};

    int num[9]={1,2,3,3,3,3,3,3,0};
    int M[16][4],A[16],rem3;

void printint64(long long int n)
{
  int i,len,digit[20];
  
  if(n<0)  printf("-"),n=-n;
  
  digit[0]=n%10,n/=10,len=1;
  while(n)  digit[len]=n%10,n/=10,len++;
  for(i=len-1;i>=0;i--)  printf("%d",digit[i]);
  
  return;
}

void re(int pos)  {
    int j,c=A[pos];
    
    for(j=0;j<num[c];j++)  M[pos+x[j][c]][y[j][c]]--;
    rem3-=num[c];
    
    return;
}


int main()  {

    double dtime=clock();
    int c,i,j,k,n,w1,w2,T,pos,pow3[9];
    int *u,*w,var=0;

    u=(int*) (malloc) (131072*sizeof(int));
    w=(int*) (malloc) (131072*sizeof(int));

    pow3[0]=1;
    for(i=1;i<9;i++)  pow3[i]=3*pow3[i-1];

    long long int p[19683],q[19683];
    
    p[0]=1;
    for(i=1;i<19683;i++)  p[i]=0;
    for(i=0;i<19683;i++)  q[i]=0;
    
        pos=0;
        A[0]=0;
        rem3=0;
        for(j=0;j<11;j++)
            for(k=0;k<3;k++)  M[j][k]=0;

        while(A[0]<7)  {
            if(M[pos][0])  A[pos]=8,pos++,A[pos]=0;
            else {
                  c=A[pos];
                  rem3+=num[c];
                  if((pos<8)||(rem3%3==0))  {
                     T=1;
                     for(j=0;j<num[c];j++)  {
                         M[pos+x[j][c]][y[j][c]]++;
                         if(M[pos+x[j][c]][y[j][c]]>1)  T=0;
                     }
                     if((T==0)||M[9][0]||M[9][1])  {
                         re(pos);
                         while(A[pos]>=7)  pos--,re(pos);
                         A[pos]++;
                     }
                     else pos++,A[pos]=0;
                  }
                  else {
                       rem3-=num[c];
                       while(A[pos]>=7)  pos--,re(pos);
                       A[pos]++;
                  }
           }

        if(pos==9)  {
              w1=0;
              for(j=0;j<9;j++)  {
                  if(A[j]==0)  w1+=pow3[j];
                  else if(A[j]==1)  w1+=2*pow3[j];
              }
              w2=0;
              for(j=0;j<9;j++)  {
                  c=0;
                  if(M[j][1])  c=1;
                  if(M[j][2])  c=2;
                  w2+=c*pow3[j];
              }
              u[var]=w2;
              w[var]=w1;
              var++;
              pos--,re(pos);
              while(A[pos]>=7)  pos--,re(pos);
              A[pos]++;
        }
      }
      
   for(n=1;n<=12;n++)  {
       if(n%2)  {
          for(i=0;i<var;i++)  q[u[i]]+=p[w[i]];
          for(i=0;i<19683;i++)  p[i]=0;
          printf("tiling[9][%d]=",n),printint64(q[0]),printf("\n");
       }
       else  {
          for(i=0;i<var;i++)  p[u[i]]+=q[w[i]];
          for(i=0;i<19683;i++)  q[i]=0;
          printf("tiling[9][%d]=",n),printint64(p[0]),printf("\n");
       }
   }
   printf("Used time=%.0lf millisec.\n",(double) 1000.0*(clock()-dtime)/CLOCKS_PER_SEC);
   
   return 0;
}
