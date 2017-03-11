#include <stdio.h>
#include <stdlib.h>
 
 
#define lim 2000000000
#define interval 80000
 
int main()  {
 
   int a,a2,b,i,j,I,n,si=interval/8,ct,up,*st1,*st2,*st3,*st7;
   unsigned int *A,Bit[32],x;
   A=(unsigned int*)(malloc)(si*sizeof(unsigned int));
    st1=(int*)(malloc)(45000*sizeof(int));
    st2=(int*)(malloc)(45000*sizeof(int));
    st3=(int*)(malloc)(45000*sizeof(int));
    st7=(int*)(malloc)(45000*sizeof(int));
    
   for(i=0;i<45000;i++)  {
      st1[i]=i;
      st2[i]=1;
      st3[i]=1;
      st7[i]=1;
   }
   Bit[0]=1;
   for(n=1;n<32;n++)  Bit[n]=2*Bit[n-1];
   
   ct=0;
   for(I=0;I<lim;I+=interval)  {
   	for(i=0;i<si;i++)  A[i]=0;
    up=I+interval;
       
   for(a=1;2*a*a<up;a++)  {
       a2=a*a;
      for(b=st1[a];a2+b*b<up;b++)  {
          n=a2+b*b-I;
          A[n>>3]|=Bit[(n&7)<<2];
      }
      st1[a]=b;
   }
   for(a=1;a*a<up;a++)  {
       a2=a*a;
      for(b=st2[a];a2+2*b*b<up;b++)  {
          n=a2+2*b*b-I;
          A[n>>3]|=Bit[1+((n&7)<<2)];
      }
      st2[a]=b;
   }
   for(a=1;a*a<up;a++)  {
       a2=a*a;
      for(b=st3[a];a2+3*b*b<up;b++)  {
          n=a2+3*b*b-I;
          A[n>>3]|=Bit[2+((n&7)<<2)];
      }
      st3[a]=b;
   }
   for(a=1;a*a<up;a++)  {
       a2=a*a;
      for(b=st7[a];a2+7*b*b<up;b++)  {
          n=a2+7*b*b-I;
          A[n>>3]|=Bit[3+((n&7)<<2)];
      }
      st7[a]=b;
   }
 
   for(i=0;i<si;i++)  {
      x=A[i];
      for(j=0;j<8;j++)  {
          if((x&15)==15)  ct++;
         x>>=4;
      }
   }
    }
   printf("%d\n",ct);
   return 0;
}
