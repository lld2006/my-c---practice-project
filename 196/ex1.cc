#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int Bits[32],*isp;
long long int first;

int ISPRIME(long long int n)  {
    if(n%2==0)  return 0;
    n-=first;
    if(isp[n>>5]&Bits[n&31])  return 1;
    return 0;
}

int main()  {
    
    int seconds=time(NULL);
    
    int N[2]={5678027,7208785},all,T,j,i,d,e,interval,step,L;
    int dx[9]={-1,0,1,1,1,0,-1,-1,0};
    int dy[9]={1,1,1,0,-1,-1,-1,0,0};
    long long int n,x,y,x2,y2,K,last,p,low,sum=0;
    unsigned int *isprime;
    Bits[0]=1;
    for(i=1;i<32;i++) Bits[i]=Bits[i-1]<<1;
    isprime=(unsigned int*) (malloc) (159375*sizeof(unsigned int));
    isp=(unsigned int*) (malloc) (1150000*sizeof(unsigned int));
    for(i=0;i<159375;i++)  isprime[i]=4294967295LL;
    for(i=3;i<2258;i+=2)  {
        if(isprime[i>>5]&Bits[i&31])  {
           step=i<<1;
           for(j=i*i;j<5100000;j+=step)  isprime[j>>5]&=~Bits[j&31];
        }
    }
    
    for(i=0;i<2;i++)  {
        n=N[i];
        K=n*(n-1)/2;
        
        first=(n-2)*(n-3)/2+1;
        last=(n+2)*(n+3)/2;
        interval=last-first;
        L=interval/32+1;
        for(j=0;j<=L;j++)  isp[j]=4294967295LL;
        for(p=3;p*p<=last;p+=2)  {
            if(isprime[p>>5]&Bits[p&31]) {
               low=((first+p-1)/p)*p;
               if(low%2==0)  low+=p;
               low-=first;
               step=p<<1;
               for(j=low;j<=interval;j+=step)  isp[j>>5]&=~Bits[j&31];
        }}
        
        for(j=1;j<=n;j++)  {
            if(ISPRIME(K+j)==1)  {
               T=0;
               for(d=0;d<9;d++)  {
                   x=n+dx[d];
                   y=j+dy[d];
                   if((y>0)&&(y<=x)&&(ISPRIME(x*(x-1)/2+y)==1))  {
                   all=0;
                   for(e=0;e<8;e++)  {
                       x2=x+dx[e];
                       y2=y+dy[e];
                       if((y2>0)&&(y2<=x2)&&(ISPRIME((x2-1)*x2/2+y2)==1))  all++;
                   }
                   if(all>=2)  T=1;
                   }
               }
               if(T)  sum+=K+j;
            }
        }
    }
    printf("%lld\nTime=%ld sec.\n",sum,time(NULL)-seconds);
    return 0;
}
