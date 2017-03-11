
#include <stdio.h>
#include <stdlib.h>

int MIN(int a,int b)  {
    if(a<b)  return a;
    return b;
}


int main()  {

    int **A,i,j,k,i2,M;
    long long int sum;
    A=(int**)(malloc)(51*sizeof(int*));
    for(i=0;i<=50;i++)  A[i]=(int*)(malloc)(300000*sizeof(int));
    
    for(i=0;i<=50;i++)
        for(j=0;j<300000;j++)  A[i][j]=0;
    A[0][0]=1;
    for(i=1;i<=100;i++)  {
        M=i;
        if(M>50)  M=50;
        i2=i*i;
        for(j=M;j>0;j--)
            for(k=299999;k>=i2;k--)
                if(A[j-1][k-i2]>0)  A[j][k]=MIN(2,A[j-1][k-i2]+A[j][k]);
    }
    sum=0;
    for(i=0;i<300000;i++)
        if(A[50][i]==1)  sum+=i;
    printf("%lld\n",sum);
    return 0;
}
