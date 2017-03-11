
#include <stdio.h>
#include <algorithm>
#define N 40000000 
int fac[N+1], phi[N+1], cyc[N+1];
int np, prime[N+1];
int main()
{
   int i, j, c = 0;
   long long int s = 0;
   for(i = 0; i <= N; i++)
      fac[i] = i;
   np = 0; phi[1] = 1; cyc[1] = 1;
   for(i = 2; i <= N; i++) {
      j = i/fac[i];
      if(j % fac[i] == 0)
         phi[i] = phi[j] * fac[i];
      else
         phi[i] = phi[j] * (fac[i]-1);
      cyc[i] = cyc[phi[i]] + 1;
      if(fac[i] != i) continue;
      if(cyc[i] == 25) {
         //printf("cyc(%d) = %d, phi[%d] = %d\n", i, cyc[i], i, phi[i]);
         ++c; s += i;
      }
      for(j = i*i; i < 32768 && j <= N; j+=i) {
         if(fac[j] < j) continue;
         fac[j] = i;
      }
   }
   printf("\n%d %d %lld\n",np, c, s);
   return 0;
}

