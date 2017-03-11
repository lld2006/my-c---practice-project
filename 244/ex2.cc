#include<stdio.h>
#include<queue>
#define BASE 100000007
using namespace std;
int d[1048576];
bool chk[1048576];
int cnt[1048576];
long long int checksum[1048576];
int start_pointer=209712, end_pointer=370080;
queue<int> q;
int a[4][4];
int dx[4]={0, 0, -1, 1};
int dy[4]={-1, 1, 0, 0};
int asc[4]={82, 76, 68, 85};
int main()
{
   int i, j, k;
   int cur, nxt;
   int tmp;
   int x, y, nx, ny;
   q.push(start_pointer); cnt[start_pointer]=1;
   while(!q.empty())
   {
      cur=q.front(); q.pop();
      y=cur&3; x=(cur>>2)&3;
      tmp=cur>>4;
      for(i=3;i>=0;i--)
      {
         for(j=3;j>=0;j--){a[i][j]=tmp&1; tmp>>=1;}
      }
      for(k=0;k<=3;k++)
      {
         nx=x+dx[k]; ny=y+dy[k];
         if(nx<0 || ny<0 || nx>3 || ny>3) continue;
         tmp=a[x][y]; a[x][y]=a[nx][ny]; a[nx][ny]=tmp;
         nxt=0;
         for(i=0;i<=3;i++)
         {
            for(j=0;j<=3;j++){nxt<<=1; nxt|=a[i][j];}
         }
         nxt<<=2; nxt|=nx; nxt<<=2; nxt|=ny;
         tmp=a[x][y]; a[x][y]=a[nx][ny]; a[nx][ny]=tmp;
         if(chk[nxt] && d[nxt]==d[cur]+1)
         {
            checksum[nxt]=(checksum[nxt]+(checksum[cur]*243+asc[k])%BASE)%BASE;
            cnt[nxt]+=cnt[cur];
         }
         else if(!chk[nxt] || d[nxt]>d[cur]+1)
         {
            chk[nxt]=true; d[nxt]=d[cur]+1;
            checksum[nxt]=(checksum[cur]*243+asc[k])%BASE;
            cnt[nxt]=cnt[cur];
            q.push(nxt);
         }
      }
   }
   printf("%d\n", d[end_pointer]);
   printf("%lld\n", checksum[end_pointer]);
   printf("%d\n", cnt[end_pointer]);
   return 0;
}
