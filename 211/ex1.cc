#include <stdio.h>
#include <math.h>


int main()  {

    int isprime[8096],primes[1028],A[8000],i,j,q,n,up,np;
    long long int S[8000],sum=0,mul,div,p,sq;
    
    for(i=0;i<8096;i++)  isprime[i]=1;
    isprime[0]=0;
    isprime[1]=0;
    np=0;
    for(i=2;i<8096;i++)  {
        if(isprime[i])  {
            for(j=i*i;j<8096;j+=i)  isprime[j]=0;
            primes[np]=i;
            np++;
        }
    }
    for(n=0;n<64000000;n+=8000)  {
        for(i=0;i<8000;i++)  A[i]=1;
        for(i=0;i<8000;i++)  S[i]=1;
        up=n+8000;
        for(i=0;primes[i]*primes[i]<=up;i++)  {
            p=primes[i];
            q=1;
            mul=1;
            while(q<=up/p)  {
                  q*=p;
                  div=mul;
                  mul=mul*p*p+1;
                  for(j=((n+q-1)/q)*q-n;j<8000;j+=q)  S[j]/=div,S[j]*=mul,A[j]*=p;
            }
        }
        for(i=(n==0);i<8000;i++)  {
            if(A[i]!=n+i)  {
               p=(n+i)/A[i];
               S[i]*=p*p+1;
            }
            sq=(long long int) sqrt(S[i]);
            if(sq*sq==S[i])  sum+=n+i;
        }
    }
    printf("%lld\n",sum);
    return 0;
}
