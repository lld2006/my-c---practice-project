#include <cstdio>
#include <cmath>
#include <ctime>

typedef long long int LL;
double eps = 1e-9;

clock_t start=clock();

#define N 35000000
int minp[N];
int p[2222222];
int plen;
int cnt[N];

LL B = LL(1e12/sqrt(12.)+eps);

LL mypow(int a,int k)
{
   LL p=1;
   while(k--)
   {
      if(p>B/a) return B+1;
      p*=a;
   }
   return p;
}

int main()
{
   int i,j,k;
   cnt[1]=1;
   for(i=2;i<N;i++)
   {
      if(!minp[i])
      {
         if(i%6==1) p[plen++]=i;
         for(j=i;j<N;j+=i) if(!minp[j]) minp[j]=i;
      }
      for(j=i;j>1;)
      {
         int q=minp[j];
         if(q%6==1) break;
         for(;j%q==0;j/=q);
      }
      cnt[i]=cnt[i-1];
      if(j==1) cnt[i]++;
   }
   LL ans=0;
   LL n,m,q;

   //p[i]^12 * p[j] * v
   for(i=0;(n=mypow(p[i],12))<=B;i++)
   for(j=0;(m=n*p[j])<=B;j++) if(i!=j)
      ans+=cnt[B/m]+cnt[int(B/sqrt(3.)/m+eps)];
   printf("%lld\n",ans);

   //p[i]^7 * p[j]^2 * v
   for(i=0;(n=mypow(p[i],7))<=B;i++)
   for(j=0;(m=n*p[j]*p[j])<=B;j++) if(i!=j)
      ans+=cnt[B/m]+cnt[int(B/sqrt(3.)/m+eps)];
   printf("%lld\n",ans);

   //p[i]^2 * p[j]^2 * p[k] * v
   for(i=0;(n=LL(p[i])*p[i])*p[i+1]*p[i+1]<=B;i++)
   for(j=i+1;(m=n*p[j]*p[j])<=B;j++)
   for(k=0;(q=m*p[k])<=B;k++) if(k!=i && k!=j)
      ans+=cnt[B/q]+cnt[int(B/sqrt(3.)/q+eps)];
   printf("%lld\n",ans);
   printf("time=%.3lfsec\n",0.001*(clock()-start));
   return 0;
}

