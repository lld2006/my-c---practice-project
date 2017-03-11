#include <stdio.h>
#include <string.h>
#define MOD 14348907

typedef long long LL;

LL cnt[24][220];    // the number cnt[length][sum]
LL sum[24][220];    // the sum
LL ten[48];
LL ret[48];

LL calcT(int l){
    int a,b,s;
    LL ans=0;
    LL count=0;
    LL s1,s2,c1,c2;
    a=l/2;
    b=l-a;
    for (s=0;s<=a*9;s++){
        c1=cnt[a][s];
        c2=cnt[a][s];
        if (a>0) c1=(c1-cnt[a-1][s]+MOD)%MOD;
        s1=sum[a][s];
        s2=sum[a][s];
        if (a>0) s1=(s1-sum[a-1][s]+MOD)%MOD;
        ans=(ans+c1*s2+c2*s1%MOD*ten[b])%MOD;
        count=(count+c1*c2)%MOD;
    }
    printf("a=%d b=%d\n",a,b);
    if (a!=b) ans=(ans*10+count*45*ten[a])%MOD;
    printf("ret[%d]=%lld\n",l,ans);
    return ans;
}

int main()
{
    int i,j,k,l;
    memset(cnt,0,sizeof(cnt));
    memset(sum,0,sizeof(sum));
    for (ten[0]=1,i=1;i<48;i++)
        ten[i]=ten[i-1]*10%MOD;
    cnt[0][0]=1;
    sum[0][0]=0;
    for (l=0;l<23;l++){
        for (i=0;i<=l*9;i++){
            for (j=0;j<10;j++){
                k=i+j;
                cnt[l+1][k]=(cnt[l+1][k]+cnt[l][i])%MOD;
                sum[l+1][k]=(sum[l+1][k]+cnt[l][i]*j*ten[l]+sum[l][i])%MOD;
            }
        }
    }
    for (i=0;i<48;i++)
        ret[i]=calcT(i);
    for (i=1;i<48;i++)
        ret[i]=(ret[i-1]+ret[i])%MOD;
    for (i=0;i<48;i++)
        printf("ret[%d]=%lld\n",i,ret[i]);
    return 0;
}
