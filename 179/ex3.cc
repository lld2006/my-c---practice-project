#include<cstdio>
#include<cstring>
#include<ctime>
const int mr=100;

bool isp[mr];
int p[mr];
short f[mr];
char e[mr];
int pr[670000],pn;

int main()
{
   memset(isp,1,sizeof(isp));
   int ans=0;
   p[1]=f[1]=1;
   for(int i=2,tmp;i<mr;i++)
   {
      if(isp[i]){
          pr[pn++]=i; //number of primes inc by 1, it is i
          f[i]=2; //i is prime, two divisors
          e[i]=1; //only i^1
          p[i]=i; //least prime factor
      } else 
          f[i]=(e[i]+1)*f[i/p[i]];

      for(int j=0;j<pn && (tmp=pr[j]*i)<mr;j++) { 
          //select those numbers that may be expressed as i*pr[j], 
          //these numbers p[] e[] can be easily found
         isp[tmp]=0;
         f[tmp]=pr[j];
         if(i%pr[j]){ //not divisible by small primes
             e[tmp]=1; //just use the factor from i
             p[tmp]=f[tmp]; // same as above line
         }
         else {
             e[tmp]=e[i]+1;
             p[tmp]=p[i]*f[tmp];
             break;
         }
      }
      if(f[i]==f[i-1])ans++;
   }
   
   printf("%d\nTime=%.4lf\n",ans,(double)clock()/CLOCKS_PER_SEC);
   return 0;
}
