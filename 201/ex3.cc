#include<stdio.h>
#define SQ 544
int isqrt[SQ*SQ], S[101], c;

void countrep(int s, int max, int num) {
   int m=isqrt[s-S[num-1]];
   if(s==S[num]) return c++;
   if(num==1) return c+=(s==m*m);
   if(m>max) m=max;
   for(; S[m]-S[m-num] >= s && c<2; m--)
      countrep(s-m*m, m-1, num-1);
};

int main() {
   int n, i, pairs=0;
   for(n=1;n<=100;n++) S[n]=S[n-1]+n*n;
   for(n=0;n<SQ;n++) for(i=n*n;i<(n+1)*(n+1);i++) isqrt[i]=n;
   for(n=S[100]/2;n<=S[100]-S[50];n++) {
      c=0; countrep(n, 100, 50);
      if(c==1) pairs++;
   }
   printf("%i\n",S[100]*pairs);
}
