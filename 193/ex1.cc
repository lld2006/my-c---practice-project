#include <stdio.h>
#include <stdlib.h>


#define interval 32768
void printint64(long long int n)  {
    if(n<0) printf("-"),n=-n;
    int digit[20],i;
 
    for(i=0;i<20;i++)  digit[i]=n%10,n/=10;
    i=19;
    while((i>0)&&(digit[i]==0))  i--;
    while(i>=0) printf("%d",digit[i]),i--;
 
    return;
}

int main()  {
    
    int R=1<<25;
    long long int N=(long long int) R*R-1;
    int moebius[interval],prod[interval],isprime[6000],primes[800],i,I,j,p,q,up,first,last,count=0;
    long long int sum;
    //first found the primes < 6000
    for(i=0;i<6000;i++) 
        isprime[i]=1;
    isprime[0]=0,isprime[1]=0;
    for(i=2;i<6000;i++) {
        if(isprime[i]) {
            for(j=i*i;j<6000;j+=i) isprime[j]=0;
            primes[count]=i,count++;
        }
    }
 
    sum=0;
    for(I=0;I<=R;I+=interval)  {
        up=I+interval;
        for(i=0;i<interval;i++)  
            moebius[i]=1;
        for(i=0;i<interval;i++)  
            prod[i]=1;
        for(i=0;primes[i]*primes[i]<=up;i++)  {
           p=primes[i];
           for(j=(I+p-1)/p*p-I;j<interval;j+=p)  
               moebius[j]=-moebius[j];
           for(j=(I+p-1)/p*p-I;j<interval;j+=p)  
               prod[j]*=p;  //if prod[j] == j + I, then all factors are in prime range, 
                            // otherwise there is a large factor need to be considered
           q=p*p;
           for(j=(I+q-1)/q*q-I;j<interval;j+=q)  
               moebius[j]=0;
        }
        for(i=0;i<interval;i++)
            if((moebius[i]!=0)&&(prod[i]!=i+I))  
                moebius[i]=-moebius[i];
        if(I==0) 
            first=1;
        else    
            first=0;
        if(I+interval-1>R) 
            last=R-I;
        else               
            last=interval-1;
        for(i=first;i<=last;i++) 
            sum+=N/((long long int) (I+i)*(I+i))*moebius[i];
    }
    printint64(sum);
    return 0;
}
