
#include <stdio.h>

int powmod(int base, int exp, int mod) {
  int p=base%mod,x=1;
  while (exp) {
    if (exp&1) x=(x*p)%mod;
    p=(p*p)%mod;
    exp>>=1;
  }
  return x;
}
  

int main() {
  long long unsigned x_[250],y_[250], *x=x_,*y=y_,*h, m=10000000000000000llu;
  int i,j,rem;

  x[0]=1; for (i=1;i<250;i++) x[i]=0;
  
  for (i=1;i<=250250;i++) {
    rem=powmod(i,i,250);
    for (j=0;j<250;j++) y[(j+rem)%250]=(x[(j+rem)%250]+x[j])%m;
    h=x;x=y;y=h;
  }

  printf("%llu\n",x[0]-1);
}
