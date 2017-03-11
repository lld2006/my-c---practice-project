#include <stdio.h>
#include <math.h>
#include <stdlib.h>
long long int gcd(long long int a,long long int b);

long long int minl(long long int x,long long int y);
long long int p[10];
long long int m[10];
int main()
{
  long long int a[]={0,5248,1312,2624,5760,3936};
  long long int b[]={0,640,1888,3776,3776,5664};
  long long int Sa=0;long long int Sb=0;
  for(int i=0;i<=5;i++)
    {
      Sa+=a[i];
      Sb+=b[i];
    }
  double maxf=0;
  long long int mina[10],minb[10];
  for(long long int a1=1;a1<=5248;a1++)
    {
      for(long long int b1=1;b1<=640;b1++)
   {
     if(b1*a[1]>a1*b[1])
       {
         bool ok=1;
        
         for(int i=1;i<=5;i++)
      {
        long long int numer=b1*a[1]*b[i]/gcd(b1*a[1]*b[i],a1*b[1]*a[i]);
        long long int denom=a1*b[1]*a[i]/gcd(b1*a[1]*b[i],a1*b[1]*a[i]);
        minb[i]=numer;
        mina[i]=denom;
        if(i==1)
          minb[1]=b1;
        if(i==1)
          mina[1]=a1;
        if(numer>b[i] || denom>a[i])
          ok=0;
      }
         long long int numer=Sa*b1*a[1]/gcd(Sa*b1*a[1],Sb*a1*b[1]);
         long long int denom=Sb*a1*b[1]/gcd(Sa*b1*a[1],Sb*a1*b[1]);
         if(numer>Sa || denom>Sb)
      ok=0;
         if(ok)
      {
        // printf("%lld/%lld\n",b1*a[1]/gcd(b1*a[1],a1*b[1]),a1*b[1]/gcd(b1*a[1],a1*b[1]));
       
       long long int numer=Sa*b1*a[1]/gcd(Sa*b1*a[1],Sb*a1*b[1]);
         long long int denom=Sb*a1*b[1]/gcd(Sa*b1*a[1],Sb*a1*b[1]);
         
         for(int i=1;i<=5;i++)
      {
        m[i]=denom*mina[i]-numer*minb[i];
        p[i]=minl(a[i]/mina[i],b[i]/minb[i]);
      }
         bool done=0;
         //printf("%lld %lld %lld\n",m[1],m[2],m[4]);
         //printf("%lld %lld %lld\n",p[1],p[2]+p[3]+p[5],p[4]);
         if(m[2]!=m[3] || m[3]!=m[5])
      {
        printf("Error\n");
        exit(-1);
      }
         for(long long int p235=1;p235<=p[2]+p[3]+p[5];p235++)
      for(long long int p4=1;p4<=p[4];p4++)
        {
          
          if(m[1]+m[2]*p235+m[4]*p4==0 && !done && (double)(b1*a[1])/(double)(a1*b[1])>maxf)
            {
         printf("%lld/%lld\n",b1*a[1]/gcd(b1*a[1],a1*b[1]),a1*b[1]/gcd(b1*a[1],a1*b[1]));
         maxf=(double)(b1*a[1])/(double)(a1*b[1]);
         done=1;
            }
        }


   
        
      }
       }
   }
    }
}



long long int gcd(long long int a,long long int b)
{
  if(b==0)
    return a;
  else
    return gcd(b,a%b);
}

long long int minl(long long int x,long long int y)
{
  if(x>y)
    return y;
  else
    return x;
}
