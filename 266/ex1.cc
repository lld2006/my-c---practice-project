#include <stdio.h>
#include <string.h>
#include <math.h>
int primes[42]={
  2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73, 
  79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181
};

long double s=0,s_2,lp[42],*lp_=lp,x,eps,epsmin;
long double sum_[3][1<<21],*hsum=sum_[2],*sum,*sum1,*sum2,*hs;
int comb_[3][1<<21],*hcomb=comb_[2],*comb,*comb1,*comb2,*hc;
int i,j,k,hi,ii,imin,jmin;
long long int result=1;

int main() {
  for(i=0;i<42;i++)
    s+=lp[i]=logl(primes[i]);

  // generate two groups of sums of logarithms, remember combinations 
  for (ii=0;ii<2;ii++,lp_+=21) {
    sum=sum_[ii];
    comb=comb_[ii];
    sum[0]=0;comb[0]=0;
    for (i=0;i<21;i++) {
      j=0;k=0;x=lp_[i];hi=0;
      while (1) {
        if (j<(1<<i)&& comb[j]<x) {
          hsum[hi]=sum[j];
          hcomb[hi++]=comb[j++];
          continue;
        }
        hsum[hi]=x;
        hcomb[hi++]=comb[k++]+(1<<i);
        if (k==(1<<i)) break;
        x=lp_[i]+sum[k];
      }
      hs=sum;sum=hsum;hsum=hs;
      hc=comb;comb=hcomb;hcomb=hc;
    }
    if (!ii) {sum1=sum;comb1=comb;} else {sum2=sum;comb2=comb;}
  }

  // find best match
  s_2=s/2;epsmin=s;i=-1;j=(1<<21)-1;
  while(++i<(1<<21)) {
    while((eps=s_2-sum1[i]-sum2[j])<0) j--;
    if (eps<epsmin) {imin=i;jmin=j;epsmin=eps;}
  }

  // postprocess
  //printf("%d %d %.20llf\n",imin,jmin,epsmin);
  for(ii=0;ii<2;ii++) {
    for(k=!ii?comb1[imin]:comb2[jmin],i=0; k; k>>=1,i++) if(k&1) {
      printf("%d,",primes[i+21*ii]);
      result*=primes[i+21*ii];
      result%=10000000000000000ll;
    }
  }
  printf("\n%lld\n",result);
}
