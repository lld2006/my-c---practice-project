#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
 
int main()  {

    double dtime=clock();

    int target  = 100000000;
    
    int *A,isprime[10000],d,n,e,p,k,sum;
    A=(int*) (malloc) ((target+1)*sizeof(int));
    
    for(n=1;n<=target;n++)  A[n]=0;
    for(n=2;n<10000;n++)  isprime[n]=1; // only check numbers upto sqrt(target)
    
    for(d=2;d<10000;d++)  {
        if(isprime[d])  {
            for(n=d*d;n<10000;n+=d)  isprime[n]=0;
            for(n=d*d;n<=target;n+=d)  A[n]=d;
        }
    }
    
    A[1]=1;
    for(n=2;n<=target;n++)  {
        if(A[n]==0)  A[n]=2;
        else {
           p=A[n],k=n/p,e=2;
           while(k%p==0)  k/=p,e++;
           A[n]=A[k]*e;
        }
    }        
    
    sum=0;
    for(n=2;n<target;n++)
        if(A[n]==A[n+1])  sum++;
    
    printf("%d,time=%.3lf sec.\n",sum,(double) (clock()-dtime)/CLOCKS_PER_SEC);
    return 0;
}
