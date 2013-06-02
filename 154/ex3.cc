#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>

typedef long long int int64;

struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};

void f154()
{
   const int N=200000;
   const int N3=N/3;
   int *pn = new int [2+N*2];
   int* pn2=pn;
   int* pn5=pn+N+1;
   int i=-1;
   while (++i<=N)
   {
      int j=i, k=0;
      while (j>=2)
         j>>=1, k+=j;
      pn2[i]=k;
      j=i, k=0;
      while (j>=5)
         j/=5, k+=j;
      pn5[i]=k;
   }
   int64 nt=0;
   i=N+1;
   while (--i>=N3)
   {
      int n2=pn2[N]-pn2[i];
      int n5=pn5[N]-pn5[i];
      if (n5<12 || n2<12)
         continue;
      int j=i;
      if (i+j>N)
         j=N-i;
      int k=N-i-j;
      if (k<j)
      {
         if (n5-pn5[j]-pn5[k]>=12 && n2-pn2[j]-pn2[k]>=12)
            nt+=3;
         while (--j>++k)
            if (n5-pn5[j]-pn5[k]>=12 && n2-pn2[j]-pn2[k]>=12)
               nt+=6;
         if (j==k && n5-pn5[j]-pn5[k]>=12 && n2-pn2[j]-pn2[k]>=12)
            nt+=3;
      }
   }
   printf("%lld\n",nt);
   delete [] pn;
}

int main(int argc, char**argv)
{
   //timer t;
   f154();
   return 0;
}
