#include <stdio.h>


int main()  {

    int h,k,n,s,d,c,M,res,i,j;
    unsigned long long int sum,dp[21][13][11][71],b[21][21],power[21][21],MOD;
    
    for(i=0;i<=20;i++)  {
        power[i][0]=1;
        for(j=1;j<=20;j++)  power[i][j]=i*power[i][j-1];
    }
    for(n=0;n<=20;n++)  {
        b[n][0]=1;
        b[n][n]=1;
        for(k=1;k<n;k++)  b[n][k]=b[n-1][k-1]+b[n-1][k];
    }
    
    for(d=0;d<=20;d++)  {
        for(k=0;k<=12;k++)  {
            for(h=0;(h<=d)&&(h<=10);h++)  {
            for(s=0;s<=70;s++)  {
                sum=0;
                for(M=1;M<=k;M++)
                    for(c=1;c<=d;c++)  {
                        res=s-M*c;
                        if((res<=0)&&(s==M*h)&&(c>=h))  sum+=b[d][c]*power[M-1][d-c];
                        else if((res>0)&&(c<=h))        sum+=b[d][c]*dp[d-c][M-1][h-c][s-M*c];
                    }
                if((k>0)&&(h>0)) dp[d][k][h][s]=sum;
                else  dp[d][k][h][s]=((s==0)&&(h==0));
    }}}}
    printf("%llu\n",dp[20][12][10][70]);
    return 0;
}
