#include<cstdio>
#include "../lib/typedef.h"

using namespace std;


i64 dp[12][262144];

i64 ways(int state, int level) {
   int i=0, s;
   s = state;
   for(i=0;i<9;i++) {
      if((s&3)==0) {
         break;
      }
      s>>=2;
   }
   while(i==9) {
      level++;
      for(i=0;i<9;i++) {
         state -= 1<<(2*i);
      }
      if(level==12) {
         if(state==0)
            return 1;
         else
            return 0;
      }
      s = state;
      for(i=0;i<9;i++) {
         if((s&3)==0) {
            break;
         }
         s>>=2;
      }
   }
   if(dp[level][state]>=0) {
      return dp[level][state];
   }
   i64 tot = 0;
   //case 1
   if(i<8&&(state&(3<<2*(i+1)))==0) {
      tot += ways(state+(2<<(2*i))+(1<<(2*(i+1))),level);
   }
   //case 2
   if(i<8&&(state&(3<<2*(i+1)))==0) {
      tot += ways(state+(1<<(2*i))+(2<<(2*(i+1))),level);
   }
   //case 3a
   if(i<8&&(state&(3<<2*(i+1)))==(1<<2*(i+1))) {
      tot += ways(state+(2<<(2*i))+(1<<(2*(i+1))),level);
   }
   //case 3b
   if(i<7&&(state&(3<<2*(i+1)))==0&&(state&(3<<2*(i+2)))==0) {
      tot += ways(state+(2<<(2*i))+(2<<(2*(i+1)))+(2<<(2*(i+2))),level);
   }
   //case 3c
   if(i<6&&(state&(3<<2*(i+1)))==0&&(state&(3<<2*(i+2)))==0&&(state&(3<<2*(i+3)))==0) {
      tot += ways(state+(2<<(2*i))+(2<<(2*(i+1)))+(1<<(2*(i+2)))+(1<<(2*(i+3))),level);
   }	
   //case 4
   if(i>0&&(state&(3<<2*(i-1)))==(1<<2*(i-1))) {
      tot += ways(state+(2<<(2*i))+(1<<(2*(i-1))),level);
   }
   //case 5
   tot += ways(state+(3<<(2*i)),level);
   //case 6
   if(i<7&&(state&(3<<2*(i+1)))==0&&(state&(3<<2*(i+2)))==0) {
      tot += ways(state+(1<<(2*i))+(1<<(2*(i+1)))+(1<<(2*(i+2))),level);
   }
   return dp[level][state]=tot;
   
}

int main()
{
   for(int i=0;i<12;i++) {
      for(int j=0;j<(1<<18);j++) {
         dp[i][j] = -1;
      }
   }
   i64 ans = ways(0,0);
   printf("%lld\n", ans);
   return 0;
}
