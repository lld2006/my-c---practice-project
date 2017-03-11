#include<cstdio>
const int ms=300000;

int f[2][51][ms];

int main()
{
   int s=0,t=1;
   f[0][0][0]=f[1][0][0]=1;
   for(int i=1,sum=1;i<=100;i++,sum+=i*i)
   {
      for(int j=1;j<=50&&j<=i;j++)
         for(int k=1;k<ms&&k<=sum;k++)
         {
            f[t][j][k]=f[s][j][k];
            if(k>=i*i)f[t][j][k]+=f[s][j-1][k-i*i];
         }
      s^=1,t^=1;
   }
   long long ans=0;
   for(int i=0;i<ms;i++)
      if(f[s][50][i]==1)ans+=i;
   printf("%lld\n",ans);
   return 0;
}
