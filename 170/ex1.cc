#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <numeric>
#include "../lib/typedef.h"

struct timer
{
   clock_t t;
   timer() { t = clock(); }
   ~timer() { printf("runtime %.3f secs\n", getTime()); }
   double getTime() { return ((double)clock()-(double)t)/(double)CLOCKS_PER_SEC; }
};

void f170()
{
   int i=0,j;
   i64 found=0;
   while (j=0, ++i<5){
      bool b[10]={false};
      b[i]=true;
      while (++j<10){
         if (b[j]!=false) continue;
         b[j]=true;
         int n1=i*10+j;
         int k=-1, a[8], *p=a;
         while (++k<10)
            if (b[k]==false) *p++=k;
         do
         {
            int len=1;
            while (++len<=4)
            {
               if (a[0]==0 || a[len]==0) continue;
               int n2=0;
               int i=-1;
               while (++i<len)
                  n2=n2*10+a[i];
               if (n2<n1) continue;
               int n12=n1*n2;
               bool b[10]={false};
               while (n12)
               {
                  int n=n12%10;
                  if (b[n]!=false)
                     break;
                  b[n]=true;
                  n12/=10;
               }
               if (n12!=0)
                  continue;
               int n3=0;
               i=len-1;
               while (++i<8)
                  n3=n3*10+a[i];
               if (n3<n2) continue;
               int n13=n1*n3;
               while (n13)
               {
                  int n=n13%10;
                  if (b[n]!=false)
                     break;
                  b[n]=true;
                  n13/=10;
               }
               if (n13==0)
               {
                  i64 n123;
                  n12=n1*n2, n13=n1*n3;
                  n123=n13;
                  int t=n12;
                  while (t>0)
                     n123*=10, t/=10;
                  n123+=n12;
                  if (n123>found)
                     found=n123;
               }
            }
         }
         while (std::next_permutation(a,a+8));
         b[j]=false;
      }
      b[i]=false;
   }
   printf("found=%lld\n",found);
}
int main(int argc, char**argv)
{
   timer t;
   f170();
   return 0;
}
/*
found=9857164023
runtime 0.190 secs
*/
