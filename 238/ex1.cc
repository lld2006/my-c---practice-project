#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define a0 14025256
#define M 20300713
#define N 2000000000000000LL
     
int main()  {
     
    int d[10],i,j,n,x,iter,len,up,br,pos,s,num;
    long long int a,S,total;
    unsigned char *digit,*p;
    
    a=a0;
    for(iter=1;;iter++)  {
        a=(a*a)%M;
        if(a==a0)  break;
    }
    printf("Blum's period=%d\n",iter);
    
    num=(int) ((double) (iter+200)*(1+log(M)/log(10))); //number of digits for the whole periodic digits array
    digit=(unsigned char*)(malloc)(num*sizeof(unsigned char));
    p=(unsigned char*)(malloc)(5*num*sizeof(unsigned char));
    
    S=0,br=0,a=a0,pos=0;
    for(i=1;i<iter+200;i++)  {
        x=a;
        len=0;
        while(x)  d[len]=x%10,x/=10,len++;
        for(j=len-1;j>=0;j--)  {
            digit[pos]=d[j];
            if(i<=iter)  S+=digit[pos];
            pos++;
        }
        a=(a*a)%M;
    }//end of creating digits
    for(i=0;i<5*num;i++)  p[i]=0;
    for(i=0;i<200;i++)  {
        s=0;
        for(j=i;j<pos;j++)  {
            s+=digit[j];
            if(p[s]==0)  p[s]=i+1;
        }
    }

    total=0;
    if(N<S)  {
       for(i=1;i<=N;i++)  total+=p[i];
    }
    else  {
       total=N/S;
       for(i=1;i<S;i++)  total+=p[i]*((N-i)/S+1);
    }
    printf("total=%lld\n",total);
    
    return 0;
}
