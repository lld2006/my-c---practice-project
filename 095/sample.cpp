#include <stdio.h> 
#include <math.h> 
int next [1000000]; 
int table[1000000]; 
int main() { 
    int i; int j; int max=0; int temp,m; int n,k; 
    next[0]=next[1]=0; 
    for(i=2;i<1000000;i++) 
        next[i]=1; 
    for(i=2;i<500000;i++) 
        for(j=i<<1;j<1000000;j+=i) 
            next[j]+=i; 
    for(i=2;i<=1000000;i++) {
        n=0;j=i; table[n++]=i; 
        while(1) { if(j>=1000000) break; 
            j=next[j]; for(k=0;k<n;k++) 
                if(table[k]==j) break; 
            if(k!=n) break; 
            table[n++]=j; temp++; 
        } 
        if(j==i) { 
            if(n>max) { 
                max=n; m=j; 
            } 
        //printf("%d %d\n",i,n); 

        } 
    } 
    printf("%d %d\n",m,max); 
    return 0; 
}
