#include <cstdio>
#include <ctime>

typedef long long int int64;
struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.6f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};
enum{N=50000000};
void f216()
{
   int64* pn=new int64 [N+1];
   int sum=0;
   int i=0, a=-2;
   pn[0]=-1;
   while (a+=4, ++i<=N)
      pn[i]=pn[i-1]+a;
   i=-1;
   while (++i<=N)
   {
      int64 t=pn[i];
      if (t<=1)
         continue;
      if ((int)((t+1)>>1)==i*i)
         ++sum;
      int64 j=-i;
      while (j+=t, j<=N)
         while (pn[j]/=t, pn[j]%t == 0);
      j=i;
      while (j+=t, j<=N)
         while (pn[j]/=t, pn[j]%t == 0);
   }
   printf("sum=%d\n",sum);
   delete pn;
}
int main(int argc, char**argv)
{
   timer t;
   f216();
   return 0;
}
/*
sum=5437849
runtime 13.415 secs
*/

